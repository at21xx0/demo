#include <iostream>
#include <limits>
//#include <vector>

#include "test.h"

using namespace std;
//template <typename T>
//concept Integral = std::is_integral::value;
#define nT(T) \
	std::cout << #T << std::endl << "  size: " << sizeof(T) << std::endl << "  max: " << (numeric_limits<T>::max)() << std::endl << "  min: " << (numeric_limits<T>::min)() << std::endl;
class c1{
	public:
		c1(){}
		int operator[](int i)
		{
			return i;
		}
};

int main(int argc, char **argv)
{
	int *i = new int;
	*i = 5;
	auto n = *i;
	(void)argc;
	(void)argv;
	cout << "test" << endl;
	cout << *i << endl;
	delete i;
	cout << n << endl;
	nT(int);
	nT(signed int);
	nT(unsigned int);
	nT(long);
	nT(long long);
	nT(long long int);
	COUT(1+1);
	COUT(1-1);
	COUT(1|1);
	COUT(1&1);
	COUT(1^1);
	COUT(~((int)1));
	c1 c;
	cout << c[5] << endl;
	cout << endl << endl;
	//const type_info &nInfo = typeid(n);
	//cout << nInfo.name() << "|" << nInfo.raw_name() << "|" << nInfo.hash_code() << endl;
	stringTest();
	classTest();
	cTest();
	/*
	vector<int> a;
	srand((unsigned)time(0));
	for(int i = 0;i < 100000;++i)
	{
		a.insert(a.end(), rand());
	}
	sort(a.begin(), a.end());
	for(int i = 0;i < 100000;++i)
	{
		cout << a.at(i) << endl;
	}
	*/

	return 0;
}
