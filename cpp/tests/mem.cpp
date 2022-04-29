#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
using namespace std;

int main()
{
	cout<<"hello,world!"<<endl;

	cout<<"mem.cpp"<<endl;
	int &i=*new int;
	char *m=new char[64];
	strcpy(m,"hello");
	cout<<m<<endl;
	delete &i;
	delete []m;
	return 0;
}
