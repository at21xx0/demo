#include <iostream>
#include <iomanip>

#include "test.h"

using namespace std;


namespace ClassTest // 使用namespace防止重复，冲突
{
	/*
	 * 注意
	 * 尽量要把类的声明和实现分开
	 * 比如声明写在 xxx.h 中
	 * 实现写在 xxx.cpp 中
	 */
	class BaseClass
	{
		private:
			static int privateId;
			int *p; // 备用
		protected:
			int id;
		public:
			BaseClass() // 构造函数
			{

				id = ++privateId; // this->id
				cout << "Constructor: " << id << endl;
				p = new int;
			}
			~BaseClass() // 析构函数
			{
				cout << "Destructor: " << id << endl;
				delete p;
			}
			int getId() const // const 指不改变类成员变量，但可以改变static成员
			{
				return this->id;
			}
			static int getStaticId()
			{
				// 静态函数，只能使用静态成员
				return privateId;
			}
			friend int getId(const BaseClass& b); //友元函数声明

	};
	int BaseClass::privateId = 0; // 初始化
	int getId(const BaseClass& a) //友元函数实现
	{
		// 友元函数有权访问 private protected 成员
		return a.id;
	}
	class Number{
		protected:
			int n;
		public:
			Number()
			{
				n = 0;
			}
			Number(int n)
			{
				this->n = n; // 解决命名冲突
			}
			Number(const Number& a) // 拷贝函数
			{
				this->n = a.n;
			}
			Number& operator=(const Number& a)
			{
				// 拷贝赋值运算符 // 解决 deprecated copy
				Number *b;
				if(this==&a)
					return *this;//证同测试
				b = new Number(a.n);
				return *b;
				
			}

			~Number()
			{
			}
			int getN() const
			{
				return n;
			}
			friend int getN(const Number& a);
			operator int() const
			{
				return n;
			}
			Number& add()
			{
				this->n++;
				// 返回引用，意味着没有新创建一个 Number 对象
				return *this;
			}
			Number& add(int i)
			{
				this->n += i;
				return *this;
			}
			Number& operator++(); // 前缀
			Number& operator--();
			Number operator--(int); // 后缀
			Number operator++(int);
			Number operator+(const Number &bc)
			{
				Number b;
				b.n = this->n + bc.n;
				return b;
			}
			Number operator-(const Number &bc) const;
			Number operator-() const
			{
				Number b(-this->n);
				return b;
			}
			friend Number operator+(const Number& a, const Number& b); // 不能用 const
			Number& operator<<(const Number& a)
			{
				return this->add(a.getN());
			}
			Number& operator<<(int n)
			{
				return this->add(n);
			}
			Number &operator+=(const Number& a)
			{
				this->n += a.n;
				return *this;
			}
			bool operator==(Number& a)
			{
				return (bool)(this->n == a.n);
			}
			bool operator==(int n)
			{
				return (bool)(this->n == n);
			}
			Number& operator[](Number& a)
			{
				this->n += a.getN();
				return *this;
			}
			Number* operator->()
			{
				return this;
			}
			Number& operator,(int n)
			{
				this->n = n;
				return *this;
			}
			Number& operator=(int n)
			{
				this->n = n;
				return *this;
			}
			Number operator-(Number& a)
			{
				return Number(-a.n);
			}
			Number &operator()(int n)
			{
				this->n = n;
				return *this;
			}
			Number &operator()(const Number& a)
			{
				this->n = a.n;
				return *this;
			}
			friend ostream& operator<<(ostream&, const Number&);
			friend istream& operator>>(istream&, Number&);
			/* operator->  moudleTest.cpp*/
	};
	int getN(const Number& a)
	{
		// 友元函数有权访问 private protected 成员
		return a.n;
	}
	Number Number::operator-(const Number &bc) const
	{
		Number b(this->n - bc.getN());
		return b;
	}

	Number operator+(const Number& a, const Number& b)
	{
		Number c;
		c.n = a.n + b.n;
		return c;
	}

	Number Number::operator--(int)
	{
		Number b(*this);
		--this->n;
		return b;
	}
	Number Number::operator++(int)
	{
		Number b(*this);
		++this->n;
		return b;
	}
	Number& Number::operator++()
	{
		++this->n;
		return *this;
	}
	Number& Number::operator--()
	{
		--this->n;
		return *this;
	}

	ostream& operator<<(ostream& o, const Number& n)
	{
		o << (int)n;
		return o;
	}
	istream& operator>>(istream& i, Number& n)
	{
		i >> n.n;
		return i;
	}

