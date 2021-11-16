#include <iostream>
//#include "MyMatrixGraph.h"
#include "MyListGraph.h"
#include <array>

using namespace std;

int main()
{
	//MyGraph<EGraphType::Matrix, 7> g;
	//
	//g.AddEdge(0, 1, 32);
	//g.AddEdge(0, 2, 38);
	//g.AddEdge(0, 3, 23);
	//g.AddEdge(0, 4, 12);
	//g.AddEdge(0, 5, 8);
	//
	//g.Print();
	//
	//// false
	//cout << boolalpha << g.IsAdjacent(0, 6) << endl;
	//
	//// 5
	//// 1
	//// 1
	//// 1
	//// 1
	//// 1
	//// 0
	//for (int i = 0; i < 7; ++i)
	//{
	//	cout << g.GetDegree(i) << endl;
	//}


	MyGraph<EGraphType::List, 7> g2;

	g2.AddEdge(0, 1, 32);
	g2.AddEdge(0, 2, 38);
	g2.AddEdge(0, 3, 23);
	g2.AddEdge(0, 4, 12);
	g2.AddEdge(0, 5, 8);

	g2.Print();

	cout << boolalpha << g2.IsAdjacent(0, 6) << endl;


	for (int i = 0; i < 7; ++i)
	{
		cout << g2.GetDegree(i) << endl;
	}

}


/*
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <queue>

int N, M, V;

using namespace std;

// �������
bool graph[1001][1001];

// ���� ����Ʈ
vector<int> graph2[1001];

// ���� ��Ŀ����� dfs
void dfs(int node)
{
	// 1. ������ �湮�ߴ��� ������־�� ��. => set �ڷᱸ�� ����ؾ���
	// 2. ������ �����Ѵ�. ���ÿ��� ���� ������ �־��ش�.
	//	  ������ ���� �湮�� ��尡 �����.
	// 3. ������ �������� �ݺ��Ѵ�. => ��� ������ �ݺ��� �� ���� �ݺ��Ѵ�.
	// 4. ���ÿ��� ������ �湮�� ������ �����´�.
	// 5. �̹� �湮�� ����� �ǳʶڴ�.
	// 6. ������ �湮�Ѵ�.
	// 7. ����� ���� �� �湮���� ���� ������ ���ÿ� �߰��Ѵ�.
	// 8. �湮�� ��带 ���ÿ� �߰��Ѵ�.
	// Set : �� ���ҵ��� �����ϰ� ����ִ� �ڷᱸ��
	std::set<int> visitedSet;
	// visited �ش� ������ �湮�ߴ����� ���ѿ���
	static bool isVisited[1001] = { false };

	// ���� �ʱ� ����
	stack<int> st;
	// ���� ������ �־��ش�.
	st.push(node);

	while (false == st.empty())
	{
		// ���ÿ��� ������ �湮�� ������ �����´�.
		int vertex = st.top();
		st.pop();

		if (visitedSet.end() != visitedSet.find(vertex))
		{
			continue;
		}

		//�湮�� ������ ǥ���Ѵ�
		isVisited[vertex] = true;
		visitedSet.insert(vertex);

		cout << vertex << " ";
		// ��� ��带 ��ȸ�ϸ鼭
		for (int i = 1; i <= N; ++i)
		{
			// �湮���� �ʰ� ����� ��常�� �湮�Ѵ�.
			//if(visitedSet.end() == visitedSet.find(i) && graph[vertex][i] == true)
			if (isVisited[i] == false && graph[vertex][i] == true)
			{
				// �湮�� ��带 ���ÿ� �߰��Ѵ�.
				st.push(i);
			}
		}
	}


}
// ���� ����Ʈ������ dfs
void dfs2(int node)
{
	// 1. �湮�� ������ ǥ���� �ڷᱸ���� �ʿ�
	static bool isVisited[1001] = { false };

	// 2. ���� ����
	stack<int> st;
	st.push(node);

	// 3. ��� ������ �湮�� ������ �ݺ��Ѵ�.
	while (false == st.empty())
	{
		// 4. ���ÿ��� ������ �湮�� ������ �����´�.
		int vertex = st.top();
		st.pop();

		// 5. �̹� �湮�� ����� �ǳʶڴ�.
		if (isVisited[vertex] == true)
		{
			continue;
		}

		// 6. ������ �湮�Ѵ�.
		isVisited[vertex] = true;
		cout << vertex << " ";

		// 7. ����� ���� �� �湮���� ���� ������ ���ÿ� �߰��Ѵ�.
		for (int e : graph2[vertex])
		{
			if (isVisited[e] == false)
			{
				// 8. �湮�� ��带 ���ÿ� �߰��Ѵ�.
				st.push(e);
			}
		}
	}
}

// ��ͷ� ������ dfs / ���� ��� ���
void dfsr(int node)
{
	// 1. �湮�� ������ ǥ���� Set ����
	static bool isVisited[1001] = { false };

	// 2. ���� ��带 �湫�Ѵ�.
	isVisited[node] = true;
	cout << node << " ";

	for (int i = 1; i <= N; ++i)
	{
		if (isVisited[i] == false && graph[node][i] == true)
		{
			dfsr(i);
		}
	}
}

// ��ͷ� ������ dfs / ���� ����Ʈ ���
void dfsr2(int node)
{
	// 1. �湮�� ������ ǥ���� Set ����
	static bool isVisited[1001] = { false };

	// 2. ���� ��带 �湮�Ѵ�.
	isVisited[node] = true;
	cout << node << " ";

	for (int e : graph2[node])
	{
		if (isVisited[e] == false)
		{
			dfsr2(e);
		}
	}
}

void bfs(int node)
{
	static bool isVisited[1001] = { false };

	queue<int> qu;
	qu.push(node);

	// 3. ť�� �������� �ݺ��Ѵ�. => ��� ������ �ݺ��� �� ���� �ݺ��Ѵ�.
	while (false == qu.empty())
	{
		// 4. ť���� ������ �湮�� ������ �����´�.

		int vertex = qu.front();
		qu.pop();

		// 5. �̹� �湮�� ����� �ǳʶڴ�.
		if (true == isVisited[vertex])
		{
			continue;
		}

		// 6. ������ �湮�Ѵ�.
		isVisited[vertex] = true;
		cout << vertex << " ";


		// 7. ����� ���� �� �湮���� ���� ������ ť�� �߰��Ѵ�.
		for (int i = 1; i <= N; ++i)
		{
			if (isVisited[i] == false && graph[vertex][i] == true)
			{
				// 8. �湮�� ��带 ť�� �߰��Ѵ�.
				qu.push(i);
			}
		}
	}

}

void bfs2(int node)
{
	// 1. �湮�� ������ ǥ���� �ڷᱸ���� �ʿ�
	static bool isVisited[1001] = { false };

	// 2. ���� ����
	queue<int> qu;
	qu.push(node);

	// 3. ��� ������ �湮�� ������ �ݺ��Ѵ�.
	while (false == qu.empty())
	{
		// 4. ���ÿ��� ������ �湮�� ������ �����´�.
		int vertex = qu.front();
		qu.pop();

		// 5. �̹� �湮�� ����� �ǳʶڴ�.
		if (isVisited[vertex] == true)
		{
			continue;
		}

		// 6. ������ �湮�Ѵ�.
		isVisited[vertex] = true;
		cout << vertex << " ";

		// 7. ����� ���� �� �湮���� ���� ������ ���ÿ� �߰��Ѵ�.
		for (int e : graph2[vertex])
		{
			if (isVisited[e] == false)
			{
				// 8. �湮�� ��带 ���ÿ� �߰��Ѵ�.
				qu.push(e);
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	cin >> N >> M >> V;

	for (int i = 0; i < M; ++i)
	{
		int s, e;
		cin >> s >> e;

		// ������ ���� ���
		graph[s][e] = true;
		graph[e][s] = true;

		// -------------------

		// ������ ���� ����Ʈ
		graph2[s].push_back(e);
		graph2[e].push_back(s);
	}

	for (int i = 1; i <= N; ++i)
	{
		sort(graph2[i].begin(), graph2[i].end());
	}

	dfs2(V);
	bfs2(V);
}
*/

