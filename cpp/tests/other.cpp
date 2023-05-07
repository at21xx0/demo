#include <iostream>
#include <iomanip>


int main(int argc, char** argv)
{
	std::cout << std::hex << std::setiosflags(std::ios::showbase | std::ios::uppercase) << 30 << std::endl;
	std::cout << std::resetiosflags(std::ios::showbase | std::ios::uppercase) << 5 << std::endl;
	std::cout << std::setbase(8) << 8 << std::setbase(10) << std::endl;
	std::cout << std::setfill('*') << std::setw(11);
	std::cout << 1 << '*' << 2 << '*' << 3 << '*' << std::endl;
	std::cout << std::setprecision(5) << 5.0123456 << std::endl; 
	return 0;
}
