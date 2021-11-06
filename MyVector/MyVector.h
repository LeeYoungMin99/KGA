#pragma once

#include <stdexcept>	// std::out_of_range
#include <algorithm>	// swap

class MyVector
{
public:
	// 기본 생성자
	MyVector() = default;

	// count만큼 공간이 할당된 생성자
	explicit MyVector(size_t count)
		:_container{ new int[count] }, _size{ count }, _capacity{ count }
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_container[i] = 0;
		}
	}

	// 복사 생성자. 깊은 복사(deep copy)가 이뤄져야 한다.
	MyVector(const MyVector& other)
		:_container{ new int[other._capacity] }, _size{ other._size }, _capacity{ other._capacity }
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_container[i] = other._container[i];
		}
	}

	// 할당 연산자. 깊은 복사(deep copy)가 이뤄져야 한다.
	MyVector& operator=(const MyVector& rhs)
	{
		if (this == &rhs)
		{
			MyVector temp(rhs);
			std::swap(_container, temp._container);
			std::swap(_size, temp._size);
			std::swap(_capacity, temp._capacity);
		}

		return *this;
	}

	// 소멸자
	~MyVector()
	{
		clear();
		_capacity = 0;
	}

	// 첫 번째 요소를 가리키는 반복자를 반환한다.
	int* begin() { return _container; }
	const int* begin() const { return _container; }

	// 마지막 요소의 다음 번째를 가리키는 반복자를 반환한다.
	int* end() { return _container + _size; }
	const int* end() const { return _container + _size; }

	// 컨테이너가 비었는지 검사한다.
	bool empty() const { return _size == 0; }

	// 원소의 개수를 반환한다.
	size_t size() const { return _size; }

	// 현재 할당된 공간의 크기를 반환한다.
	size_t capacity() const { return _capacity; }

	// pos에 위치한 원소의 참조를 반환한다. 만약 pos가 범위에서 벗어나면 std::out_of_range 예외가 던져진다.
	int& at(size_t pos)
	{
		if (pos >= _size)
		{
			throw std::out_of_range("범위를 벗어난 곳 참조");
		}

		return _container[pos];
	}
	const int& at(size_t pos) const
	{
		if (pos >= _size)
		{
			throw std::out_of_range("범위를 벗어난 곳 참조");
		}

		return _container[pos];
	}

	// pos에 위치한 원소의 참조를 반환한다.
	int& operator[](size_t pos)
	{
		return _container[pos];
	}
	const int& operator[](size_t pos) const
	{
		return _container[pos];
	}

	// 컨테이너의 첫 번째 원소의 참조를 반환한다.
	int& front()
	{
		return _container[0];
	}
	const int& front() const
	{
		return _container[0];
	}

	// 컨테이너의 마지막 원소의 참조를 반환한다.
	int& back() { return _container[_size - 1]; }
	const int& back() const { return _container[_size - 1]; }

	// 컨테이너를 비운다.
	void                clear()
	{
		delete[] _container;
		_container = nullptr;

		_size = 0;
	}

	// pos 이전 위치에 value를 삽입한다.
	// value가 삽입된 곳을 가리키는 포인터를 반환한다.
	int* insert(int* pos, int value)
	{
		int dist = pos - begin();
		if (_capacity == 0)
		{
			reserve(1);

			pos = begin() + dist;
		}

		if (_capacity == _size)
		{
			reserve(_capacity * 2);

			pos = begin() + dist;
		}

		for (int* iter = end(); iter != pos; --iter)
		{
			*iter = *(iter - 1);
		}

		*pos = value;
		++_size;

		return pos;
	}

	// pos에 위치한 원소를 지운다.
	// 삭제된 요소의 다음 포인터를 반환한다.
	int* erase(int* pos)
	{
		if (empty())
		{
			return end();
		}

		int* last = end() - 1;

		if (pos == last)
		{
			--_size;

			return end();
		}

		for (int* iter = pos; iter != end(); ++iter)
		{
			*iter = *(iter + 1);
		}

		--_size;

		return pos;
	}

	// 컨테이너의 맨 끝에 원소를 추가한다.
	void                push_back(int value)
	{
		insert(end(), value);
	}

	// 컨테이너의 마지막 원소를 삭제한다.
	void                pop_back()
	{
		erase(end());
	}

	// value가 존재하는지 검사한다.
	bool                contains(int value)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_container[i] == value)
			{
				return true;
			}
		}

		return false;
	}

	// 컨테이너의 용량을 newCapacity보다 같거나 크게 늘린다.
	// newCapacity > _capacity라면 새로운 메모리를 할당하고,
	// 그렇지 않다면 아무 동작도 수행하지 않는다.
	void                reserve(size_t newCapacity)
	{
		// 예외처리
		if (_capacity >= newCapacity)
		{
			return;
		}

		// 새로운 메모리 할당
		int* newContainer = new int[newCapacity];

		// 컨테이너 복사
		for (size_t i = 0; i < _size; ++i)
		{
			newContainer[i] = _container[i];
		}

		delete[] _container;

		_container = newContainer;
		_capacity = newCapacity;
	}
private:
	int* _container = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};
