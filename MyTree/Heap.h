#pragma once

#include <vector>
class Heap
{
public:
	Heap() = default;
	~Heap() = default;

	// 최대 원소를 반환한다.
	const int& top() const { return _container.front(); }

	// 힙이 비어있는지 확인한다.
	bool empty() const { return _container.empty(); }

	// 힙의 크기를 반환한다.
	size_t size() const { return _container.size(); }

	// 힙에 원소를 삽입한다.
	void push(int value)
	{
		// 마지막 노드에 값을 추가한다.
		_container.push_back(value);

		// 부모와 비교하면서 위치를 바꿔준다.
		// 힙의 불변성을 만족할때 까지
		// 부모노드가 항상 자식노드보다 커야한다.

		size_t curr = _container.size();
		size_t parent = curr / 2;

		while (curr > 0 && _container[parent] < _container[curr-1])
		{
			std::swap(_container[parent], _container[curr-1]);

			curr = parent;
			parent = curr / 2;
		}
	}

	// 힙에서 원소를 삭제한다.
	void pop()
	{
		if (empty())
			return;
		// 가장 마지막 노드를 루트 노드로 만들어준다.
		_container[0] = _container[size() - 1];
		_container.pop_back();

		// 힙의 불변성을 만족할 때까지 자식 노드와 바꿔준다.
		size_t curr = 1;
		size_t child = 2;

		while (child < _container.size())
		{
			if (child + 1 < _container.size() && _container[child] < _container[child + 1])
			{
				// 오른쪽 자식과 비교한다.
				++child;
			}

			// 이미 힙의 불변성을 만족한다면 중단한다.
			if (_container[curr] >= _container[child])
			{
				break;
			}

			std::swap(_container[curr], _container[child]);
			curr = child;
			child = curr * 2;
		}
	}

private:

public:
private:
	std::vector<int>	_container;
};