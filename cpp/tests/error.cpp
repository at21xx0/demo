#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	cout<<"hello,world!"<<endl;

	cout<<"error.cpp"<<endl;
	int i=15,y=1,z=1;
	try{
		y=y-z;
		z=i/y;
		cout<<z<<endl;
	}catch(std::exception e){
		cout<<"e"<<endl;
	}
	return 0;
}
