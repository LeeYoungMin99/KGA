#pragma once

#include "MySingleLinkedList.h"
#include <algorithm>

class MyStack
{
public:
	// �⺻ ������
	MyStack() = default;

	// ���� ������
	MyStack(const MyStack& other)
		:_container{ other._container }, _size{ other._size }
	{

	}

	// �Ҵ� ������
	MyStack& operator=(const MyStack& rhs)
	{
		if (this != &rhs)
		{
			_container = rhs._container;
			_size = rhs._size;
		}
	}

	// �Ҹ���
	~MyStack() = default;

	// ������ �� �� ��ҿ� �����Ѵ�.
	int& top() { return _container.front(); }
	const int& top() const { return _container.front(); }

	// ������ ������� �˻��Ѵ�.
	bool            empty() const { return _container.empty(); }

	// ������ ũ�⸦ ��ȯ�Ѵ�.
	size_t          size() const { return _size; }

	// ���ÿ� �����͸� �����Ѵ�.
	void            push(int value)
	{
		++_size;
		_container.push_front(value);
	}

	// ���ÿ��� �����͸� �����Ѵ�.
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

