#include <iostream>
#include <set>
#include "Set.h"
#include <queue>
#include "Heap.h"

int main()
{
	set<int> set = { 8,3,2,5,4,10,14,11,16 };

	for (int data : set)
	{
		cout << data << ' ';
	}
	cout << endl;

	if (set.end() != set.find(2))
	{
		cout << "Found 2\n";
	}

	if (set.end() == set.find(12))
	{
		cout << "Not Found 12\n";
	}

	// 9
	cout << "Size : " << set.size() << endl;

	// false
	cout << boolalpha << set.empty() << endl;

	auto iter = set.begin(); //2
	++iter; //3
	++iter; //4

	set.erase(iter); //

	// 8
	cout << "Size : " << set.size() << endl;

	if (set.end() == set.find(4))
	{
		cout << "Not Found 12\n";
	}

	set.clear();

	cout << set.empty() << endl;

	cout << "-----------------------------------------------------" << endl;

	Set<int> mySet;

	mySet.insert(8);
	mySet.insert(3);
	mySet.insert(2);
	mySet.insert(5);
	mySet.insert(4);
	mySet.insert(10);
	mySet.insert(14);
	mySet.insert(11);
	mySet.insert(16);

	if (mySet.find(2))
	{
		cout << "Found 2\n";
	}

	if (mySet.find(12) == nullptr)
	{
		cout << "NotFound 12\n";
	}

	// 9
	cout << "Size : " << mySet.size() << endl;

	mySet.erase(4);

	// 8
	cout << "Size : " << mySet.size() << endl;

	if (mySet.find(4) == nullptr)
	{
		cout << "Not Found 4\n";
	}

	// 8 3 2 5 10 14 11 16
	mySet.traverseByPreorder();
	cout << endl;

	// 2 5 3 11 16 14 10 8
	mySet.traverseByInorder();
	cout << endl;

	// 8 3 2 5 10 14 11 16
	mySet.traverseByPostorder();
	cout << endl;

	// 8 3 10 2 5 14 11 16
	mySet.traverseByLevelorder();
	cout << endl;

	cout << "Height : " << mySet.height() << ' ' << mySet.height2() << ' ' << mySet.height3() << endl;

	mySet.clear();

	// true
	cout << mySet.empty() << endl;

	Set<char> myCharSet;

	//a
	myCharSet.insert('a' + 8);
	myCharSet.insert('a' + 3);
	myCharSet.insert('a' + 2);
	myCharSet.insert('a' + 5);
	myCharSet.insert('a' + 4);
	myCharSet.insert('a' + 10);
	myCharSet.insert('a' + 14);
	myCharSet.insert('a' + 11);
	myCharSet.insert('a' + 16);

	if (myCharSet.find('a' + 2))
	{
		cout << "Found " << (char)('a' + 2) << endl;
	}

	if (myCharSet.find('a' + 12) == nullptr)
	{
		cout << "NotFound " << (char)('a' + 12) << endl;;
	}

	// 9
	cout << "Size : " << myCharSet.size() << endl;

	myCharSet.erase('a' + 4);

	// 8
	cout << "Size : " << myCharSet.size() << endl;

	if (myCharSet.find('a' + 4) == nullptr)
	{
		cout << "Not Found " << (char)('a' + 4) << endl;;
	}

	// 8 3 2 5 10 14 11 16
	myCharSet.traverseByPreorder();
	cout << endl;

	// 2 5 3 11 16 14 10 8
	myCharSet.traverseByInorder();
	cout << endl;

	// 8 3 2 5 10 14 11 16
	myCharSet.traverseByPostorder();
	cout << endl;

	// 8 3 10 2 5 14 11 16
	myCharSet.traverseByLevelorder();
	cout << endl;

	cout << "Height : " << myCharSet.height() << ' ' << myCharSet.height2() << ' ' << myCharSet.height3() << endl;

	myCharSet.clear();

	// true
	cout << myCharSet.empty() << endl;

	const auto data = { 77,18,58,28,12,17,19,9,44 };

	priority_queue<int> q;
	for (int d : data)
	{
		q.push(d);
	}	
	
	while (false == q.empty())
	{
		int d = q.top();
		q.pop();

		cout << d << ' ';
	}
	cout << endl;

	cout << "-----------------------------------------------------" << endl;

	Heap h;
	for (int d : data)
	{
		h.push(d);
	}

	while (false == h.empty())
	{
		int d = h.top();
		h.pop();

		cout << d << ' ';
	}

	make_heap(data.begin(), data.end());
}