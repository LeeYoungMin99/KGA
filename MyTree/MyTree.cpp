#include <iostream>
#include <set>
#include "Set.h"

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

	if (set.end() != set.find(12))
	{
		cout << "Not Found 12\n";
	}


}