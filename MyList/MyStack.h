#pragma once

#include "MySingleLinkedList.h"
#include <algorithm>

class MyStack
{
public:
	// 기본 생성자
	MyStack() = default;

	// 복사 생성자
	MyStack(const MyStack& other)
		:_container{ other._container }, _size{ other._size }
	{

	}

	// 할당 연산자
	MyStack& operator=(const MyStack& rhs)
	{
		if (this != &rhs)
		{
			_container = rhs._container;
			_size = rhs._size;
		}
	}

	// 소멸자
	~MyStack() = default;

	// 스택의 맨 위 요소에 접근한다.
	int& top() { return _container.front(); }
	const int& top() const { return _container.front(); }

	// 스택이 비었는지 검사한다.
	bool            empty() const { return _container.empty(); }

	// 스택의 크기를 반환한다.
	size_t          size() const { return _size; }

	// 스택에 데이터를 삽입한다.
	void            push(int value)
	{
		++_size;
		_container.push_front(value);
	}

	// 스택에서 데이터를 제거한다.
	void            pop()
	{
		if (empty())
		{
			return;
		}

		--_size;
		_container.pop_front();
	}
private:
	MySingleLinkedList			_container;
	size_t						_size = 0;
};

