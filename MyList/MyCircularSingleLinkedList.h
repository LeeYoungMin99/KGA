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
	// �⺻ ������
	MyCircularSingleLinkedList() = default;

	MyCircularSingleLinkedList(const size_t& count)
		:MyCircularSingleLinkedList()
	{
		for (size_t i = 0; i < count; ++i)
		{
			push_front(0);
		}
	}

	// ���� ������
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

	// �Ҵ� ������
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

	// �Ҹ���
	~MyCircularSingleLinkedList()
	{
		clear();

		delete _before_head;
		_before_head = nullptr;
		_before_tail = nullptr;
	}

	// ù ��° ��Ҹ� ��ȯ�Ѵ�.
	int& front() { return head()->Data; }
	const int& front() const { return head()->Next->Data; }

	// ������ ��Ҹ� ��ȯ�Ѵ�.
	int& back() { return tail()->Data; }
	const int& back() const { return tail()->Data; }

	// ���� �� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* before_head() { return _before_head; }
	const Node* before_head() const { return _before_head; }

	// �� �� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* before_tail() { return _before_tail; }
	const Node* before_tail() const { return _before_tail; }

	// ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* head() { return _before_head->Next; }
	const Node* head() const { return _before_head->Next; }

	// �� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* tail() { return _before_tail->Next; };
	const Node* tail() const { return _before_tail->Next; };

	// pos ������ value�� �����Ѵ�.
	// ���Ե� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* insert_after(Node* pos, int value)
	{
		//Node* newNode = new Node(value);
		//Node* nextNode = pos->Next;
		//Node* tailNode = tail();
		//
		//if (nextNode == nullptr)		// ó�� ������
		//{
		//	newNode->Next = newNode;
		//	pos->Next = newNode;
		//	return newNode;
		//}
		//
		//newNode->Next = nextNode;
		//pos->Next = newNode;
		//
		//if (pos == tailNode)			// pos�� tail �̿�����
		//{
		//	_before_tail = pos;
		//}
		//else if (pos == before_tail())	// pos �� before_tail �϶�
		//{
		//	_before_tail = newNode;
		//}
		//else if (pos == before_head())	// pos�� before_head �϶�
		//{
		//	tail()->Next = newNode;
		//}
		//
		//return newNode;

		Node* newNode = new Node(value);
		newNode->Next = pos->Next;
		pos->Next = newNode;
		// ù ��° ���Ұ� ���Ե� ��
		if (head()->Next == nullptr)
		{
			head()->Next = head();
		}
		// �� ��° ���Ұ� ���Ե� ��
		else if (before_head() == before_tail())
		{
			_before_tail = head();
			tail()->Next = head();
		}
		// before_tail / tail�� ������ ��
		else if (pos == before_tail() || pos == tail())
		{
			_before_tail = _before_tail->Next;
		}
		// before_head()�� ������ ��
		else if (pos == before_head())
		{
			tail()->Next = head();
		}
		return newNode;
	}

	// pos ���� ��Ҹ� �����Ѵ�.
	// ������ ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* erase_after(Node* pos)
	{
		//Node* removed = pos->Next;
		//Node* tailNode = tail();
		//
		//
		//if (_before_head == _before_tail)	//��Ұ� ���ų� �ϳ����϶�
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
		//if (removed == _before_tail)		// ������� ��Ұ� bt�ϋ�
		//{
		//	_before_tail = pos;
		//}
		//else if (removed == tailNode)			// ������� ��Ұ� tail�ϋ�
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
		// ���Ұ� �ϳ��� ��
		if (head()->Next == head())
		{
			before_head()->Next = nullptr;
		}
		// ���Ұ� �� ���� ��
		else if (before_tail() == head())
		{
			before_head()->Next = removed->Next;
			_before_tail = before_head();
			tail()->Next = head();
		}
		// tail�� �����Ϸ��� �� ��
		else if (pos == before_tail())
		{
			before_tail()->Next = removed->Next;
			while (tail()->Next != head())
			{
				_before_tail = _before_tail->Next;
			}
		}
		// before_tail�� ���ŵ� ��
		else if (removed == before_tail())
		{
			pos->Next = removed->Next;
			_before_tail = pos;
		}
		// ù �κ��� ���ŵ� ��
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
		//// ���Ұ� �ϳ��� ��
		//if (head()->Next == head())
		//{
		//	before_head()->Next = nullptr;
		//	removed->Next = nullptr;
		//	return removed;
		//}
		//pos->Next = removed->Next;
		//// ���Ұ� �� ���� ��
		//if (before_tail() == head())
		//{
		//	_before_tail = before_head();
		//	tail()->Next = head();
		//}
		//// tail�� �����Ϸ��� �� ��
		//else if (pos == before_tail())
		//{
		//	while (tail()->Next != head())
		//	{
		//		_before_tail = _before_tail->Next;
		//	}
		//}
		//// before_tail�� ���ŵ� ��
		//else if (removed == before_tail())
		//{
		//	_before_tail = pos;
		//}
		//// ù �κ��� ���ŵ� ��
		//else if (removed == head())
		//{
		//	before_head()->Next = removed->Next;
		//	tail()->Next = head();
		//}
		//removed->Next = nullptr;
		//return removed;
	}

	// ���� ��ҿ� value�� �����Ѵ�.
	void      push_front(int value)
	{
		insert_after(before_head(), value);
	}

	// ������ ��ҿ� value�� �����Ѵ�.
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

	// ���� ��Ҹ� �����Ѵ�.
	void      pop_front()
	{
		erase_after(before_head());
	}

	// ������ ��Ҹ� �����Ѵ�.
	void      pop_back()
	{
		erase_after(before_tail());
	}

	// �����̳ʰ� ������� �Ǵ��Ѵ�.
	bool      empty() const
	{
		return _before_head->Next == nullptr;
	}

	// �����̳ʸ� ���������.
	void      clear()
	{
		while (false == empty())
		{
			pop_front();
		}
	}

	// �����̳ʿ� value�� �ִ��� Ȯ���Ѵ�.
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
	// � ����� �ʿ��ұ�?
	Node* _before_head = new Node;
	Node* _before_tail = _before_head;

};