	class SimpleClass : public BaseClass //, public Number // 多继承
	{
		/*
		 * 继承方式
		 * public 公有继承 基类(BaseClass)中 public protected 不变，private 无法访问
		 * protected 保护继承 public 和 protected 变成 protected
		 * private 私有继承 public 和 protected 变成 private
		 */
		protected:
			string message;
		public:
			SimpleClass()
			{
				cout << "SimpleClass Constructor: " << id << endl;
				cout << setfill(' ') << setw(6) << getId() \
					<< setw(6) << ClassTest::getId(*this) \
					<< setw(6) << BaseClass::getId() << endl; // cout << setfill('*') << setw(5) << id << endl;
				//cout << __super::getId() << endl; // VC++
				//cout << privateId << endl; // 报错，已不可访问
				/* 
				 * 访问      public protected private
				 * 同一个类  yes    yes       yes
				 * 派生类    yes    yes       no
				 * 外部的类  yes    no        no
				 */
				message = "id: " + to_string(id);
			}
			SimpleClass(string& message)
			{
				cout << "SimpleClass Constructor: " << id << endl;
				this->message = message;
			}
			~SimpleClass()
			{
				cout << "SimpleClass Destructor: " << id << endl;
			}
			void setId(const int i)
			{
				this->id = i;
			}
			virtual string getMessage() const
			{
				return message;
			}
			//virtual string getMessage() = 0; // 纯虚函数
	};
	class StatusClass : public SimpleClass
	{
		public:
			virtual string getMessage() const // 已经默认virtual 可以不加virtual
			{
				return ("status: " + message);
			}
	};
	class ErrorClass : public SimpleClass
	{
		public:
			virtual string getMessage() const
			{
				return ("error: " + message);
			}
	};

	class N2 : public Number
	{
		public:
			//friend N2 * operator new()
			N2(int);
			N2();
			void *operator new(size_t); // 默认 static
			void *operator new(size_t, void *); // 默认 static
			void *operator new(size_t, int);
			void operator delete(void *);
	};
	N2::N2()
	{
	}
	N2::N2(int i)
	{
		(void)i;
	}
	void *N2::operator new(size_t size)
	{
		return std::malloc(size);
	}
	void *N2::operator new(size_t size, void *p)
	{
		cout << "placement new" << endl;
		(void)size;
		return p;
	}
	void *N2::operator new(size_t size, int i)
	{
		cout << "i: " << i << endl;
		return std::malloc(size);
	}
	void N2::operator delete(void *p)
	{
		free(p);
	}
	struct AAA
	{
		// public: // default
		int a;
		AAA(){}
		~AAA(){}
		int get() const
		{
			return a;
		}
	};
}
using namespace ClassTest;
using ClassTest::BaseClass;

void classTestF1(const Number& n)
{
	std::cout << n << '\t';
}
void classTestF2(Number& n)
{
	std::cout << n << '\t';
}
void classTestF3(Number n)
{
	std::cout << n << '\t';
}

void classTest1()
{
	BaseClass b;
	cout << "id: " << b.getId() << endl;
}
void classTest2()
{
	Number n1(5); // 构造函数
	Number n2 = 3; // 运算符重载
	Number n3(n2); // 拷贝函数
	Number i;
	classTestF1(n1);
	classTestF2(n1);
	classTestF3(n1); // 拷贝
	cout << endl;
	cout << n1.getN() << endl;
	n1.add().add(3).add(5);  // + 1 + 3 + 5
	cout << n1.getN() << endl;
	n3 = n1 + n2; // 14 + 3
	cout << n3.getN() << endl;
	n1 = 1;
	n1 += (++n1) + (n1++); // ...
	cout << (int)n1 << endl;
	n1 << n2 << n3 << 5;
	cout << n1 << endl;
	n1(5);
	cout << n1 << endl;
	// n1[n2] // n1->getN()
	N2 *n4 = new N2;
	N2 *n5 = new(n4) N2();
	(void)n5;
	// delete n5;
	delete n4;
	i = 1;
	n1 = (++i) + (++i); // 经典
	cout << n1 << endl; // 6
	i = 1;
	n1 = (++i) + (i++);
	cout << n1 << endl;
	i = 1;
	n1 = (i++) + (++i);
	cout << n1 << endl;
	i = 1;
	n1 = (i++) + (i++);
	cout << n1 << endl;
	n1 = (n1, 1, 1 + 1, 2 + 3);
	// n1, 1, 2, 3;
	cout << n1 << endl; // 5
	cout << endl;
}
void classTest3()
{
	SimpleClass s1;
}
void classTest4Cout(SimpleClass *s)
{
	cout << s->getMessage() << endl;
}
void classTest4()
{
	SimpleClass s1;
	StatusClass s2 = StatusClass();
	ErrorClass s3;
	SimpleClass *s;
	cout << "s1: " << s1.getMessage() << endl;
	cout << "s2: " << s2.getMessage() << endl;
	cout << "s3: " << s3.getMessage() << endl;
	s = &s2;
	cout << "s2: " << s->getMessage() << endl;
	cout << endl << endl;
	classTest4Cout(&s1);
	// 虚函数 多态
	classTest4Cout(&s2); // classTest4Count(dynamic_cast<SimpleClass*>(&s)); // safe
	classTest4Cout(&s3);

}
// class A{};
// class B: virtual public{};
// class B: virtual public{};
// class D: public A, public B{} // not confict with
void classTest()
{
	//cout << new char[] {'y', 'y', 'y' , '\0'} << endl;
	classTest1(); // 自动释放 
	BaseClass *b = new BaseClass(); // 自己 new 的要自己释放
	cout << "getId: " << b->getId() << endl;
	cout << "getId: " << getId(*b) << endl; // 友元函数
	delete b;
	cout << BaseClass::getStaticId() << endl; // 静态方法 // 只能使用静态变量，不需要实例化
	classTest2();
	classTest3();
	classTest4();
	// cpp11 // module
}



