#pragma once

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
	explicit MyDoubleLinkedList(size_t count);

	// ���� ������.
	MyDoubleLinkedList(const MyDoubleLinkedList& other);

	// �Ҵ� ������
	MyDoubleLinkedList& operator=(const MyDoubleLinkedList& rhs);

	// �Ҹ���
	~MyDoubleLinkedList();

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

	// pos ���� ��Ҹ� �����Ѵ�.
	// ������ ����� ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	// �ƹ� ��ҵ� ������ end()�� ��ȯ�Ѵ�.
	Node* erase(Node* pos)
	{
		Node* removed = pos->Next;

	}

	// ���ۿ� value�� �����Ѵ�.
	void            push_front(int value);

	// ���� value�� �����Ѵ�.
	void            push_back(int value);

	// ���� ��Ҹ� �����Ѵ�.
	void            pop_front();

	// �� ��Ҹ� �����Ѵ�.
	void            pop_back();

	// �����̳ʰ� ������� �Ǵ��Ѵ�.
	bool            empty() const { return _size == 0; }

	// ����Ʈ �ȿ� �ִ� ����� ������ ��ȯ�Ѵ�.
	size_t          size() const { return _size; };

	// �����̳ʸ� ���������.
	void            clear();

	// �ش� value�� �ִ��� üũ�Ѵ�.
	bool            contains(int value) const;
private:
	Node* _end = new Node;
	Node* _head = new Node;
	size_t	_size = 0;
};

