#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int graph[7][7] = {
    {   0,   7, INF, INF,   3,  10, INF },
    {   7,   0,   4,  10,   2,   6, INF },
    { INF,   4,   0,   2, INF, INF, INF },
    { INF,  10,   2,   0,  11,   9,   4 },
    {   3,   2, INF,  11,   0, INF,   5 },
    {  10,   6, INF,   9, INF,   0, INF },
    { INF, INF, INF,   4,   5, INF,   0 }
};

vector<vector<int>> GetShortestPath()
{
    // distance 인접 행렬 만들기
    // distance[i][j]는 i 정점에서 j 정점까지의 최단 경로다.
    vector<vector<int>> dist;
    for (int i = 0; i < 7; ++i)
        dist.emplace_back(graph[i], graph[i] + 7);

    // 모든 정점의 최단 경로를 구할 때까지 반복한다.
    for (int via = 0; via < 7; ++via) // 경유 정점
    {
        for (int from = 0; from < 7; ++from) // 시작 정점
        {
            for (int to = 0; to < 7; ++to) // 도착 정점
            {
                dist[from][to] = min(dist[from][to], dist[from][via] + dist[via][to]);
            }
        }
    }

    return dist;
}

int main()
{
    auto dist = GetShortestPath();

    for (const auto& d : dist)
    {
        cout << "[ ";
        for (const auto& elem : d)
        {
            cout << elem << ' ';
        }
        cout << "]\n";
    }
}

