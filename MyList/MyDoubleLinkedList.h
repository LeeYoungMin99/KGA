#pragma once

#include <algorithm>

class MyDoubleLinkedList
{
public:
	struct Node
	{
		Node(int data = 0, Node* prev = nullptr, Node* next = nullptr)
			:Data{ data }, Prev{ prev }, Next{ next }	{ }
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		~Node()
		{
			Next = nullptr;
			Prev = nullptr;
		}

		int   Data;
		Node* Next = nullptr;
		Node* Prev = nullptr;
	};

public:
	// 기본 생성자
	MyDoubleLinkedList()
	{
		_head->Next = _end;
		_end->Prev = _head;
	}

	// count만큼의 요소를 갖고 있는 컨테이너를 만드는 생성자
	explicit MyDoubleLinkedList(size_t count)
		:MyDoubleLinkedList()
	{
		for (size_t i = 0; i < count; ++i)
		{
			push_back(0);
		}
	}

	// 복사 생성자.
	MyDoubleLinkedList(const MyDoubleLinkedList& other)
		:MyDoubleLinkedList()
	{
		for (const Node* iter = other.begin(); iter != other.end(); iter = iter->Next)
		{
			push_back(iter->Data);
		}
	}

	// 할당 연산자
	MyDoubleLinkedList& operator=(const MyDoubleLinkedList& rhs)
	{
		if (this != &rhs)
		{
			MyDoubleLinkedList temp(rhs);
			std::swap(_head, temp._head);
			std::swap(_end, temp._end);
			std::swap(_size, temp._size);
		}

		return *this;
	}

	// 소멸자
	~MyDoubleLinkedList()
	{
		clear();

		_head = nullptr;
		_end = nullptr;
	}

	// 첫 번째 요소를 반환한다.
	int& front() { return begin()->Data; }
	const int& front() const { return begin()->Data; };

	// 마지막 요소를 반환한다.
	int& back() { return end()->Prev->Data; }
	const int& back() const { return end()->Prev->Data; }

	// 시작 요소를 가리키는 반복자를 반환한다.
	// 리스트가 비어있다면 end()와 같다.
	Node* begin() { return _head->Next; }
	const Node* begin() const { return _head->Next; }

	// 끝 다음 요소를 가리키는 반복자를 반환한다.
	Node* end() { return _end; }
	const Node* end() const { return _end; }

	// pos 이전에 value를 삽입한다.
	// 삽입된 요소를 가리키는 반복자를 반환한다.
	Node* insert(Node* pos, int value)
	{
		Node* newNode = new Node(value);
		newNode->Next = pos;
		newNode->Prev = pos->Prev;

		pos->Prev->Next = newNode;
		pos->Prev = newNode;

		++_size;

		return newNode;
	}

	// pos 를 삭제한다.
	// 삭제된 요소의 다음 요소를 가리키는 반복자를 반환한다.
	// 아무 요소도 없으면 end()를 반환한다.
	Node* erase(Node* pos)
	{
		if (empty() || end())
		{
			return end();
		}

		Node* nextNode = pos->Next;
		Node* prevNode = pos->Prev;

		nextNode->Prev = prevNode;
		prevNode->Next = nextNode;

		pos->Next = nullptr;
		pos->Prev = nullptr;

		--_size;

		return nextNode;
	}

	// 시작에 value를 삽입한다.
	void            push_front(int value) { insert(begin(), value); }

	// 끝에 value를 삽입한다.
	void            push_back(int value) { insert(end(), value); }

	// 시작 요소를 제거한다.
	void            pop_front() { erase(begin()); }

	// 끝 요소를 제거한다.
	void            pop_back() { erase(end()->Prev); }

	// 컨테이너가 비었는지 판단한다.
	bool            empty() const { return _size == 0; }

	// 리스트 안에 있는 요소의 개수를 반환한다.
	size_t          size() const { return _size; };

	// 컨테이너를 비워버린다.
	void            clear()
	{
		while (false == empty())
		{
			pop_front();
		}
	}

	// 해당 value가 있는지 체크한다.
	bool            contains(int value) const
	{
		for (const Node* iter = begin(); iter != end(); iter = iter->Next)
		{
			if (value == iter->Data)
			{
				return true;
			}
		}

		return false;
	}

private:
	Node* _end = new Node;
	Node* _head = new Node;
	size_t	_size = 0;
};

