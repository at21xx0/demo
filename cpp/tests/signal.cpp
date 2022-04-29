#include<iostream>
#include<csignal>
#include<unistd.h>
using namespace std;

void s1(int signum)
{
	cout<<"signal:"<<signum<<endl;
	exit(signum);
}
int main()
{
	cout<<"hello,world!"<<endl;
	cout<<"signal.cpp"<<endl;
	cout<<"Ctrl+C"<<endl;
	signal(SIGINT,s1);
	for(int i=0; ;i++)
	{
		cout<<i<<endl;
		sleep(1);
		if(i==99)
		{
			cout<<"close"<<endl;
			raise(SIGINT);
		}
	}
	return 0;
}
