#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#include "test.h"

using namespace std;

extern "C"{
	const char *_c_string = "Cstring";
};
void stringC()
{
	string s1; // 空字符串
	string s2 = "string2";
	string s3(s2); // 拷贝
	string s4(s2, 1); // 始于1位置复制
	string s5(s2, 1, 3); // s5(s2, pos, len);
	extern const char *_c_string; // C++ 中没有这种隐式转换，所以加 const
	const char *_c_s2 = "CSTRING"; // 这里代替被注释的那两个
	//char cc1[] = "sss";
	string s6(_c_string);
	string s7(_c_s2, 4); // 前4个字符
	string s8(5,'c'); // 包含5个c
	string s9(1,9); //以区间beg;end(不包含end)内的字符作为字符串s的初值
	C2(s1);
	C2(s2);
	C2(s3);
	C2(s4);
	C2(s5);
	C2(s6);
	C2(s7);
	C2(s8);
	C2(s9);
}
void utfTest()
{
	//汉字：你好啊
	const char* szgbk = u8"你好啊";
	char u8[] = u8"\u4f60\u597d\u554a";
	char16_t u16[] = u"\u4f60\u597d\u554a";
	char32_t u32[] = U"\u4f60\u597d\u554a";
	(void)szgbk;
	std::cout<<"u8:"<<u8<<std::endl;
	std::cout<<"u16:"<<u16<<std::endl;
	std::cout<<"u32:"<<u32<<std::endl;

	//两个2字节emoji字符
	char u8emoji[] = u8"\u1f4bb\u231a"; //\u形式无法输入超过2字节的unicode字符了
	char16_t u16emoji[] = u"\u1f4bb\u231a"; //用u16编码也无法正确输入超过2字符的unicode
	char32_t u32emoji[] = U"x\u231a";
	u32emoji[0] = 0x1f4bb; //笔记本电脑图标的emoji，用u32编码直接输入超过2字符的unicode字符.


	std::cout<<"u8emoji:"<<u8emoji<<std::endl;
	std::cout<<"u16emoji:"<<u16emoji<<std::endl;
	std::cout<<"u32emoji:"<<u32emoji<<std::endl;

	//utf32 to utf16
	std::u32string u32wstr(u32emoji);
	std::wstring_convert<std::codecvt_utf16<char32_t , 0x10ffff, std::little_endian>, char32_t> utf16le_cvt;
	std::string stru16bytes = utf16le_cvt.to_bytes(u32wstr);
	char16_t* p16 = (char16_t*)(stru16bytes.c_str()); //观察内存可以看到大于2字节的emoji字符，从u32转到u16，做了相应的编码

	//u16 to u8
	//std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> utf8_ucs2_cvt;
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf8_ucs2_cvt;
	std::string stru18emoji = utf8_ucs2_cvt.to_bytes(p16);
	std::u16string stru16emoji = utf8_ucs2_cvt.from_bytes(stru18emoji);

	//utf8 to u32
	std::wstring_convert<std::codecvt_utf8<char32_t >, char32_t> u8_u32_convert;
	std::string u32tou8 = u8_u32_convert.to_bytes(u32emoji); //u32 to u8
	std::u32string stru32emoji = u8_u32_convert.from_bytes(stru18emoji);//u8 to u32

	//uft8 to u1
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t >, char16_t> u8_u16_convert;
	std::u16string stru16emoji2 = u8_u16_convert.from_bytes(stru18emoji);

	std::cout<<"end u8u16u32"<<std::endl;
}



