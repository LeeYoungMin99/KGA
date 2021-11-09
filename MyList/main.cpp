#include <forward_list>
#include <list>
#include <iostream>

#include "MySingleLinkedList.h"
#include "MyTemplateSingleLinkedList.h"
#include "MyCircularSingleLinkedList.h"

using namespace std;

void print(const MyCircularSingleLinkedList& mcList)
{
	for (auto iter = mcList.before_head(); iter != mcList.tail();)
	{
		iter = iter->Next;
		cout << iter->Data << ' ';
	}

	cout << endl;
}

struct A
{
	A(int val1 = 0, int val2 = 0) { a = val1; b = val2; }
	int a;
	int b;
};

int main()
{
#pragma region forwardList

	forward_list<int> forwardList;
	forward_list<int> forwardList2(5);

	forwardList.push_front(1);
	// [1]
	forwardList.push_front(2);
	// [2] -> [1]
	forwardList.push_front(3);
	// [3] -> [2] -> [1]
	forwardList.pop_front();
	// [2] -> [1]

	// 2
	cout << forwardList.front() << endl;

	// 2 1
	for (int elem : forwardList)
	{
		cout << elem << ' ';
	}
	cout << endl;

	// [0] -> [0] -> [0] -> [0] -> [0]
	auto iter = forwardList2.insert_after(forwardList2.begin(), 3);
	// [0] -> [3] -> [0] -> [0] -> [0] -> [0] 
	//		         iter

	++iter;

	iter = forwardList2.insert_after(iter, 4);
	// [0] -> [3] -> [0] -> [4] -> [0] -> [0] -> [0]
	//						iter

	forwardList2.erase_after(iter);
	// [0] -> [3] -> [0] -> [4] -> [0] -> [0]

	for (int elem : forwardList2)
	{
		cout << elem << ' ';
	}
	cout << endl;

	cout << boolalpha << forwardList2.empty() << endl;

	forward_list<int> forwardlist3(forwardList);

	for (int elem : forwardlist3)
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

	for (auto iter = myTemplateList.begin(); iter != myTemplateList.end(); ++iter)
	{
		cout << *iter << ' ';
	}
	cout << endl;

	auto iter3 = myTemplatelist2.insert_after(myTemplatelist2.begin(), 'c');
	++iter3;
	iter3 = myTemplatelist2.insert_after(iter3, 'd');
	myTemplatelist2.erase_after(iter3);


	for (auto iter = myTemplatelist2.begin(); iter != myTemplatelist2.end(); ++iter)
	{
		cout << *iter << ' ';
	}
	cout << endl;

	cout << boolalpha << myTemplatelist2.empty() << endl;

	MyTemplateSingleLinkedList<char> myTemplateList3(myTemplateList);

	for (auto iter = myTemplateList3.begin(); iter != myTemplateList3.end(); ++iter)
	{
		cout << *iter << ' ';
	}
	cout << endl;


	MyTemplateSingleLinkedList<A> myStTemplateList;
	MyTemplateSingleLinkedList<A> myStTemplatelist2(5);

	myStTemplateList.push_front({ 1,2 });
	myStTemplateList.push_front({ 3,4 });
	myStTemplateList.push_front({ 5,6 });
	myStTemplateList.pop_front();

	cout << myStTemplateList.front().a << myStTemplateList.front().b << endl;

	for (auto iter = myStTemplateList.begin(); iter != myStTemplateList.end(); ++iter)
	{
		cout << "{" << iter->a << ", " << iter->b << "}" << ' ';
	}
	cout << endl;

	auto iter4 = myStTemplatelist2.insert_after(myStTemplatelist2.begin(), { 5,6 });
	++iter4;
	iter4 = myStTemplatelist2.insert_after(iter4, { 7,8 });
	myStTemplatelist2.erase_after(iter4);


	for (auto iter = myStTemplatelist2.begin(); iter != myStTemplatelist2.end(); ++iter)
	{
		cout << "{" << iter->a << ", " << iter->b << "}" << ' ';
	}
	cout << endl;

	cout << boolalpha << myStTemplatelist2.empty() << endl;

	MyTemplateSingleLinkedList<A> myStTemplateList3(myStTemplateList);

	for (auto iter = myStTemplateList3.begin(); iter != myStTemplateList3.end(); ++iter)
	{
		cout << "{" << iter->a << ", " << iter->b << "}" << ' ';
	}
	cout << endl;


	MySingleLinkedList mylist;
	MySingleLinkedList mylist2(5);

	mylist.push_front(1);
	mylist.push_front(2);
	mylist.push_front(3);
	mylist.pop_front();

	cout << mylist.front() << endl;

	for (auto iter = mylist.begin(); iter != mylist.end(); iter = ++iter)
	{
		cout << *iter << ' ';
	}
	cout << endl;

	auto iter2 = mylist2.insert_after(mylist2.begin(), 3);
	++iter2;
	iter2 = mylist2.insert_after(iter2, 4);
	mylist2.erase_after(iter2);


	for (auto iter = mylist2.begin(); iter != mylist2.end(); ++iter)
	{
		cout << *iter << ' ';
	}
	cout << endl;

	cout << boolalpha << mylist2.empty() << endl;

	MySingleLinkedList mylist3(mylist);

	for (auto iter = mylist3.begin(); iter != mylist3.end(); ++iter)
	{
		cout << *iter << ' ';
	}
	cout << endl;

#pragma endregion

#pragma region List


#pragma endregion

#pragma region CircularSingleLinkedList


	cout << "여기부터" << endl;
	MyCircularSingleLinkedList mcList;
	MyCircularSingleLinkedList mcList6(5);


	//mcList.push_front(1);
	//// [1]
	//mcList.push_front(2);
	//// [2] -> [1]
	//mcList.push_front(3);
	//print(mcList);
	//// [3] -> [2] -> [1]
	//mcList.push_front(4);
	//// [4] -> [3] -> [2] -> [1]

	mcList.push_back(4);
	mcList.push_back(3);
	mcList.push_back(2);
	mcList.push_back(1);
	//mcList.pop_front();
	//// [2] -> [1]


	auto testiter = mcList.head()->Next->Next->Next;

	MyCircularSingleLinkedList mcList1 = mcList;
	MyCircularSingleLinkedList mcList2 = mcList;
	MyCircularSingleLinkedList mcList3 = mcList;
	MyCircularSingleLinkedList mcList4 = mcList;
	MyCircularSingleLinkedList mcList5;
	mcList5 = mcList;

	print(mcList);
	cout << "4 3 2 1 예상" << endl;
	cout << "before_tail : " << mcList.before_tail()->Data << endl;
	cout << "       tail : " << mcList.tail()->Data << endl;
	cout << "       head : " << mcList.head()->Data << endl;
	cout << endl;

	testiter = mcList1.before_head();
	mcList1.erase_after(testiter);

	print(mcList1);
	cout << "3 2 1 예상" << endl;
	cout << "before_tail : " << mcList1.before_tail()->Data << endl;
	cout << "       tail : " << mcList1.tail()->Data << endl;
	cout << "       head : " << mcList1.head()->Data << endl;

	testiter = mcList2.before_head()->Next;
	mcList2.erase_after(testiter);

	print(mcList2);
	cout << "4 2 1 예상" << endl;
	cout << "before_tail : " << mcList2.before_tail()->Data << endl;
	cout << "       tail : " << mcList2.tail()->Data << endl;
	cout << "       head : " << mcList2.head()->Data << endl;

	testiter = mcList3.before_head()->Next->Next;
	mcList3.erase_after(testiter);

	print(mcList3);
	cout << "4 3 1 예상" << endl;
	cout << "before_tail : " << mcList3.before_tail()->Data << endl;
	cout << "       tail : " << mcList3.tail()->Data << endl;
	cout << "       head : " << mcList3.head()->Data << endl;

	testiter = mcList4.before_head()->Next->Next->Next;
	mcList4.erase_after(testiter);

	print(mcList4);
	cout << "4 3 2 예상" << endl;
	cout << "before_tail : " << mcList4.before_tail()->Data << endl;
	cout << "       tail : " << mcList4.tail()->Data << endl;
	cout << "       head : " << mcList4.head()->Data << endl;

	testiter = mcList5.before_head()->Next->Next->Next->Next;

	print(mcList5);
	cout << "before_tail : " << mcList5.before_tail()->Data << endl;
	cout << "       tail : " << mcList5.tail()->Data << endl;
	cout << "       head : " << mcList5.head()->Data << endl;

	mcList5.erase_after(testiter);

	print(mcList5);
	cout << "3 2 1 예상" << endl;
	cout << "before_tail : " << mcList5.before_tail()->Data << endl;
	cout << "       tail : " << mcList5.tail()->Data << endl;
	cout << "       head : " << mcList5.head()->Data << endl;

	print(mcList);


	auto mcIter = mcList.head();
	do
	{
		std::cout << mcIter->Data << "->";
		mcIter = mcIter->Next;
	} while (mcIter != mcList.tail());
	std::cout << mcIter->Data << std::endl;

	cout << boolalpha << mcList.contains(1) << endl;;
	cout << boolalpha << mcList.contains(2) << endl;;
	cout << boolalpha << mcList.contains(3) << endl;;
	cout << boolalpha << mcList.contains(4) << endl;;
	cout << boolalpha << mcList.contains(5) << endl;;


	cout << mcList.front() << endl;
	cout << mcList.back() << endl;
	mcList.clear();
	cout << boolalpha << mcList.empty() << endl;
	cout << boolalpha << mcList.contains(1) << endl;;


	mcList.push_back(1);
	cout << mcList.back() << endl;
	cout << mcList.front() << endl;


	// [0] -> [0] -> [0] -> [0] -> [0]
	auto mcIter2 = mcList6.insert_after(mcList6.head(), 3);
	// [0] -> [3] -> [0] -> [0] -> [0] -> [0]
	//		         iter

	mcIter2 = mcIter2->Next;

	mcIter2 = mcList6.insert_after(mcIter2, 4);
	// [0] -> [3] -> [0] -> [4] -> [0] -> [0] -> [0]
	//						iter

	mcList6.erase_after(mcIter2);

	// [0] -> [3] -> [0] -> [4] -> [0] -> [0]
	print(mcList6);
	cout << endl;

	cout << boolalpha << mcList6.empty() << endl;

	MyCircularSingleLinkedList mcList7(mcList6);

	print(mcList7);
	cout << endl;

#pragma endregion

}