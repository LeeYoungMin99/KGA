#pragma once

template <typename T>
class MyTemplateSingleLinkedList
{
	struct Node
	{
		Node(T data = {}, Node* next = nullptr)
			:Data{ data }, Next{ next }	{ }
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		~Node()
		{
			Next = nullptr;
		}

		T     Data = {};
		Node* Next = nullptr;
	};

public:
	// �⺻ ������
	MyTemplateSingleLinkedList()
	{
		_head->Next = _end;
	}

	// count��ŭ�� ��Ҹ� ���� �ִ� �����̳ʸ� ����� ������
	explicit MyTemplateSingleLinkedList(size_t count)
		:MyTemplateSingleLinkedList()
	{
		for (size_t i = 0; i < count; ++i)
		{
			push_front({});
		}
	}

	// ���� ������.
	MyTemplateSingleLinkedList(const MyTemplateSingleLinkedList& other)
		:MyTemplateSingleLinkedList()
	{
		auto inserted = before_begin();
		for (auto iter = other.begin(); iter != other.end(); iter = iter->Next)
		{
			inserted = insert_after(inserted, iter->Data);
		}
	}

	// �Ҵ� ������
	MyTemplateSingleLinkedList& operator=(const MyTemplateSingleLinkedList& rhs)
	{
		if (this == &rhs)
		{
			MyTemplateSingleLinkedList temp(rhs);
			std::swap(_head, temp._head);
			std::swap(_end, temp._end);
		}

		return *this;
	}

	// �Ҹ���
	~MyTemplateSingleLinkedList()
	{
		clear();
	}

	// ù ��° ��Ҹ� ��ȯ�Ѵ�.
	T& front() { return begin()->Data; }
	const T& front() const { return begin()->Data; }

	// ���� �� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* before_begin() { return _head; }
	const Node* before_begin() const { return _head; }

	// ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* begin() { return _head->Next; }
	const Node* begin() const { return _head->Next; }

	// �� ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* end() { return _end; }
	const Node* end() const { return _end; };

	// pos ������ value�� �����Ѵ�.
	// ���Ե� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	Node* insert_after(Node* pos, const T& value)
	{
		Node* newNode = new Node(value);

		newNode->Next = pos->Next;

		pos->Next = newNode;

		return newNode;
	}

	// pos ���� ��Ҹ� �����Ѵ�.
	// ������ ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	// �ƹ� ��ҵ� ������ end()�� ��ȯ�Ѵ�.
	Node* erase_after(Node* pos)
	{
		Node* removeNode = pos->Next;

		if (empty())
		{
			return end();
		}

		pos->Next = removeNode->Next;
		delete removeNode;
		removeNode = nullptr;

		return pos->Next;
	}

	// ���� ��ҿ� value�� �����Ѵ�.
	void            push_front(const T& value)
	{
		insert_after(before_begin(), value);
	}

	// ���� ��Ҹ� �����Ѵ�.
	void            pop_front()
	{
		erase_after(before_begin());
	}

	// �����̳ʰ� ������� �Ǵ��Ѵ�.
	bool            empty() const
	{
		return begin() == _end;
	}

	// �����̳ʸ� ���������.
	void            clear()
	{
		while (false == empty())
		{
			pop_front();
		}
	}

	bool            contains(const T& value) const
	{
		for (auto iter = begin(); iter != end(); iter = iter->Next)
		{
			if (iter->Data == value)
			{
				return true;
			}
		}

		return false;
	}

private:
	Node* _head = new Node();
	Node* _end = new Node();
};
