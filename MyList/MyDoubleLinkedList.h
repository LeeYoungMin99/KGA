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
	// �⺻ ������
	MyDoubleLinkedList()
	{
		_head->Next = _end;
		_end->Prev = _head;
	}

	// count��ŭ�� ��Ҹ� ���� �ִ� �����̳ʸ� ����� ������
	explicit MyDoubleLinkedList(size_t count)
		:MyDoubleLinkedList()
	{
		for (size_t i = 0; i < count; ++i)
		{
			push_back(0);
		}
	}

	// ���� ������.
	MyDoubleLinkedList(const MyDoubleLinkedList& other)
		:MyDoubleLinkedList()
	{
		for (const Node* iter = other.begin(); iter != other.end(); iter = iter->Next)
		{
			push_back(iter->Data);
		}
	}

	// �Ҵ� ������
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

	// �Ҹ���
	~MyDoubleLinkedList()
	{
		clear();

		_head = nullptr;
		_end = nullptr;
	}

	// ù ��° ��Ҹ� ��ȯ�Ѵ�.
	int& front() { return begin()->Data; }
	const int& front() const { return begin()->Data; };

	// ������ ��Ҹ� ��ȯ�Ѵ�.
	int& back() { return end()->Prev->Data; }
	const int& back() const { return end()->Prev->Data; }

	// ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	// ����Ʈ�� ����ִٸ� end()�� ����.
	Node* begin() { return _head->Next; }
	const Node* begin() const { return _head->Next; }

	// �� ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* end() { return _end; }
	const Node* end() const { return _end; }

	// pos ������ value�� �����Ѵ�.
	// ���Ե� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
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

	// pos �� �����Ѵ�.
	// ������ ����� ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	// �ƹ� ��ҵ� ������ end()�� ��ȯ�Ѵ�.
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

	// ���ۿ� value�� �����Ѵ�.
	void            push_front(int value) { insert(begin(), value); }

	// ���� value�� �����Ѵ�.
	void            push_back(int value) { insert(end(), value); }

	// ���� ��Ҹ� �����Ѵ�.
	void            pop_front() { erase(begin()); }

	// �� ��Ҹ� �����Ѵ�.
	void            pop_back() { erase(end()->Prev); }

	// �����̳ʰ� ������� �Ǵ��Ѵ�.
	bool            empty() const { return _size == 0; }

	// ����Ʈ �ȿ� �ִ� ����� ������ ��ȯ�Ѵ�.
	size_t          size() const { return _size; };

	// �����̳ʸ� ���������.
	void            clear()
	{
		while (false == empty())
		{
			pop_front();
		}
	}

	// �ش� value�� �ִ��� üũ�Ѵ�.
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

