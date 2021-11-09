#pragma once
#include <algorithm>

class MyCircularSingleLinkedList
{
public:
	struct Node
	{
		Node(int data = 0, Node* next = nullptr)
			: Data{ data }, Next{ next } { }
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		~Node() = default;

		int   Data = 0;
		Node* Next = nullptr;
	};

public:
	// 기본 생성자
	MyCircularSingleLinkedList() = default;

	MyCircularSingleLinkedList(const size_t& count)
		:MyCircularSingleLinkedList()
	{
		for (size_t i = 0; i < count; ++i)
		{
			push_front(0);
		}
	}

	// 복사 생성자
	MyCircularSingleLinkedList(const MyCircularSingleLinkedList& other)
		:MyCircularSingleLinkedList()
	{
		if (other.empty())
			return;

		for (const Node* iter = other.before_head(); iter != other.tail(); )
		{
			iter = iter->Next;
			push_back(iter->Data);
		}
	}

	// 할당 연산자
	MyCircularSingleLinkedList& operator=(const MyCircularSingleLinkedList& rhs)
	{
		if (this != &rhs)
		{
			MyCircularSingleLinkedList temp(rhs);
			std::swap(_before_head, temp._before_head);
			std::swap(_before_tail, temp._before_tail);
		}

		return *this;
	}

	// 소멸자
	~MyCircularSingleLinkedList()
	{
		clear();

		delete _before_head;
		_before_head = nullptr;
		_before_tail = nullptr;
	}

	// 첫 번째 요소를 반환한다.
	int& front() { return head()->Data; }
	const int& front() const { return head()->Next->Data; }

	// 마지막 요소를 반환한다.
	int& back() { return tail()->Data; }
	const int& back() const { return tail()->Data; }

	// 시작 전 요소를 가리키는 반복자를 반환한다.
	Node* before_head() { return _before_head; }
	const Node* before_head() const { return _before_head; }

	// 끝 전 요소를 가리키는 반복자를 반환한다.
	Node* before_tail() { return _before_tail; }
	const Node* before_tail() const { return _before_tail; }

	// 시작 요소를 가리키는 반복자를 반환한다.
	Node* head() { return _before_head->Next; }
	const Node* head() const { return _before_head->Next; }

	// 끝 요소를 가리키는 반복자를 반환한다.
	Node* tail() { return _before_tail->Next; };
	const Node* tail() const { return _before_tail->Next; };

	// pos 다음에 value를 삽입한다.
	// 삽입된 요소를 가리키는 반복자를 반환한다.
	Node* insert_after(Node* pos, int value)
	{
		//Node* newNode = new Node(value);
		//Node* nextNode = pos->Next;
		//Node* tailNode = tail();
		//
		//if (nextNode == nullptr)		// 처음 넣을때
		//{
		//	newNode->Next = newNode;
		//	pos->Next = newNode;
		//	return newNode;
		//}
		//
		//newNode->Next = nextNode;
		//pos->Next = newNode;
		//
		//if (pos == tailNode)			// pos가 tail 이였을때
		//{
		//	_before_tail = pos;
		//}
		//else if (pos == before_tail())	// pos 가 before_tail 일때
		//{
		//	_before_tail = newNode;
		//}
		//else if (pos == before_head())	// pos가 before_head 일때
		//{
		//	tail()->Next = newNode;
		//}
		//
		//return newNode;

		Node* newNode = new Node(value);
		newNode->Next = pos->Next;
		pos->Next = newNode;
		// 첫 번째 원소가 삽입될 때
		if (head()->Next == nullptr)
		{
			head()->Next = head();
		}
		// 두 번째 원소가 삽입될 때
		else if (before_head() == before_tail())
		{
			_before_tail = head();
			tail()->Next = head();
		}
		// before_tail / tail에 삽입할 때
		else if (pos == before_tail() || pos == tail())
		{
			_before_tail = _before_tail->Next;
		}
		// before_head()에 삽입할 때
		else if (pos == before_head())
		{
			tail()->Next = head();
		}
		return newNode;
	}

