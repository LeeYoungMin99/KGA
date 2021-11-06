#pragma once

#include <stdexcept>	// std::out_of_range
#include <algorithm>	// swap

class MyVector
{
public:
	// �⺻ ������
	MyVector() = default;

	// count��ŭ ������ �Ҵ�� ������
	explicit MyVector(size_t count)
		:_container{ new int[count] }, _size{ count }, _capacity{ count }
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_container[i] = 0;
		}
	}

	// ���� ������. ���� ����(deep copy)�� �̷����� �Ѵ�.
	MyVector(const MyVector& other)
		:_container{ new int[other._capacity] }, _size{ other._size }, _capacity{ other._capacity }
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_container[i] = other._container[i];
		}
	}

	// �Ҵ� ������. ���� ����(deep copy)�� �̷����� �Ѵ�.
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

	// �Ҹ���
	~MyVector()
	{
		clear();
		_capacity = 0;
	}

	// ù ��° ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	int* begin() { return _container; }
	const int* begin() const { return _container; }

	// ������ ����� ���� ��°�� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	int* end() { return _container + _size; }
	const int* end() const { return _container + _size; }

	// �����̳ʰ� ������� �˻��Ѵ�.
	bool empty() const { return _size == 0; }

	// ������ ������ ��ȯ�Ѵ�.
	size_t size() const { return _size; }

	// ���� �Ҵ�� ������ ũ�⸦ ��ȯ�Ѵ�.
	size_t capacity() const { return _capacity; }

	// pos�� ��ġ�� ������ ������ ��ȯ�Ѵ�. ���� pos�� �������� ����� std::out_of_range ���ܰ� ��������.
	int& at(size_t pos)
	{
		if (pos >= _size)
		{
			throw std::out_of_range("������ ��� �� ����");
		}

		return _container[pos];
	}
	const int& at(size_t pos) const
	{
		if (pos >= _size)
		{
			throw std::out_of_range("������ ��� �� ����");
		}

		return _container[pos];
	}

	// pos�� ��ġ�� ������ ������ ��ȯ�Ѵ�.
	int& operator[](size_t pos)
	{
		return _container[pos];
	}
	const int& operator[](size_t pos) const
	{
		return _container[pos];
	}

	// �����̳��� ù ��° ������ ������ ��ȯ�Ѵ�.
	int& front()
	{
		return _container[0];
	}
	const int& front() const
	{
		return _container[0];
	}

	// �����̳��� ������ ������ ������ ��ȯ�Ѵ�.
	int& back() { return _container[_size - 1]; }
	const int& back() const { return _container[_size - 1]; }

	// �����̳ʸ� ����.
	void                clear()
	{
		delete[] _container;
		_container = nullptr;

		_size = 0;
	}

	// pos ���� ��ġ�� value�� �����Ѵ�.
	// value�� ���Ե� ���� ����Ű�� �����͸� ��ȯ�Ѵ�.
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

	// pos�� ��ġ�� ���Ҹ� �����.
	// ������ ����� ���� �����͸� ��ȯ�Ѵ�.
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

	// �����̳��� �� ���� ���Ҹ� �߰��Ѵ�.
	void                push_back(int value)
	{
		insert(end(), value);
	}

	// �����̳��� ������ ���Ҹ� �����Ѵ�.
	void                pop_back()
	{
		erase(end());
	}

	// value�� �����ϴ��� �˻��Ѵ�.
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

	// �����̳��� �뷮�� newCapacity���� ���ų� ũ�� �ø���.
	// newCapacity > _capacity��� ���ο� �޸𸮸� �Ҵ��ϰ�,
	// �׷��� �ʴٸ� �ƹ� ���۵� �������� �ʴ´�.
	void                reserve(size_t newCapacity)
	{
		// ����ó��
		if (_capacity >= newCapacity)
		{
			return;
		}

		// ���ο� �޸� �Ҵ�
		int* newContainer = new int[newCapacity];

		// �����̳� ����
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
