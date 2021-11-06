#pragma once

#include <stdexcept>	// std::out_of_range
#include <algorithm>	// swap

template <typename T>
class MyTemplateVector
{
public:
	// �⺻ ������
	MyTemplateVector() = default;

	// count��ŭ ������ �Ҵ�� ������
	explicit MyTemplateVector(size_t count)
		:_container{ new T[count] }, _size{ count }, _capacity{ count }
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_container[i] = {};
		}
	}

	// ���� ������. ���� ����(deep copy)�� �̷����� �Ѵ�.
	MyTemplateVector(const MyTemplateVector& other)
		:_container{ new T[other._capacity] }, _size{ other._size }, _capacity{ other._capacity }
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_container[i] = other._container[i];
		}
	}

	// �Ҵ� ������. ���� ����(deep copy)�� �̷����� �Ѵ�.
	MyTemplateVector& operator=(const MyTemplateVector& rhs)
	{
		if (this == &rhs)
		{
			MyTemplateVector temp(rhs);
			std::swap(_container, temp._container);
			std::swap(_size, temp._size);
			std::swap(_capacity, temp._capacity);
		}

		return *this;
	}

	// �Ҹ���
	~MyTemplateVector()
	{
		clear();
		_capacity = 0;
	}

	// ù ��° ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	T* begin() { return _container; }
	const T* begin() const { return _container; }

	// ������ ����� ���� ��°�� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
	T* end() { return _container + _size; }
	const T* end() const { return _container + _size; }

	// �����̳ʰ� ������� �˻��Ѵ�.
	bool empty() const { return _size == 0; }

	// ������ ������ ��ȯ�Ѵ�.
	size_t size() const { return _size; }

	// ���� �Ҵ�� ������ ũ�⸦ ��ȯ�Ѵ�.
	size_t capacity() const { return _capacity; }

	// pos�� ��ġ�� ������ ������ ��ȯ�Ѵ�. ���� pos�� �������� ����� std::out_of_range ���ܰ� ��������.
	T& at(size_t pos)
	{
		if (pos >= _size)
		{
			throw std::out_of_range("������ ��� �� ����");
		}

		return _container[pos];
	}
	const T& at(size_t pos) const
	{
		if (pos >= _size)
		{
			throw std::out_of_range("������ ��� �� ����");
		}

		return _container[pos];
	}

	// pos�� ��ġ�� ������ ������ ��ȯ�Ѵ�.
	T& operator[](size_t pos)
	{
		return _container[pos];
	}
	const T& operator[](size_t pos) const
	{
		return _container[pos];
	}

	// �����̳��� ù ��° ������ ������ ��ȯ�Ѵ�.
	T& front()
	{
		return _container[0];
	}
	const T& front() const
	{
		return _container[0];
	}

	// �����̳��� ������ ������ ������ ��ȯ�Ѵ�.
	T& back() { return _container[_size - 1]; }
	const T& back() const { return _container[_size - 1]; }

	// �����̳ʸ� ����.
	void clear()
	{
		delete[] _container;
		_container = nullptr;

		_size = 0;
	}

	// pos ���� ��ġ�� value�� �����Ѵ�.
	// value�� ���Ե� ���� ����Ű�� �����͸� ��ȯ�Ѵ�.
	T* insert(T* pos, const T& value)
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

		for (T* iter = end(); iter != pos; --iter)
		{
			*iter = *(iter - 1);
		}

		*pos = value;
		++_size;

		return pos;
	}

	// pos�� ��ġ�� ���Ҹ� �����.
	// ������ ����� ���� �����͸� ��ȯ�Ѵ�.
	T* erase(T* pos)
	{
		if (empty())
		{
			return end();
		}

		T* last = end() - 1;

		if (pos == last)
		{
			--_size;

			return end();
		}

		for (T* iter = pos; iter != end(); ++iter)
		{
			*iter = *(iter + 1);
		}

		--_size;

		return pos;
	}

	// �����̳��� �� ���� ���Ҹ� �߰��Ѵ�.
	void                push_back(const T& value)
	{
		insert(end(), value);
	}

	// �����̳��� ������ ���Ҹ� �����Ѵ�.
	void                pop_back()
	{
		erase(end());
	}

	// value�� �����ϴ��� �˻��Ѵ�.
	bool                contains(const T& value)
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
		T* newContainer = new T[newCapacity];

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
	T* _container = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};