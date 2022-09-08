#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

mutex cout_lock;
class thread_pool
{
public:

    explicit thread_pool(size_t thread_count = thread::hardware_concurrency())
    {
       cout << "creating " << thread_count << " threads..." << endl;
        for (auto i = 0; i < thread_count; ++i)
        {
            threads.push_back(thread([&]()
                {
                    while (true)
                    {
                        work_item_ptr_t work{ nullptr };
                        {
                            unique_lock guard(tasks_lock);
                            cv.wait(guard, [&]() { return !tasks.empty(); });
                            work = move(tasks.front());
                            cout << "thread " << i << " is working\n";
                            tasks.pop();
                        }
                        if (!work)
                            break;
                        (*work)();
                    }
                }));
        }
    }

    ~thread_pool()
    {
        {
            unique_lock guard(tasks_lock);
            for (auto& t : threads)
                tasks.push(work_item_ptr_t{ nullptr });
        }
        for (auto& t : threads)
            t.join();
    }

    

    using work_item_t = function<void(void)>;
    void do_work(work_item_t wi)
    {
        work_item_ptr_t work_item = make_unique<work_item_t>(move(wi));
        {
            unique_lock<mutex> guard(tasks_lock);
            tasks.push(move(work_item));
        }
        cv.notify_one();
    }

private:
    using work_item_ptr_t = unique_ptr<work_item_t>;
    queue<work_item_ptr_t> tasks;
    mutex tasks_lock;
    condition_variable cv;
    vector<thread> threads;
};

int main()
{
	using namespace std;
	mutex cout_guard;
	thread_pool tp;

	for (auto i = 1; i <= 50; i++)
		tp.do_work([&, i = i]()
			{
				{
					unique_lock guard(cout_guard);
					cout << "task " << i<< endl;
				}
			});
}

