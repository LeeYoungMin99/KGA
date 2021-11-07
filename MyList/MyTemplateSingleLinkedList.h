#pragma once

template <typename T>
class MyTemplateSingleLinkedList
{
	struct Node
	{
		Node() = default;
		Node(const T& data/* = {}*/, Node* next = nullptr)
			:Data{ data }, Next{ next }	{ }
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		~Node()
		{
			Next = nullptr;
		}

		T     Data/* = {}*/;
		Node* Next = nullptr;
	};
public:
	class const_iterator
	{
	public:
		const_iterator(Node* _p = nullptr)
			:_p{ _p } {}
		~const_iterator() { _p = nullptr; }

		const T& operator*() { return _p->Data; }
		const T* operator->() { return &_p->Data; }
		const_iterator& operator++() { _p = _p->Next; return *this; }
		const_iterator operator++(int)
		{
			auto temp = *this;
			_p = _p->Next;
			return temp;
		}

		bool                operator==(const const_iterator& rhs) const { return _p == rhs._p; }
		bool                operator!=(const const_iterator& rhs) const { return !(*this == rhs); }
		bool                operator==(nullptr_t p) const { return _p == nullptr; }
		bool                operator!=(nullptr_t p) const { return _p != nullptr; }

		Node* _p = nullptr;
	};

	class iterator : public const_iterator
	{
	public:
		using const_iterator::const_iterator;

		T& operator*() { return const_cast<T&>(const_iterator::operator*()); }
		T* operator->() { return const_cast<T*>(const_iterator::operator->()); }
		iterator& operator++() { const_iterator::operator++(); return *this; }
		iterator      operator++(int)
		{
			iterator temp = *this;
			const_iterator::operator++();

			return temp;
		}
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
		for (auto iter = other.begin(); iter != other.end(); ++iter)
		{
			inserted = insert_after(inserted, *iter);
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
	T& front() { return *begin(); }
	const T& front() const { return *begin(); }

	// 시작 전 요소를 가리키는 반복자를 반환한다.
	iterator before_begin() { return _head; }
	const_iterator before_begin() const { return _head; }

	// 시작 요소를 가리키는 반복자를 반환한다.
	iterator begin() { return _head->Next; }
	const_iterator begin() const { return _head->Next; }

	// 끝 다음 요소를 가리키는 반복자를 반환한다.
	iterator end() { return _end; }
	const_iterator end() const { return _end; };

	// pos 다음에 value를 삽입한다.
	// 삽입된 요소를 가리키는 반복자를 반환한다.
	iterator insert_after(iterator pos, const T& value)
	{
		Node* where = pos._p;
		Node* newNode = new Node(value);

		newNode->Next = where->Next;

		where->Next = newNode;

		return newNode;
	}

	// pos 다음 요소를 삭제한다.
	// 삭제된 요소를 가리키는 반복자를 반환한다.
	// 아무 요소도 없으면 end()를 반환한다.
	iterator erase_after(iterator pos)
	{
		Node* where = pos._p;
		Node* removeNode = where->Next;

		if (empty())
		{
			return end();
		}

		where->Next = removeNode->Next;
		delete removeNode;
		removeNode = nullptr;

		return where->Next;
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
		for (auto iter = begin(); iter != end(); ++iter)
		{
			if (*iter == value)
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
