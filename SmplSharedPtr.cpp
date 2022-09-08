#pragma once
#include <iostream>
#include<algorithm>

template<typename T>
struct SharedPtr
{

    void swap(SharedPtr& other)
    {
        std::swap(counter, other.counter);
        std::swap(ptr_, other.ptr_);
    }
    explicit SharedPtr(T* ptr = 0) : ptr_(ptr), counter(0)
    {
        if (ptr_)
            counter = new int(1);
    }
    ~SharedPtr()
    {
       
        if (ptr_ && !(--(*counter)))
        {
            std::cout << "destr " << *ptr_ << std::endl;
            delete counter;
            delete ptr_;
        }
    }
    SharedPtr(const SharedPtr& other) :
        ptr_(other.ptr_), counter(other.counter)
    {
        if (ptr_) 
            ++(*counter);
    }
    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this != &other)
        {
            SharedPtr(other).swap(*this);
        }
        return *this;
    }
    T& operator[](int i)
    {
        return *(ptr_+i);
    }
    T* get() const
    {
        return  ptr_;
    }

    T& operator*() const
    {
        return *ptr_;
    }
    T* operator->() const
    {
        return ptr_;
    }
    int* counter;
    T* ptr_;
};
