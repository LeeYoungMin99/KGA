#pragma once
#include <array>
#include <iostream>

enum class EGraphType
{
	Matrix,
	List
};

template <EGraphType type, size_t N>
class MyGraph;

template <size_t N>
class MyGraph<EGraphType::Matrix, N>
{
public:
	// 두 정점이 인접한지 확인한다.
	bool        IsAdjacent(int start, int end)
	{
		if (_edges[start][end] != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// 차수를 구한다.
	int         GetDegree(int node)
	{
		int in = GetInDegree(node);
		int out = GetOutDegree(node);

		return in + out;
	}

	// 진입 차수를 구한다.
	int         GetInDegree(int node)
	{
		int count = 0;

		for (int i = 0; i < _edges.size(); ++i)
		{
			if (_edges[i][node])
			{
				++count;
			}
		}

		return count;
	}

	// 진출 차수를 구한다.
	int         GetOutDegree(int node)
	{
		int count = 0;

		for (size_t i = 0; i < _edges.size(); ++i)
		{
			if (_edges[node][i])
			{
				++count;
			}
		}

		return count;
	}

	// 간선을 추가한다.
	void        AddEdge(int start, int end, int weight = 1)
	{
		// start -> end로 연결
		_edges[start][end] = weight;
	}

	// 간선을 제거한다.
	void        DeleteEdge(int start, int end)
	{
		// start -> end의 간선 제거
		_edges[start][end] = 0;
	}

	// 출력한다.
	// 예시..
	// [ 0 1 0 0 0 ]
	// [ 0 0 1 0 0 ]
	// [ 0 0 0 0 1 ]
	// [ 0 1 0 0 0 ]
	// [ 0 0 0 0 0 ]
	void        Print()
	{
		for (size_t i = 0; i < _edges.size(); ++i)
		{
			cout << "[ ";
			for (size_t j = 0; j < _edges.size(); ++j)
			{
				cout << _edges[i][j] << ' ';
			}
			cout << "]\n";
		}
	}

private:
	array<array<int, N>, N>     _edges = {};
};

