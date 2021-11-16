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

// 인접행렬
bool graph[1001][1001];

// 인접 리스트
vector<int> graph2[1001];

// 인접 행렬에서의 dfs
void dfs(int node)
{
	// 1. 정점을 방문했는지 기록해주어야 함. => set 자료구조 사용해야함
	// 2. 스택을 구성한다. 스택에는 시작 정점을 넣어준다.
	//	  스택은 다음 방문할 노드가 저장됨.
	// 3. 스택이 빌때까지 반복한다. => 모든 정점을 반복할 때 까지 반복한다.
	// 4. 스택에서 다음에 방문할 정점을 가져온다.
	// 5. 이미 방문한 노드라면 건너뛴다.
	// 6. 정점을 방문한다.
	// 7. 연결된 정점 중 방문하지 않은 정점을 스택에 추가한다.
	// 8. 방문할 노드를 스택에 추가한다.
	// Set : 각 원소들이 유일하게 들어있는 자료구조
	std::set<int> visitedSet;
	// visited 해당 정점을 방문했는지에 대한여부
	static bool isVisited[1001] = { false };

	// 스택 초기 구성
	stack<int> st;
	// 시장 정점을 넣어준다.
	st.push(node);

	while (false == st.empty())
	{
		// 스택에서 다음에 방문할 정점을 가져온다.
		int vertex = st.top();
		st.pop();

		if (visitedSet.end() != visitedSet.find(vertex))
		{
			continue;
		}

		//방문한 정점을 표기한다
		isVisited[vertex] = true;
		visitedSet.insert(vertex);

		cout << vertex << " ";
		// 모든 노드를 순회하면서
		for (int i = 1; i <= N; ++i)
		{
			// 방문하지 않고 연결된 노드만을 방문한다.
			//if(visitedSet.end() == visitedSet.find(i) && graph[vertex][i] == true)
			if (isVisited[i] == false && graph[vertex][i] == true)
			{
				// 방문할 노드를 스택에 추가한다.
				st.push(i);
			}
		}
	}


}
// 인접 리스트에서의 dfs
void dfs2(int node)
{
	// 1. 방문할 정점을 표기할 자료구조가 필요
	static bool isVisited[1001] = { false };

	// 2. 스택 구성
	stack<int> st;
	st.push(node);

	// 3. 모든 정점을 방문할 때까지 반복한다.
	while (false == st.empty())
	{
		// 4. 스택에서 다음에 방문할 정점을 가져온다.
		int vertex = st.top();
		st.pop();

		// 5. 이미 방문한 노드라면 건너뛴다.
		if (isVisited[vertex] == true)
		{
			continue;
		}

		// 6. 정점을 방문한다.
		isVisited[vertex] = true;
		cout << vertex << " ";

		// 7. 연결된 정점 중 방문하지 않은 정점을 스택에 추가한다.
		for (int e : graph2[vertex])
		{
			if (isVisited[e] == false)
			{
				// 8. 방문할 노드를 스택에 추가한다.
				st.push(e);
			}
		}
	}
}

// 재귀로 구현한 dfs / 인접 행렬 사용
void dfsr(int node)
{
	// 1. 방문한 정점을 표기할 Set 정의
	static bool isVisited[1001] = { false };

	// 2. 현재 노드를 방무한다.
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

// 재귀로 구현한 dfs / 인접 리스트 사용
void dfsr2(int node)
{
	// 1. 방문한 정점을 표기할 Set 정의
	static bool isVisited[1001] = { false };

	// 2. 현재 노드를 방문한다.
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

	// 3. 큐이 빌때까지 반복한다. => 모든 정점을 반복할 때 까지 반복한다.
	while (false == qu.empty())
	{
		// 4. 큐에서 다음에 방문할 정점을 가져온다.

		int vertex = qu.front();
		qu.pop();

		// 5. 이미 방문한 노드라면 건너뛴다.
		if (true == isVisited[vertex])
		{
			continue;
		}

		// 6. 정점을 방문한다.
		isVisited[vertex] = true;
		cout << vertex << " ";


		// 7. 연결된 정점 중 방문하지 않은 정점을 큐에 추가한다.
		for (int i = 1; i <= N; ++i)
		{
			if (isVisited[i] == false && graph[vertex][i] == true)
			{
				// 8. 방문할 노드를 큐에 추가한다.
				qu.push(i);
			}
		}
	}

}

void bfs2(int node)
{
	// 1. 방문할 정점을 표기할 자료구조가 필요
	static bool isVisited[1001] = { false };

	// 2. 스택 구성
	queue<int> qu;
	qu.push(node);

	// 3. 모든 정점을 방문할 때까지 반복한다.
	while (false == qu.empty())
	{
		// 4. 스택에서 다음에 방문할 정점을 가져온다.
		int vertex = qu.front();
		qu.pop();

		// 5. 이미 방문한 노드라면 건너뛴다.
		if (isVisited[vertex] == true)
		{
			continue;
		}

		// 6. 정점을 방문한다.
		isVisited[vertex] = true;
		cout << vertex << " ";

		// 7. 연결된 정점 중 방문하지 않은 정점을 스택에 추가한다.
		for (int e : graph2[vertex])
		{
			if (isVisited[e] == false)
			{
				// 8. 방문할 노드를 스택에 추가한다.
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

		// 무방향 인접 행렬
		graph[s][e] = true;
		graph[e][s] = true;

		// -------------------

		// 무방향 인접 리스트
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

	//위쪽
	if ((r - 1) >= 0 && isVisited[r - 1][c] == false && map[r - 1][c] == '1')
		dfs(r - 1, c);
	//아래쪽
	if ((r + 1) < N && isVisited[r + 1][c] == false && map[r + 1][c] == '1')
		dfs(r + 1, c);
	//왼쪽
	if ((c - 1) >= 0 && isVisited[r][c - 1] == false && map[r][c - 1] == '1')
		dfs(r, c - 1);
	//오른쪽
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