void stringTest(void)
{
	string s1 = "userName";
	string s2 = "password";
	string s3 = "clientId";
	string s4;
	size_t t;
	u32string s32;
	u16string s16;
	wstring sw;
	string::iterator it;
	ios::sync_with_stdio(false); // cin cout 提速
#define pos 1
#define len 5
	stringC();
	cout << "stringTest" << endl;
	cout << s1 << endl;
	cout << s2 << endl;
	s4 = s1; // 复制
	COUT(s4);
	s4 = s1 + s2 + s3;
	COUT(s4);
	s1 = "0123456789ABCDEF";
	C2(s1);
	C2(s1 == s2);
	C2(s1 == "0123456789ABCDEF"); // 比较  
	C2(s1.length());
	C2(s1.size());
	C2(s1[0]);
	C2(typeid(s1[0]).name());


	C2(s1.substr(pos)); // 截取字符串 
	C2(s1.substr(pos, len));
	s2 = "[str]";
	C2(s2);
	C2(s1.insert(pos, s2)); // 插入str
	C2(s1.insert(pos, s2)); // 改变了原来的值
#define s2_pos 1
#define s2_len 3
	C2(s1.insert(pos, s2, s2_pos, s2_len));
	C2(s1.insert(pos, s2.substr(s2_pos, s2_len)));
	C2(s1.insert(pos, s2, s2_pos));
	C2(s1.insert(pos, "Cstr"));
	C2(s1.insert(pos, len, '*'));
	it = s1.insert(s1.begin() + 1, '.');// 返回新插入位置的迭代器
	s1.insert(s1.begin(), 3, 'z');// 在 插入3个Z
	C2(s1);
	s1.insert(it + 2, s1.begin(), s1.begin() + 3); // 在 it 位置 插入区间[s1.begin(), s1.begin() + 3) 字符串
	C2(s1);
	C2(s1.erase(pos, len)); // 擦除
	C3(s1.erase(s1.begin() + 2), s1)// 删除迭代器指向字符 '.'
	C3(s1.erase(s1.begin() + 2, s1.end() - 15), s1);
	C2(s1.append(s2));// 拼接到末尾
	C2(s1.append(s2, s2_pos, s2_len));
	C2(s1.append(s2, pos));
	C2(s1.append("Cstring...", len)); // 前len个字符
	C2(s1.append("Cstring..."));
	C2(s1.append(10u, '?'));// 10 个?
	C2(s1.append(s1.begin() + 8, s1.end()));
	C2(s1.append(5, (char)65)); // 5个A
	C2(s1 += s2);
	s3 = "[STR]";
	C2(s1.replace(pos + 1, len, s3)); // 从第 pos + 1 开始共替换len个字符为 s3
	C2(s1.replace(pos + 1 + 1, len + 13, s3));
	C2(s1.replace(pos + 1 + 2, s2_len, s2, s2_pos, s2_len));
	C2(s1.replace(pos + 1 + 1, len, "()"));
	C2(s1.replace(pos + 1 + 1, 2, 3, '?'));
	C3(s1.replace(s1.begin(), s1.end(), s2 + s3), s1);
	C3(s1.replace(s1.begin() + 2, s1.end() - 3, "_"), s1);
	C3(s1.replace(s1.begin() + 2, s1.end() - 3, 6, '?'), s1);
	C3(s1.replace(s1.begin() + 2, s1.end() - 3, "Cstr", 2), s1);
	C3(s1.replace(s1.begin() + 2, s1.end() - 3, s2.begin(), s2.end()), s1);
	C2(s1.assign(s2)); // 赋值
	C2(s1.assign(s2, s2_pos, s2_len));
	C2(s1.assign("Cstr", 3));
	C2(s1.assign("Cstr"));
	C2(s1.assign(25, '*'));
	C2(s1.assign(10, (char)0x2D));
	C2(s1.assign(s2.begin(), s2.end()));
	s1.assign(s2);
	s1.append(s3);
	s1.append(s2);
	C2(s1);
	C2(t = s1.find(s1));// 第一次出现
	C2(t == string::npos);
	if(t != string::npos)
	{
		cout << "first: " << t << endl;
		C2(t = s1.find(s2, t + 1)); // 查找第二次出现
		cout << "second: " << t << endl;
	}
	C2(s1.find("str", 0, 5)); // 查找从0开始前5个字符
	C2(s1.find("str"));
	C2(s1.find('s'));
	if(t != string::npos)
	{
		C2(s1.replace(s1.find(s2), s2.length(), s3));
	}
	C2(t = s1.rfind(s3));
	if(t != string::npos)
	{
		C2(s1.replace(t, s3.length(), s2));
	}
	// ...
	s4 = "()[]{}[]";
	C2(s4);
	C2(t = s1.find_first_of(s4)); // s4 中任意字符第一次出现
	C2(t = s1.find_last_of(s4));
	C2(t = s1.find_first_not_of(s4)); // 不再 s4
	C2(t = s1.find_last_not_of(s4));

	// MinGW 不低于3.8，否则有BUG
	C2(s2.compare(s3)); // >  与 strcmp 基本相同
	C2(s1.compare(5, s2.length(), s2)); // 6 为pos
	C2(s1.compare(5, 3, "[st"));
	C2(s1.compare(5, 3, s2, 0, 3)); // 同上
	C2(s2 >= s3);// 运算符 == >= <= > <
	C2(to_string(5)); // std::to_string
	s1 = to_string(65536);
	C2(stoi(s1)); // 转 int
	C2(stol(s1)); // 转 long
	C2(stoll(s1));
	C2(stoul(s1)); // 转 unsigned long
	C2(t = s1.find_first_of("0123456789"))
	C2(stoi(s1, &t, 8)); // 8 进制
	C2(stof(s1, &t));
	C2(stof(s1));
	C2(typeid(stold(s1)).name());
	C2(typeid(double).name());
	C2(L"str");
	C2(u"str");
	C2(U"str");
	//u32string s32;
	//u16string s16;
	//wstring sw;
	(void)s16;
	(void)sw;
	s32 = U"测试";
	C2(sizeof(char32_t));
	for(char32_t x:s32)
	{
		wcout << (uint32_t)x << (wchar_t)x;
		//wcout << (char32_t)x;
	}
	cout << endl;
	utfTest();
	// #include<sstream> // ostringstream


}


