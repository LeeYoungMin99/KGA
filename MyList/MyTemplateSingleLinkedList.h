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
	// 기본 생성자
	MyTemplateSingleLinkedList()
	{
		_head->Next = _end;
	}

	// count만큼의 요소를 갖고 있는 컨테이너를 만드는 생성자
	explicit MyTemplateSingleLinkedList(size_t count)
		:MyTemplateSingleLinkedList()
	{
		for (size_t i = 0; i < count; ++i)
		{
			push_front({});
		}
	}

	// 복사 생성자.
	MyTemplateSingleLinkedList(const MyTemplateSingleLinkedList& other)
		:MyTemplateSingleLinkedList()
	{
		auto inserted = before_begin();
		for (auto iter = other.begin(); iter != other.end(); iter = iter->Next)
		{
			inserted = insert_after(inserted, iter->Data);
		}
	}

	// 할당 연산자
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

	// 소멸자
	~MyTemplateSingleLinkedList()
	{
		clear();
	}

	// 첫 번째 요소를 반환한다.
	T& front() { return begin()->Data; }
	const T& front() const { return begin()->Data; }

	// 시작 전 요소를 가리키는 반복자를 반환한다.
	Node* before_begin() { return _head; }
	const Node* before_begin() const { return _head; }

	// 시작 요소를 가리키는 반복자를 반환한다.
	Node* begin() { return _head->Next; }
	const Node* begin() const { return _head->Next; }

	// 끝 다음 요소를 가리키는 반복자를 반환한다.
	Node* end() { return _end; }
	const Node* end() const { return _end; };

	// pos 다음에 value를 삽입한다.
	// 삽입된 요소를 가리키는 반복자를 반환한다.
	Node* insert_after(Node* pos, const T& value)
	{
		Node* newNode = new Node(value);

		newNode->Next = pos->Next;

		pos->Next = newNode;

		return newNode;
	}

	// pos 다음 요소를 삭제한다.
	// 삭제된 요소를 가리키는 반복자를 반환한다.
	// 아무 요소도 없으면 end()를 반환한다.
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

	// 시작 요소에 value를 삽입한다.
	void            push_front(const T& value)
	{
		insert_after(before_begin(), value);
	}

	// 시작 요소를 제거한다.
	void            pop_front()
	{
		erase_after(before_begin());
	}

	// 컨테이너가 비었는지 판단한다.
	bool            empty() const
	{
		return begin() == _end;
	}

	// 컨테이너를 비워버린다.
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
