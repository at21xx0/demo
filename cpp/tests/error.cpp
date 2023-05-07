#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<exception>
using namespace std;

class myexception : public exception
{
	public: 
		virtual const char* what() const throw()
		{
			return static_cast<const char *>("MyException");
		}
};
// void somefunc() noexcept; // C++ 11 // noerror

int main()
{
	cout<<"hello,world!"<<endl;

	cout<<"error.cpp"<<endl;
	int i=15,y=1,z=1;
	try{
		y=y-z;
		if(y == 0)
			throw myexception();
		z=i/y;
		cout<<z<<endl;
		// throw "???";
		// throw 123;
		// logic_error runtime_error bad_alloc bad_typeid bad_cast ios_base::failure bad_exception
		// logic_error // length_error domain_error out_of_range invalid_argument
		// runtime_error // range_error overflow_error underflow_error
		// std::logic_error
	}catch(myexception& e){
		cout<<e.what()<<endl;
	}catch(std::exception& e){
		cout<<e.what()<<endl;
	}
	return 0;
}
