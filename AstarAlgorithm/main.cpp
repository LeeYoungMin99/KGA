#include <iostream>
#include <queue>
#include <vector>
#include <bitset>
#include <chrono>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#define START_X 4
#define START_Y 5
#define END_X   6
#define END_Y   5
#define MAP_SIZE_X 11
#define MAP_SIZE_Y 11

#define INF 1e9

using namespace std;
using namespace chrono;

struct Pos
{
	int X;
	int Y;

	bool operator<(const Pos& other) const { return (X < other.X) && (Y < other.Y); }
	bool operator==(const Pos& other) const { return X == other.X && Y == other.Y; }
	bool operator!=(const Pos& other) const { return !(*this == other); }
};

//void PrintMap()
//{
//	for (int r = 0; r < MAP_SIZE_Y; ++r)
//	{
//		for (int c = 0; c < MAP_SIZE_X; ++c)
//		{
//			if (map[r][c] == 0)
//				cout << " ";
//			else if (map[r][c] == 1)
//				cout << "S";
//			else if (map[r][c] == 2)
//				cout << "B";
//			else if (map[r][c] == 3)
//				cout << "E";
//			else if (map[r][c] == 4)
//				cout << "P";
//		}
//		cout << endl;
//	}
//}

float Euclidean(Pos a, Pos b)
{
	return sqrtf(pow(abs(a.X - b.X), 2) + pow(abs(a.Y - b.Y), 2));
}

int Manhattan(Pos a, Pos b)
{
	return abs(a.X - b.X) + abs(a.Y - b.Y);
}

#define DIA 1.4f
#define STR 1.0f

int dy[] = { -1, 1,0, 0 ,-1, 1,-1,1 };
int dx[] = { 0, 0,-1, 1 ,-1,-1, 1,1 };
float dg[] = { STR,STR,STR,STR,DIA,DIA,DIA,DIA };

void astar(Pos start, Pos end)
{
	int map[MAP_SIZE_X][MAP_SIZE_Y] = {
		{ 0,0,0,0,0, 0, 0,0,0,0,0 },
		{ 0,2,2,2,2, 0, 2,2,2,2,0 },
		{ 0,0,0,0,0, 2, 0,0,0,0,0 },
		{ 0,0,0,0,0, 2, 0,0,0,0,0 },
		{ 0,2,2,2,2, 0, 2,2,2,2,0 },

		{ 0,0,0,0,1, 2, 3,0,0,0,0 },

		{ 0,2,2,2,2, 0, 2,2,2,2,0 },
		{ 0,0,0,0,0, 2, 0,0,0,0,0 },
		{ 0,0,0,0,0, 2, 0,0,0,0,0 },
		{ 0,2,2,2,2, 0 ,2,2,2,2,0 },
		{ 0,0,0,0,0, 0, 0,0,0,0,0 }
	};

	vector<vector<float>> f;
	for (int i = 0; i < MAP_SIZE_Y; ++i)
		f.emplace_back(MAP_SIZE_X, INF);
	f[start.Y][start.X] = 0;

	vector<vector<float>> g;
	for (int i = 0; i < MAP_SIZE_Y; ++i)
		g.emplace_back(MAP_SIZE_X, 0);

	Pos path[MAP_SIZE_Y][MAP_SIZE_X] = {};
	path[start.Y][start.X] = start;

	priority_queue<pair<float, Pos>> pq;
	pq.emplace(0, start);

	unsigned char TLR = 0b11110101;
	unsigned char BLR = 0b11111010;
	unsigned char LTB = 0b11110011;
	unsigned char RTB = 0b11111100;
	unsigned char T = 0b01111111;
	unsigned char B = 0b10111111;
	unsigned char L = 0b11011111;
	unsigned char R = 0b11101111;
	unsigned char db[] = { T,B,L,R,TLR,BLR,LTB,RTB };
	unsigned char db2[] = { 0b10000000,0b01000000,0b00100000,0b00010000,0b00001000,0b00000100,0b00000010,0b00000001 };

	while (false == pq.empty())
	{
		float w = -pq.top().first;
		Pos pos = pq.top().second;
		pq.pop();

		if (pos == end)
			break;

		if (f[pos.Y][pos.X] < w)
			continue;

		unsigned char bit = 0b11111111;
		for (int i = 0; i < 4; ++i)
		{	// 2 == º®
			int Y = dy[i] + pos.Y;
			int X = dx[i] + pos.X;

			if (Y < 0 || Y >= MAP_SIZE_Y || X < 0 || X >= MAP_SIZE_X || map[Y][X] == 2)
			{
				bit &= db[i];
				bit &= db[i + 4];
			}
		}

		for (int i = 0; i < 8; ++i)
		{
			if ((bit & db2[i]) == db2[i])
			{
				int nx = dx[i] + pos.X;
				int ny = dy[i] + pos.Y;

				if (false == (map[ny][nx] == 0 || map[ny][nx] == 3))
					continue;

				float ng = Euclidean({ nx,ny }, pos) + g[pos.Y][pos.X];
				float nf = dg[i] + Euclidean({ nx,ny }, end) + g[pos.Y][pos.X];

				if (f[ny][nx] > nf)
				{
					f[ny][nx] = nf;
					g[ny][nx] = ng;
					path[ny][nx] = pos;

					pq.emplace(-f[ny][nx], Pos{ nx,ny });
				}
			}
		}
	}

	Pos curr = end;
	while (curr != start)
	{
		map[curr.Y][curr.X] = 4;

		curr = path[curr.Y][curr.X];
	}
}

