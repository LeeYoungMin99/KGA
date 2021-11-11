#pragma once

#include "MyDoubleLinkedList.h"

class MyQueue
{
public:
    // 기본 생성자
    MyQueue() = default;

    // 복사 생성자
    MyQueue(const MyQueue& other)
        :_container{other._container}
    {
    }

    // 할당 연산자
    MyQueue& operator=(const MyQueue& rhs)
    {
        if (this != &rhs)
        {
            _container = rhs._container;
        }

        return *this;
    }

    // 소멸자
    ~MyQueue() = default;

    // 큐의 첫 번째 요소에 접근한다.
    int& front() { return _container.front(); }
    const int& front() const { return _container.front(); }

    // 큐의 마지막 요소에 접근한다. 
    int& back() { return _container.back(); }
    const int& back() const { return _container.back(); }

    // 큐가 비었는지 확인한다.
    bool            empty() const { return _container.empty(); }

    // 큐의 크기를 반환한다.
    size_t          size() const { return _container.size(); }

    // 큐에 데이터를 삽입한다.
    void            push(int value) { return _container.push_back(value); }

    // 큐에서 데이터를 꺼낸다.
    void            pop() { return _container.pop_front(); }
private:
    MyDoubleLinkedList        _container;
};