	// pos 다음 요소를 삭제한다.
	// 삭제된 요소를 가리키는 반복자를 반환한다.
	Node* erase_after(Node* pos)
	{
		//Node* removed = pos->Next;
		//Node* tailNode = tail();
		//
		//
		//if (_before_head == _before_tail)	//요소가 없거나 하나뿐일때
		//{
		//	_before_head->Next = nullptr;
		//	_before_tail = _before_head;
		//	removed->Next = nullptr;
		//	return removed;
		//}
		//else if (pos == tailNode)
		//{
		//	pos->Next = removed->Next;
		//	_before_head->Next = removed->Next;
		//}
		//else
		//{
		//	pos->Next = removed->Next;
		//}
		//
		//if (removed == _before_tail)		// 지우려는 요소가 bt일떄
		//{
		//	_before_tail = pos;
		//}
		//else if (removed == tailNode)			// 지우려는 요소가 tail일떄
		//{
		//	Node* iter = head();
		//	while (iter->Next != before_tail())
		//	{
		//		iter = iter->Next;
		//	}
		//
		//	_before_tail = iter;
		//}
		//
		//removed->Next = nullptr;
		//
		//return removed;
		//
		//
		if (empty())
		{
			return tail();
		}
		Node* removed = pos->Next;
		// 원소가 하나일 때
		if (head()->Next == head())
		{
			before_head()->Next = nullptr;
		}
		// 원소가 두 개일 때
		else if (before_tail() == head())
		{
			before_head()->Next = removed->Next;
			_before_tail = before_head();
			tail()->Next = head();
		}
		// tail을 제거하려고 할 때
		else if (pos == before_tail())
		{
			before_tail()->Next = removed->Next;
			while (tail()->Next != head())
			{
				_before_tail = _before_tail->Next;
			}
		}
		// before_tail이 제거될 때
		else if (removed == before_tail())
		{
			pos->Next = removed->Next;
			_before_tail = pos;
		}
		// 첫 부분이 제거될 때
		else if (removed == head())
		{
			before_head()->Next = removed->Next;
			tail()->Next = head();
		}
		else
		{
			pos->Next = removed->Next;
		}
		removed->Next = nullptr;
		return removed;

		//if (empty())
		//{
		//	return tail();
		//}
		//Node* removed = pos->Next;
		//// 원소가 하나일 때
		//if (head()->Next == head())
		//{
		//	before_head()->Next = nullptr;
		//	removed->Next = nullptr;
		//	return removed;
		//}
		//pos->Next = removed->Next;
		//// 원소가 두 개일 때
		//if (before_tail() == head())
		//{
		//	_before_tail = before_head();
		//	tail()->Next = head();
		//}
		//// tail을 제거하려고 할 때
		//else if (pos == before_tail())
		//{
		//	while (tail()->Next != head())
		//	{
		//		_before_tail = _before_tail->Next;
		//	}
		//}
		//// before_tail이 제거될 때
		//else if (removed == before_tail())
		//{
		//	_before_tail = pos;
		//}
		//// 첫 부분이 제거될 때
		//else if (removed == head())
		//{
		//	before_head()->Next = removed->Next;
		//	tail()->Next = head();
		//}
		//removed->Next = nullptr;
		//return removed;
	}

	// 시작 요소에 value를 삽입한다.
	void      push_front(int value)
	{
		insert_after(before_head(), value);
	}

	// 마지막 요소에 value를 삽입한다.
	void      push_back(int value)
	{
		if (tail() == nullptr)
		{
			insert_after(before_head(), value);
		}
		else
		{
			insert_after(tail(), value);
		}
	}

	// 시작 요소를 제거한다.
	void      pop_front()
	{
		erase_after(before_head());
	}

	// 마지막 요소를 제거한다.
	void      pop_back()
	{
		erase_after(before_tail());
	}

	// 컨테이너가 비었는지 판단한다.
	bool      empty() const
	{
		return _before_head->Next == nullptr;
	}

	// 컨테이너를 비워버린다.
	void      clear()
	{
		while (false == empty())
		{
			pop_front();
		}
	}

	// 컨테이너에 value가 있는지 확인한다.
	bool      contains(int value) const
	{
		if (empty())
			return false;

		for (auto iter = before_head(); iter != tail();)
		{
			iter = iter->Next;
			if (iter->Data == value)
			{
				return true;
			}
		}

		return false;
	}

private:
	// 어떤 멤버가 필요할까?
	Node* _before_head = new Node;
	Node* _before_tail = _before_head;

};
