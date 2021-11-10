#pragma once

#include "MyVector.h"
#include <algorithm>
class MyStack
{
public:
    // 기본 생성자
    MyStack() = default;

    // 복사 생성자
    MyStack(const MyStack& other)
        :_container{ other._container }
    {
         
    }

    // 할당 연산자
    MyStack& operator=(const MyStack& rhs)
    {
        if (this != &rhs)
        {
            MyStack temp(rhs);
            std::swap(_container,temp._container);
        }
    }
        

    // 소멸자
    ~MyStack() = default;

    // 스택의 맨 위 요소에 접근한다.
    int& top() { return _container.back(); }
    const int& top() const { return _container.back(); }

    // 스택이 비었는지 검사한다.
    bool            empty() const { return _container.empty(); }

    // 스택의 크기를 반환한다.
    size_t          size() const { return _container.size(); }

    // 스택에 데이터를 삽입한다.
    void            push(int value) { return _container.push_back(value); }

    // 스택에서 데이터를 제거한다.
    void            pop() { return _container.pop_back(); }
private:
    MyVector        _container;
};