void astar2(Pos start, Pos end)
{
	int map2[MAP_SIZE_X][MAP_SIZE_Y] = {
		{ 0,0,0,0,0, 0, 0,0,0,0,0 },
		{ 0,2,2,2,2, 0, 2,2,2,2,0 },
		{ 0,0,0,0,0, 2, 0,0,0,0,0 },
		{ 0,0,0,0,0, 2, 0,0,0,0,0 },
		{ 0,2,2,2,2, 0, 2,2,2,2,0 },

		{ 0,0,0,0,1, 2, 3,0,0,0,0 },

		{ 0,2,2,2,2, 0, 2,2,2,2,0 },
		{ 0,0,0,0,0, 2, 0,0,0,0,0 },
		{ 0,0,0,0,0, 2, 0,0,0,0,0 },
		{ 0,2,2,2,2, 0 ,2,2,2,2,0 },
		{ 0,0,0,0,0, 0, 0,0,0,0,0 }
	};

	vector<vector<float>> f;
	for (int i = 0; i < MAP_SIZE_Y; ++i)
		f.emplace_back(MAP_SIZE_X, INF);
	f[start.Y][start.X] = 0;

	vector<vector<float>> g;
	for (int i = 0; i < MAP_SIZE_Y; ++i)
		g.emplace_back(MAP_SIZE_X, 0);

	Pos path[MAP_SIZE_Y][MAP_SIZE_X] = {};
	path[start.Y][start.X] = start;

	priority_queue<pair<float, Pos>> pq;
	pq.emplace(0, start);

	while (false == pq.empty())
	{
		float w = -pq.top().first;
		Pos pos = pq.top().second;
		pq.pop();

		if (pos == end)
			break;

		if (f[pos.Y][pos.X] < w)
			continue;

		for (int i = 0; i < 8; ++i)
		{
			int nx = dx[i] + pos.X;
			int ny = dy[i] + pos.Y;

			if (ny < 0 || ny >= MAP_SIZE_Y || nx < 0 || nx >= MAP_SIZE_X)
				continue;

			if (false == (map2[ny][nx] == 0 || map2[ny][nx] == 3))
				continue;

			if ((i == 4 || i == 6) && map2[pos.Y - 1][pos.X] == 2)
				continue;
			else if ((i == 5 || i == 7) && map2[pos.Y + 1][pos.X] == 2)
				continue;
			else if ((i == 4 || i == 5) && map2[pos.Y][pos.X - 1] == 2)
				continue;
			else if ((i == 6 || i == 7) && map2[pos.Y][pos.X + 1] == 2)
				continue;

			float ng = Euclidean({ nx,ny }, pos) + g[pos.Y][pos.X];
			float nf = dg[i] + Euclidean({ nx,ny }, end) + g[pos.Y][pos.X];

			if (f[ny][nx] > nf)
			{
				f[ny][nx] = nf;
				g[ny][nx] = ng;
				path[ny][nx] = pos;

				pq.emplace(-f[ny][nx], Pos{ nx,ny });
			}
		}
	}

	Pos curr = end;
	while (curr != start)
	{
		map2[curr.Y][curr.X] = 4;

		curr = path[curr.Y][curr.X];
	}
}

int main()
{
	//PrintMap();

	puts("");

	auto start = timeGetTime();
	for (int i = 0; i < 100000; ++i)
		astar({ START_X, START_Y }, { END_X, END_Y });
	auto end = timeGetTime();

	auto start1 = timeGetTime();
	for (int i = 0; i < 100000; ++i)
		astar2({ START_X, START_Y }, { END_X, END_Y });
	auto end1 = timeGetTime();

	unsigned long bit = end - start;
	unsigned long normal = end1 - start1;

	cout << "   bit : " << bit << endl << endl;
	cout << "normal : " << normal << endl << endl;

	//PrintMap();
}
