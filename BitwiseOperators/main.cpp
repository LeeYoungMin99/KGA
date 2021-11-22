#include <iostream>
#include <bitset>

int main()
{
	using namespace std;


	// >>, << 는 오버라이딩 되어 있는 것
	// 이게 기본 기능이지만 다양한 곳에서 사용

	// << left shift
	// >> right shift
	// ~ not 
	// & and
	// | or
	// ^ xor

#define COUNT 8

	unsigned int a = 6;
	unsigned int b = 12;
	cout << a << " ";
	cout << bitset<COUNT>(a) << endl;

	cout << ~a << " ";
	cout << bitset<COUNT>(~a) << endl << endl;


	cout << bitset<COUNT>(a) << endl;
	cout << bitset<COUNT>(b) << endl;

	cout << bitset<COUNT>(a & b) << endl;
	cout << bitset<COUNT>(a | b) << endl;
	cout << bitset<COUNT>(a ^ b) << endl;

	int c = 0b0110 >> 2;
	cout << c << endl << endl;

	cout << bitset<COUNT>(5) << endl;
	cout << bitset<COUNT>(12) << endl << endl;

	cout << bitset<COUNT>(5 | 12) << endl;
	cout << (5 | 12) << endl << endl;
	cout << bitset<COUNT>(5 & 12) << endl;
	cout << (5 & 12) << endl << endl;
	cout << bitset<COUNT>(5 ^ 12) << endl;
	cout << (5 ^ 12) << endl << endl;

	bool item1_flag = false;
	bool item2_flag = true;
	bool item3_flag = false;

	// item 1 얻음
	item1_flag = true;

	// die  2 잃음
	item2_flag = false;

	// 1이 있다면 3 획득 1 잃음
	if (item1_flag == true && item3_flag == false)
	{
		item1_flag = false;
		item3_flag = true;
	}

	const unsigned char opt0 = 1 << 0;
	const unsigned char opt1 = 1 << 1;
	const unsigned char opt2 = 1 << 2;
	const unsigned char opt3 = 1 << 3;
	const unsigned char opt4 = 1 << 4;
	const unsigned char opt5 = 1 << 5;
	const unsigned char opt6 = 1 << 6;
	const unsigned char opt7 = 1 << 7;

	cout << bitset<COUNT>(opt0) << endl;
	cout << bitset<COUNT>(opt1) << endl;
	cout << bitset<COUNT>(opt2) << endl;
	cout << bitset<COUNT>(opt3) << endl;
	cout << bitset<COUNT>(opt4) << endl;
	cout << bitset<COUNT>(opt5) << endl;
	cout << bitset<COUNT>(opt6) << endl;
	cout << bitset<COUNT>(opt7) << endl;

	unsigned char items_flag = 0;
	cout << bitset<COUNT>(items_flag) << endl;

	// item0 get
	items_flag |= opt0;
	cout << bitset<COUNT>(items_flag) << endl;

	// item3 get
	items_flag |= opt3;
	cout << bitset<COUNT>(items_flag) << endl;

	// item3 lost
	items_flag &= ~opt3;
	cout << bitset<COUNT>(items_flag) << endl;

	// has item1 ?
	if (items_flag & opt1)
	{
		cout << "아이템1 갖고 있음" << endl;
	}
	else
	{
		cout << "아이템1 없음" << endl;
	}

	if (items_flag & opt0)
	{
		cout << "아이템0 갖고 있음" << endl;
	}

	// item2,3,4,5 get
	items_flag |= (opt2 | opt3 | opt4 | opt5);
	cout << bitset<COUNT>(items_flag) << endl;

	if ((items_flag & opt2) && !(items_flag & opt1))
	{
		items_flag ^= opt2;
		items_flag ^= opt1;
	}
	cout << bitset<COUNT>(items_flag) << endl;

}