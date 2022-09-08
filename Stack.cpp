#pragma once
#include<algorithm>

	// объявление класса

	template<typename T>
	class Stack
	{
		size_t capacity;
		size_t size;
		T* mem, * top;
	public:
		Stack(int _capacity = 10);
		~Stack()
		{
			
			Clear();
		}

		Stack(const Stack& other);
		Stack& operator= (const Stack& other);
		void Push(T val);
		void Pop();
		T GetHead() const
		{
			if (Empty())
			{
				std::cout << "Stack is empty " << std::endl;
				return -1;
			}
			return *top;
		}
		void SetHead(T val)
		{
			if (Empty())
				Push(val);
			else
				*top = val;
		}
		void Clear();
		bool Empty() const;
		bool Full() const;
		size_t GetSize() const;
		size_t GetCapacity() const;
		void Show() const;
		void Swap(Stack &other);
	};

	//реализация методов
	template<typename T>
	void Stack<T>::Swap(Stack<T>& other)
	{
		std::swap(mem, other.mem);
		std::swap(size, other.size);
		std::swap(capacity, other.capacity);
		std::swap(top, other.top);
		
	}
	template<typename T>
	Stack<T>& Stack<T>::operator= (const Stack<T>& other)
	{
		if (this == &other)
			return *this;
		Stack<T> temp(other);
		this->Swap(temp);
		return *this;
	}
	template<typename T>
	Stack<T>::Stack(int _capacity) : capacity(_capacity), size(0), mem(new T[capacity]), top(mem + capacity) {

		if (capacity <= 0)
		{
			std::cout << "Capacity is default (10)" << std::endl;
			capacity = 10;
		}
	}
	
	template<typename T>
	Stack<T>::Stack(const Stack& other) : capacity(other.capacity), size(other.size), mem(new T[capacity]), top(mem + capacity - size)
	{
		T* curother = other.top;
		T* curthis = top;
		while (curthis != mem + capacity)
		{
			*curthis = *curother;
			curother++;
			curthis++;
		}
	}

	template<typename T>
	void Stack<T>::Push(T val)
	{
		if (this->Full())
		{
			std::cout << "Stack is full" << std::endl;
			return;
		}
		size++;
		*(--top) = val;
	}

	template<typename T>
	size_t Stack<T>::GetSize() const
	{
		
		return size;
	}

	template<typename T>
	bool Stack<T>::Full() const
	{
		
		return (size == capacity);
	}

	template<typename T>
	bool Stack<T>::Empty() const
	{
		
		return (size == 0);
	}

	template<typename T>
	void Stack<T>::Pop()
	{
		
		if (this->Empty())
		{
			std::cout << "Stack is empty" << std::endl;
			return;
		}
		size--;
		top++;
	}

	template<typename T>
	size_t Stack<T>::GetCapacity() const
	{
		
		return capacity;
	}

	template<typename T>
	void Stack<T>::Clear()
	{
		
		delete[]mem;
		mem = top = nullptr;
	}

	template<typename T>
	void Stack<T>::Show() const
	{
		
		if (this->Empty())
		{
			std::cout<<"Stack is empty"<< std::endl;
			return;
		}
		T* cur = this->top;
		int i = 0;
		while (i < size)
		{
			std::cout << *(cur++) <<" ";
			i++;
		}
		std::cout << std::endl;
	}

