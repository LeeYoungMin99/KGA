#include <iostream>
#include <vector>

#include "MyVector.h"
#include "MyTemplateVector.h"

using namespace std;

struct A
{
	A(int val1 = 0, int val2 = 0) { a = val1; b = val2; };
	int a;
	int b;
};

int main()
{
	vector<int> vec;
	vector<int> vec2(5);
	vector<int> vec3 = { 1, 2, 3, 4, 5 };

	vec.push_back(1);
	vec.push_back(2);
	vec.pop_back();

	for (size_t i = 0; i < vec.size(); ++i)
	{
		cout << vec[i];
	}
	cout << endl;

	try
	{
		vec.at(1);
	}
	catch (std::out_of_range& e)
	{
		cout << e.what() << endl;
	}

	vec.pop_back();

	cout << boolalpha << vec.empty() << endl;

	cout << "Cap : " << vec.capacity() << endl;
	vec.reserve(10);
	cout << "New Cap : " << vec.capacity() << endl;

	vec2.insert(vec2.begin() + 2, 3);
	for (size_t elem : vec2)
	{
		cout << elem << ' ';
	}
	cout << endl;

	vec3.erase(vec3.begin());
	for (size_t i = 0; i < vec3.size(); ++i)
	{
		cout << vec3[i] << ' ';
	}
	cout << endl;

	vector<int> vec4 = vec3;
	for (size_t i = 0; i < vec4.size(); ++i)
	{
		cout << vec4[i] << ' ';
	}
	cout << endl << endl << endl;

	MyVector myVec;
	MyVector myVec2(5);
	MyVector myVec3;/* = { 1, 2, 3, 4, 5 };*/
	myVec3.push_back(1);
	myVec3.push_back(2);
	myVec3.push_back(3);
	myVec3.push_back(4);
	myVec3.push_back(5);

	myVec.push_back(1);
	myVec.push_back(2);
	myVec.pop_back();

	for (size_t i = 0; i < myVec.size(); ++i)
	{
		cout << myVec[i];
	}
	cout << endl;

	try
	{
		myVec.at(1);
	}
	catch (std::out_of_range& e)
	{
		cout << e.what() << endl;
	}

	myVec.pop_back();

	cout << boolalpha << myVec.empty() << endl;

	cout << "Cap : " << myVec.capacity() << endl;
	myVec.reserve(10);
	cout << "New Cap : " << myVec.capacity() << endl;

	myVec2.insert(myVec2.begin() + 2, 3);
	for (size_t elem : myVec2)
	{
		cout << elem << ' ';
	}
	cout << endl;

	myVec3.erase(myVec3.begin());
	for (size_t i = 0; i < myVec3.size(); ++i)
	{
		cout << myVec3[i] << ' ';
	}
	cout << endl;

	MyVector myVec4 = myVec3;
	for (size_t i = 0; i < myVec4.size(); ++i)
	{
		cout << myVec4[i] << ' ';
	}
	cout << endl << endl << endl;

	MyTemplateVector<char> myTemplateVec;
	MyTemplateVector<char> myTemplateVec2(5);
	MyTemplateVector<char> myTemplateVec3;/* = { a, b, c, d, e };*/
	myTemplateVec3.push_back('a');
	myTemplateVec3.push_back('b');
	myTemplateVec3.push_back('c');
	myTemplateVec3.push_back('d');
	myTemplateVec3.push_back('e');

	myTemplateVec.push_back('a');
	myTemplateVec.push_back('b');
	myTemplateVec.pop_back();

	for (size_t i = 0; i < myTemplateVec.size(); ++i)
	{
		cout << myTemplateVec[i];
	}
	cout << endl;

	try
	{
		myTemplateVec.at(1);
	}
	catch (std::out_of_range& e)
	{
		cout << e.what() << endl;
	}

	myTemplateVec.pop_back();

	cout << boolalpha << myTemplateVec.empty() << endl;

	cout << "Cap : " << myTemplateVec.capacity() << endl;
	myTemplateVec.reserve(10);
	cout << "New Cap : " << myTemplateVec.capacity() << endl;

	myTemplateVec2.insert(myTemplateVec2.begin() + 2, 3);
	for (char elem : myTemplateVec2)
	{
		cout << elem;
	}
	cout << endl;

	myTemplateVec3.erase(myTemplateVec3.begin());
	for (size_t i = 0; i < myTemplateVec3.size(); ++i)
	{
		cout << myTemplateVec3[i] << ' ';
	}
	cout << endl;

	MyTemplateVector<char> myTemplateVec4 = myTemplateVec3;
	for (size_t i = 0; i < myTemplateVec4.size(); ++i)
	{
		cout << myTemplateVec4[i] << ' ';
	}
	cout << endl << endl << endl;

	MyTemplateVector<A> myTemplateStVec;
	MyTemplateVector<A> myTemplateStVec2(5);
	MyTemplateVector<A> myTemplateStVec3;/* = { { 1 ,2 }, { 3, 4 }, { 5 , 6 }, { 7 , 8 }, { 9 , 10 } };*/
	myTemplateStVec3.push_back({ 1, 2 });
	myTemplateStVec3.push_back({ 3, 4 });
	myTemplateStVec3.push_back({ 5, 6 });
	myTemplateStVec3.push_back({ 7, 8 });
	myTemplateStVec3.push_back({ 9, 10 });

	myTemplateStVec.push_back((1, 2));
	myTemplateStVec.push_back((3, 4));
	myTemplateStVec.pop_back();

	for (size_t i = 0; i < myTemplateStVec.size(); ++i)
	{
		cout << "(" << myTemplateStVec[i].a << ", " << myTemplateStVec[i].b << ") ";
	}
	cout << endl;

	try
	{
		myTemplateStVec.at(1);
	}
	catch (std::out_of_range& e)
	{
		cout << e.what() << endl;
	}

	myTemplateStVec.pop_back();

	cout << boolalpha << myTemplateStVec.empty() << endl;

	cout << "Cap : " << myTemplateStVec.capacity() << endl;
	myTemplateStVec.reserve(10);
	cout << "New Cap : " << myTemplateStVec.capacity() << endl;

	myTemplateStVec2.insert(myTemplateStVec2.begin() + 2, { 5,6 });
	for (A elem : myTemplateStVec2)
	{
		cout << "(" << elem.a << ", " << elem.b << ") ";
	}
	cout << endl;

	myTemplateStVec3.erase(myTemplateStVec3.begin());
	for (size_t i = 0; i < myTemplateStVec3.size(); ++i)
	{
		cout << "(" << myTemplateStVec3[i].a << ", " << myTemplateStVec3[i].b << ") ";
	}
	cout << endl;

	MyTemplateVector<A> myTemplateStVec4 = myTemplateStVec3;
	for (size_t i = 0; i < myTemplateStVec4.size(); ++i)
	{
		cout << "(" << myTemplateStVec4[i].a << ", " << myTemplateStVec4[i].b << ") ";
	}
	cout << endl;
}