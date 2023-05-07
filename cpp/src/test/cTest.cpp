#include <iostream>
#include <cstdio>
#include "cTest.h"
#include "test.h"

using namespace std;
using cppTest::Message;

void cTest()
{
	int i = cTest1();
	// extern int c_int;
	cout << "cTest1: " << i << endl;
	i = c_int; // cTest.h
	i = c_sum_1(3, 1, 2, 3);
	cout << "1+2+3: " << i << endl;
}
int cppTest1()
{
	Message m("message1");
	m.show();
	cout << m << endl;
	return 5;
}

Message::Message()
{
	this->message = "";
}
Message::Message(string s)
{
	this->message = s;
}
string Message::getMessage() const
{
	return this->message;
}
void Message::show() const
{
	cout << *this << endl;
}
ostream& cppTest::operator<<(ostream& o, const Message& m)
{
	o << m.message;
	return o;
}
