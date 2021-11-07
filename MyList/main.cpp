#include <forward_list>
#include <iostream>

#include "MySingleLinkedList.h"
#include "MyTemplateSingleLinkedList.h"

using namespace std;

struct A
{
	A(int val1 = 0, int val2 = 0) { a = val1; b = val2; }
	int a;
	int b;
};

int main()
{
	forward_list<int> list;
	forward_list<int> list2(5);

	list.push_front(1);
	// [1]
	list.push_front(2);
	// [2] -> [1]
	list.push_front(3);
	// [3] -> [2] -> [1]
	list.pop_front();
	// [2] -> [1]

	// 2
	cout << list.front() << endl;

	// 2 1
	for (int elem : list)
	{
		cout << elem << ' ';
	}
	cout << endl;

	// [0] -> [0] -> [0] -> [0] -> [0]
	auto iter = list2.insert_after(list2.begin(), 3);
	// [0] -> [3] -> [0] -> [0] -> [0] -> [0] 
	//		         iter

	++iter;

	iter = list2.insert_after(iter, 4);
	// [0] -> [3] -> [0] -> [4] -> [0] -> [0] -> [0]
	//						iter

	list2.erase_after(iter);
	// [0] -> [3] -> [0] -> [4] -> [0] -> [0]

	for (int elem : list2)
	{
		cout << elem << ' ';
	}
	cout << endl;

	cout << boolalpha << list2.empty() << endl;

	forward_list<int> list3(list);

	for (int elem : list3)
	{
		cout << elem << ' ';
	}
	cout << endl;

	MyTemplateSingleLinkedList<char> myTemplateList;
	MyTemplateSingleLinkedList<char> myTemplatelist2(5);

	myTemplateList.push_front('a');
	myTemplateList.push_front('b');
	myTemplateList.push_front('c');
	myTemplateList.pop_front();

	cout << myTemplateList.front() << endl;

	for (auto iter = myTemplateList.begin(); iter != myTemplateList.end(); iter = iter->Next)
	{
		cout << iter->Data << ' ';
	}
	cout << endl;

	auto iter3 = myTemplatelist2.insert_after(myTemplatelist2.begin(), 'c');
	iter3 = iter3->Next;
	iter3 = myTemplatelist2.insert_after(iter3, 'd');
	myTemplatelist2.erase_after(iter3);


	for (auto iter = myTemplatelist2.begin(); iter != myTemplatelist2.end(); iter = iter->Next)
	{
		cout << iter->Data << ' ';
	}
	cout << endl;

	cout << boolalpha << myTemplatelist2.empty() << endl;

	MyTemplateSingleLinkedList<char> myTemplateList3(myTemplateList);

	for (auto iter = myTemplateList3.begin(); iter != myTemplateList3.end(); iter = iter->Next)
	{
		cout << iter->Data << ' ';
	}
	cout << endl;


	MyTemplateSingleLinkedList<A> myStTemplateList;
	MyTemplateSingleLinkedList<A> myStTemplatelist2(5);

	myStTemplateList.push_front({1,2});
	myStTemplateList.push_front({3,4});
	myStTemplateList.push_front({5,6});
	myStTemplateList.pop_front();

	cout << myStTemplateList.front().a << myStTemplateList.front().b << endl;

	for (auto iter = myStTemplateList.begin(); iter != myStTemplateList.end(); iter = iter->Next)
	{
		cout << iter->Data.a << iter->Data.b << ' ';
	}
	cout << endl;

	auto iter4 = myStTemplatelist2.insert_after(myStTemplatelist2.begin(), {5,6});
	iter4 = iter4->Next;
	iter4 = myStTemplatelist2.insert_after(iter4, { 7,8 });
	myStTemplatelist2.erase_after(iter4);


	for (auto iter = myStTemplatelist2.begin(); iter != myStTemplatelist2.end(); iter= iter->Next)
	{
		cout << iter->Data.a << iter->Data.b << ' ';
	}
	cout << endl;

	cout << boolalpha << myStTemplatelist2.empty() << endl;

	MyTemplateSingleLinkedList<A> myStTemplateList3(myStTemplateList);

	for (auto iter = myStTemplateList3.begin(); iter != myStTemplateList3.end(); iter = iter->Next)
	{
		cout << iter->Data.a << iter->Data.b << ' ';
	}
	cout << endl;


	MySingleLinkedList mylist;
	MySingleLinkedList mylist2(5);

	mylist.push_front(1);
	mylist.push_front(2);
	mylist.push_front(3);
	mylist.pop_front();

	cout << mylist.front() << endl;

	for (auto iter = mylist.begin(); iter != mylist.end(); iter = iter->Next)
	{
		cout << iter->Data << ' ';
	}
	cout << endl;

	auto iter2 = mylist2.insert_after(mylist2.begin(), 3);
	iter2 = iter2->Next;
	iter2 = mylist2.insert_after(iter2, 4);
	mylist2.erase_after(iter2);


	for (auto iter = mylist2.begin(); iter != mylist2.end(); iter = iter->Next)
	{
		cout << iter->Data << ' ';
	}
	cout << endl;

	cout << boolalpha << mylist2.empty() << endl;

	MySingleLinkedList mylist3(mylist);

	for (auto iter = mylist3.begin(); iter != mylist3.end(); iter = iter->Next)
	{
		cout << iter->Data << ' ';
	}
	cout << endl;
}