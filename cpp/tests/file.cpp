#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;


int main()
{
	cout<<"hello,world!"<<endl;

	int i;
	cout<<"file.cpp"<<endl;
	ofstream fo;// 读 写 读写 ofstream ifstream fstream
	fo.open("a.txt",ios::out|ios::trunc);// 追加(ios::app) 打开后在文件末尾(ios::ate) 用于读(ios::in) 写(ios::out) 从头写(ios::trunc) 二进制(ios::binary)
	srand((unsigned int)time(NULL));
	for(i=0;i<10000;i++)fo<<rand()<<endl;
	fo.seekp(5,ios::beg);// 开头 当前 结尾 ios::beg ios::cur ios::end
	// seekg  seek get  seekp seek put
	// seekg 是 ifstream 专用
	streampos pos = fo.tellp();
	cout << pos << endl;
	fo<<"fast"<<endl;
	// ostream & write(char* buffer, int count);
	// istream & read(char* buffer, int count);
	// istream & getline(char* buf, int bufSize);
	// istream & getline(char* buf, int bufSize, char delim);
	// getline(istream& i, string& s);
	fo.close();
	// cin>>i; // istream
	return 0;
}