/*
#include <iostream>
#include <vector>
#include <algorithm>

int T, M, N, K;

using namespace std;

char map[50][50];
bool isVisited[50][50] = { false };
int Count;

void dfs(int r, int c)
{
	isVisited[r][c] = true;

	//����
	if ((r - 1) >= 0 && isVisited[r - 1][c] == false && map[r - 1][c] == '1')
		dfs(r - 1, c);
	//�Ʒ���
	if ((r + 1) < N && isVisited[r + 1][c] == false && map[r + 1][c] == '1')
		dfs(r + 1, c);
	//����
	if ((c - 1) >= 0 && isVisited[r][c - 1] == false && map[r][c - 1] == '1')
		dfs(r, c - 1);
	//������
	if ((c + 1) < N && isVisited[r][c + 1] == false && map[r][c + 1] == '1')
		dfs(r, c + 1);

}

int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	cin >> T;

	for (int i = 0; i < T; ++i)
	{
		cin >> M >> N >> K;


		Count = 0;
		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < M; ++c)
			{
				map[r][c] = '0';
				isVisited[r][c] = false;
			}
		}

		for (int j = 0; j < K; ++j)
		{
			int s, e;
			cin >> s >> e;

			map[s][e] = '1';
		}


		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < M; ++c)
			{
				if (isVisited[r][c] == false && map[r][c] == '1')
				{
					dfs(r, c);

					++Count;
				}
			}
		}

		cout << Count << "\n";
	}


}
*/
