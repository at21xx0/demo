#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* note   demo */
/* 运行 make note */
extern int extra; /* 此变量在函数内可看做普通的全局变量，下同 */
int e0=1,e4=5;
int e1=2,e2=3;
static int e3=4;
void func_0(){
	printf("第一个C程序\n");
	/* printf("xjxjxjx"\
	 * xxxxx\
	 * xxxx); 可以方便阅读 */
	printf(\
			"#include <srdio.h>\n\n"\
			"int main(void){"\
			"printf(\"hello, world!\\n\");\n\n"\
			"return 0;"\
			"\n");
}
void func_1(void){
	printf("我的笔记\n");
	printf("\n");
	//我是注释
	/* 我是注释
	 * 可跨行 
	*/
}
void func_2(){
	/*头文件:
	 * #include <stdio.h>
	 * 记录函数的文件，这样写能导入函数 如  printf
	 * int main(){}
	 * 函数的形式，此处int不可替换
	 * int main(int argc,char **argv){}
	 * 函数的形式，可接受命令行参数(./a.out 6448 abcd)。其中argc 是参数个数，argv是参数字符串数组
	 * int main(){/ * 代码 * / return 0;}
	 * main 函数是准备好后执行的第一个函数，其中 return 0; 中断函数并返回int类型的 0
	 * */
	/*令牌
	 * printf("hello, world!\n");
	 * 即
	 * printf
	 * (
	 * "hello, world!\n"
	 * )
	 *
	 * 是一种固定结构
	 * */
}
void func_3(){
	/* 数据类型 */
	/* 1 B = 1 byte = 8 bits */
	/* B KB MB GB TB PB 进率是1024 */
	int a; /* 整数 (2 or 4 byte)*/
	short b;/* 整数 (2 bytes)*/
	long c; /* 整数 ，范围比 int 大 (4 bytes) */
	/* 不同系统int尺寸不同，具体可sizeof(int) */
	 auto int d=5; /* 相当于int d=5; */
	char e; /* 字符串变量 (1 byte)*/
	float f; /* 浮点数 */
	double g=0.6457; /* 双精度浮点数 */
	unsigned int h; /* 正整数 */
	unsigned short i; /* 正short整数 */
	unsigned long j; /* 正long整数 */
	long int k; /* 更大的整数 */
	long long l; /* 范围更大的整数 */
	unsigned char m; /* 正char整数 */
	const int n; /* 常量，值不会被改变 */
	long double o; /* 范围更大的double */
	/* byte p; */
	
	/* void *z;*/ /* 无类型指针 */
	/* 通常用在不返回函数前或不接受参数的函数中(如 void test_0(void){/ * 代码 * /} )
	 * 或是用作代替指针 */
	/* extra */
	/* char (-128,127)或(0,255)
	 * unsigned char (0,255)
	 * signed char (-128,127)
	 **/
	size_t lu=5; /* 32位无符号整数 */
	/* 通常未赋值时为随机值 */
	printf("类型:占用空间(byte);格式化显示:结果\n"\
			"int:%lu;%%d:%d\n"\
			"short:%lu;%%hd:%hd\n"\
			"long:%lu;%%ld:%ld\n"\
			"char:%lu;%%d:%d\n"\
			"char:%lu;%%c:%c\n"\
			"float:%lu;%%f:%f\n"\
			"double:%lu;%%lf:%lf\n"\
			"unsigned int:%lu;%%u:%u\n"\
			"unsigned short:%lu;%%hu:%hu\n"\
			"unsigned long:%lu;%lu\n"\
			"long int:%lu;%%ld%ld\n"\
			"long long:%lu;%%lld:%lld\n"\
			"unsigned char:%lu;%u\n"\
			"const int:%lu;%%d:%d\n"\
			"long double:%lu;%%Lf:%Lf\n"\
			,sizeof(int),a\
			,sizeof(short),b\
			,sizeof(long),c\
			,sizeof(char),e\
			,sizeof(char),e\
			,sizeof(float),f\
			,sizeof(double),g\
			,sizeof(unsigned int),h\
			,sizeof(unsigned short),i\
			,sizeof(unsigned long),j\
			,sizeof(long int),k\
			,sizeof(long long),l\
			,sizeof(unsigned char),m\
			,sizeof(const int),n\
			,sizeof(long double),o\
			);
	/* 额外的，格式化显示 */
	/* %md m为指定输出字符串的宽度 如%7d*/
	//int a
	//double g
	//char e
	char s[]="hello, world!";
	wchar_t t[]=L"hello, work?";
	printf("extra"\
			"%%a(%a) 浮点数、十六进制和p-计数法（c99）\n"\
			"%%A(%A) 浮点数、十六进制数字和p-记法（c99）\n"\
			"%%c(%c) 字符串(单个char)\n"\
			"%%C(%C) 一个宽ISO字符\n"\
			"%%d(%d) 有符号十进制整数 (%%ld,%%Ld 长    %%hd 短)\n"\
			"%%e(%e) 浮点数 e-记数法\n"\
			"%%E(%E) 浮点数 E-记数法\n"\
			"%%f(%f) 单精度浮点数(十进制)(%%.nf n表示小数点后位数)\n"\
			"%%g(%g) %%e或%%f\n"\
			"%%G(%G) %%e或%%f\n"\
			"%%i(%i) %%d\n"
			"%%o(%o) 八进制\n"\
			"%%p(%p) 指针\n"\
			"%%s(%s) 对应字符串数组(char*) (%%s=%%hs=%%hS 窄字符)\n"\
			"%%S(%S) 对应宽字符串(WCAHR*) (%%ws=%%S 宽字符)(L\"hello\")\n"\
			"%%u(%u) 无符号整数(unsigned int)\n"\
			"%%x(%x) 十六进制(字母小写)\n"\
			"%%X(%X) 十六进制(字母大写)\n"\
			"%%%%(%%) 百分号\n"\
			"%%hd;%%hhd;%%lld 2,1,8字节\n"\
			"extra: lu 32位无符号整数llu64位无符号整数\n"\
			,g,g,e,e,a,g,g,g,g,g,a,a,&a,s,t,(unsigned int)a,a,a);

	/*  通常占用空间越大，数据范围也越大  */
}
int view_extern_e0(void){
	/* 查看全局变量 e0 的值 */
	extern int e0;
	return e0;
}
void change_extern_e0(int i){
	/* 改变全局变量 e0 的值 */
	extern int e0;
	e0=i;
}
int view_extern_e1(void){
	extern int e1;
	return e1;
}
void change_extern_e1(int i){
	extern int e1;
	e1=i;
}
int view_extern_e2(void){
	extern int e2;
	return e2;
}
void change_extern_e2(int i){
	extern int e2;
	e2=i;
}
int view_extern_e4(void){
	extern int e4;
	return e4;
}
void change_extern_e4(int i){
	extern int e4;
	e4=i;
}
void func_4(){
	/* 变量 */
	/*type variable_list;
	 * type 如 int char long*   long long  long double 自定义变量
	 * variable_list 为变量名称
	 * variable_list[] 表示数组
	 * */
	char a,b=45; /* 通常是一字节 */
	char c;
	int d=3,e,f=5; /* 常用 */
	float g=5.6,h=4.5; /* 单精度浮点数 一位符号八位指数三十二位小数 */
	double i=446648776678787.466464; /* 单精度浮点值 一位符号十一位指数五十二位小数 */
	const int j=5; /* 常量值不可被改变 */
	/* #define  k=6 */ /* 另一种定义常量的方式 最好写在函数外 */
	/* void j 无意义报错 */
	/* 显示 */
	printf("a:%d,b:%d,c:%d,d:%d,e:%d,f:%d,g:%f,h:%f,i:%f\n",a,b,c,d,e,f,g,h,i);
	/*lvlaue=rvalue 将左变量赋右值
	 * 即把左侧变量内容改变为右侧内容
	 * 是改变变量地址对应内容的值
	 */
	printf("d:%d\n",d);
	d=6;
	printf("d:%d\n",d);
	d=f;
	printf("d:%d\n",d);
	/* 关于变量声明
	 * 第一次声明变量才算声明变量
	 * 但不同函数间可以申请相同变量名的变量(比如在函数a 声明 int i; 在函数b也可以)，但是并不相同
	 * 当声明一个不存在的变量时，是声明并定义。如 int i;
	 * 当声明一个存在的变量时(通常是外部变量)，是声明变量但不定义
	 */
	int e0; /* 声明并定义 int 型变量 i，且不引用外部同名变量 也是局部变量(仅在所在的函数中有效) */
	extern int e1; /* 声明 int 型变量 实际上是引用外部变量 */
	printf("函数内:e0:%d;e1:%d;e2:%d;\n",e0,e1,e2); /* 直接引用e2默认外部变量 extern int e2*/
	printf("全局变量:e0:%d;e1:%d;e2:%d;\n",view_extern_e0(),view_extern_e1(),view_extern_e2());
	change_extern_e0(0);
	change_extern_e1(4);
	e2=7;
	printf("函数内:e0:%d;e1:%d;e2:%d;\n",e0,e1,e2);
	printf("全局变量:e0:%d;e1:%d;e2:%d;\n",view_extern_e0(),view_extern_e1(),view_extern_e2());
	e0=9;
	printf("函数内:e0:%d;e1:%d;e2:%d;\n",e0,e1,e2);
	printf("全局变量:e0:%d;e1:%d;e2:%d;\n",view_extern_e0(),view_extern_e1(),view_extern_e2());
	/* extra (写法)*/
	int z=9;/* 下面 printf(参数同) */
	int q=074; /* 八进制 */
	printf("显示:%d,%d\n",z,q);
	printf("十进制:%d\n"\
			"八进制(0752):%d\n"\
			"十六进制(0xFA6872):%d\n"\
			"十六进制(0x6c3d):%d\n"\
			"无符号整型unsigned(256L):%u\n"\
			"长整数(999999999L)%ld\n"\
			"混合(0x8feeLU):%lu,(0x3B4Flu):%lu\n"\
			"浮点数(3.14159):%f\n"\
			"long double(314159E-5L):%Lf\n"\
			"extra(0xabcd):%X\n"\
			,42,0752,0x7B2C,0x6c3d,256U,999999999L,0x8feeLU,0x3B4Flu,3.14159,314159E-5L,0xabcd);
	printf("%s%s%c"\
			"\\\\:\\\n"\
			"\\':'\n"\
			"\\\":\"\n"\
			"\\\?:\?\n"\
			"\\a:报警铃声\n"\
			"\\b:退格键\n"\
			"\\f:换页符\n"\
			"\\n:换行符\n"\
			"\\r:回车符\n"\
			"\\t:水平制表符\n"\
			"\\v:竖直制表符\n"\
			"\\ooo:一到三位的八进制数\n"\
			"\\xhh:一个或多个数字的十六进制数\n"\
			,"字符","串",'\n');
	// const #define 都可用于定义字符串常亮或数字常量

}
void static_test(){
	static int i=0; /* 我只被初始化一次 */
	printf("%d\n",i);
	i=i+1;
}
static int func_add1(int a,int b){
	/* 此函数不可被外部调用 */
	return a+b;
}
extern int func_add2(int a,int b){
	/* 此函数可以被外部调用 */
	return a+b;
}
int func_add3(int a,int b){
	/* 此函数可以被外部调用 */
	return a+b;
}
void func_5(void){
	/* 存储类 */
	int a; /* 等效下一个 */
	auto int b; /* 默认的 等效上一个 */ /* auto 只能修饰局部变量*/
	register int c; /* 变量不在RAM中，而在寄存器中，只用于需要快速访问的变量，没有内存地址，即不能使用&b */
	static int d=9; /* 在函数中只初始化一次 */
	printf("e3:%d\n",e3); /* 全局变量作用域只在文件中 (xxx.c) */
	static_test();
	static_test(); /* 函数中a没有初始化 */
	static_test();
	static_test();
	printf("%d,%d,%d\n",func_add1(3,2),func_add2(3,2),func_add3(3,2));
	/* 外部调用例
	 * #include "t.h"  / * 头文件写在开头 * /
	  * printf("3*5=%d\n",t(3,5));
	 */
	extern int e0;/* 对于无法初始化的变量，会把变量名指向一个之前定义过的存储位置 比如引用其他c文件中的函数(未定义函数)(不同文件的变量共享)(头文件xxx.h也能做到) */
	printf("e0: %d\n",e0); /* 这里是外部变量的值 */
	/* 通常用extern 引用全局变量 */
	int e4;
	printf("e4: %d\n",e4); /* 这里是局部变量的值，未初始化，所以为随机值 */
	printf("e4: %d\n",view_extern_e4());
}
void func_pp_test(){
	int a=5,i=0,b=0,m=21,n=5;
	char d[14][6]={"a++","++a","a--","--a","a=a+b","a+=b","a=a-b","a-=b","a=a*b","a*=b","a=a/b","a/=b","a=a%%b","a%%=b"};
	printf("简便写法\n");
	printf("赋值 运算输出的值(仅仅前四个) 运算后的值\n");
	for(i=0;i<14;i++){
		if(i<4){
			printf("a=%d; ",n);
			a=n;
		}else{
			printf("a=%d;b=%d;\n",m,n);
			a=m,b=n;
		}
		switch(i){
			case 0: b=a++;break;
			case 1: b=++a;break;
			case 2: b=a--;break;
			case 3: b=--a;break;
			case 4: a=a+b;break;
			case 5: a+=b;break;
			case 6: a=a-b;break;
			case 7: a-=b;break;
			case 8: a=a*b;break;
			case 9: a*=b;break;
			case 10: a=a/b;break;
			case 11: a/=b;break;
			case 12: a=a%b;break;
			case 13: a%=b;break;
		}
		if(i<4){
			printf("%s:%d; a:%d\n",d[i],b,a);
		}else{
			printf("%s;\na:%d; b:%d\n",d[i],a,b);
		}
	}
}
char *func_6z(int a,char *s,int c){
	/* 数字转二进制 */
	static const char b[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int d=1;
	int i=0;
	int n=0;
	char e;
	while(a>0){
		s[i++]=b[a%c];
		a/=c;
	}
	s[i--]='\0';
	while(n<=i/2){
		e=s[n];
		s[n]=s[i-n];
		s[i-n]=e;
		n++;
	}
	/*
	for(char *m=s,*n=s+strlen(s)-1;m<n;m++,n--){
		e=*m;
		*m=*n;
		*n=e;
	}*/
	return s;
}
//void func_e0(){
int func_6y(char *s,int c){
	/* 二进制转数字 */
	static const char b[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int a=0,i=0,n=0,d=1;
	while(s[i]!='\0')i++;i--;
	printf("%d\n",i);
	for(;i>-1;i--){
		for(n=0;s[i]!=b[n]&&b[n]!='\0';n++);
		a+=n*d;
		d*=c;
	}
	return a;
}
void func_6a(){
	/* 位运算测试 */
	int a=0,b=0,i,k;
	char c[4][8]={"与","或","或异","取反"};
	char d[4][3]={"&","|","^","~"};
	char s[8][8];
	printf("运算:符号 举例");
	for(i=0;i<4;i++){
		printf("%s运算(%s)\n",c[i],d[i]);
		a=b=0;
		while(b<2){
			switch(i){
				case 0: k=a&b;break;
				case 1: k=a|b;break;
				case 2: k=a^b;break;
				case 3: k=~a;break;
			}
			if(i==3){if(b==0)printf("%s%d:%d\n",d[i],a,k);}else
			printf("%d%s%d:%d\n",a,d[i],b,k);
			a++;
			if(a==2){a=0;b++;}
		}
	}
	/*左右位移*/
	a=04;b=1;i=2;/* a=4; (八进制) */
	/* itoa 貌似消失了 */
	printf("向左位移\n"\
			"%s<<%d: %s\n"\
			"%s<<%d: %s\n"\
			"向右位移\n"\
			"%s>>%d: %s\n"\
			"%s>>%d: %s\n"\
			,func_6z(a,s[0],2),b,func_6z(a<<b,s[1],2)\
			,func_6z(a,s[2],2),i,func_6z(a<<i,s[3],2)\
			,func_6z(a,s[4],2),b,func_6z(a>>b,s[5],2)\
			,func_6z(a,s[6],2),i,func_6z(a>>i,s[7],2)\
	      );

}

void func_6(){
	int a=40;
	int b=5;
	char y[]="yes";
	char n[]="no";
	/* lvalue=rvalue */
	/* 左面可以是变量、指针
	 * 右可以是常量，变量，表达式
	 */
	a=b;
	a=b+5;
	a=21;
	/* 运算符号 */
	printf("运算:值\n"\
			"a: %d;b: %d\n"\
			"加(a+b):%d\n"\
			"减(a-b):%d\n"\
			"乘(a*b):%d\n"\
			"除(a/b):%d\n"\
			"除法余数(a%%\b):%d\n"\
			,a,b,a+b,a-b,a*b,a/b,a%b);
	func_pp_test(); /*额外的 a++ ++a 输出值*/ /* a+=b; 等效于 a=a+b; +*-/% 通用 */
	/* 关系符号 */
	printf("比较:(是/否)\n"\
			"a: %d;b: %d\n"\
			"相等(a==b)?%s\n"\
			"不相等(a>b)?%s\n"\
			"大于(a>b)?%s\n"\
			"小于(a<b)?%s\n"\
			"大于等于(a>=b)?%s\n"\
			"小于等于(a<=b)?%s\n"\
			,a,b\
			,(a==b)?y:n\
			,(a==b)?y:n\
			,(a>b)?y:n\
			,(a<b)?y:n\
			,(a>=b)?y:n\
			,(a<=b)?y:n\
		);
	/* 逻辑运算符号 */
	a=0;b=1;// 空指针(NULL) 0 为假，否则为真(是否为空)
	// 即真假相当于是否为 0 ，0为假
	//连接几个或多个关系式或值 如 a>b && a!=0     a!=b || a    !a
	//通常逻辑运算符号和关系符号都可用在判断性语句中，如if(语句){/ * 代码 * /} while(语句){} i=(语句)?a:b;(赋值，真a，假b)
	printf("运算:值\n"\
			"a=%d;b=%d\n"\
			"(a)?%s;(b)?%s\n"
			"左右都为真(a&&b)?%s\n"\
			"左右至少有一个为真(a||b)?%s\n"\
			"是否为假(!a)?%s\n"\
			"复合\n"\
			"(a==0&&b==1):%s\n"\
			"(1||0||0):%s\n"\
			"运算顺序从左到右，但编译器报错\n"\
			"(0&&1&&1):%s\n"\
			,a,b\
			,(a)?y:n\
			,(b)?y:n\
			,(a&&b)?y:n\
			,(a||b)?y:n\
			,(!(a))?y:n\
			,(a==0&&b==1)?y:n\
			,(1||0||0)?y:n\
			,(1&&1&&0)?y:n\
		);
	/* 位运算 */
	/* 位运算相当于把变量数字对齐，每一位进行计算
	 * 例如7 1111 8 10000 7|8:(对每一位进行|运算)
	 * 即 1111|10000=11111=15
	 * (但并不代表 | 是加法 )
	 */
	func_6a();/* 例子 */
	/* extra */
	/*sizeof();返回变量的大小
	 * * 指向一个变量
	 * & 返回变量地址
	 * ?:条件表达式 如 c=(a>b)?a:b;  选择ab中较大的数字
	 */
}
void func_7(){
	int i=5;
	/* 判断 */
	/* if(表达式){代码}else if(表达式){代码}else{} */
	/* 表达式中，将任何非零的值设定为假(false)其他为真 */
	printf("i: %d\n",i);
	if(i==5){printf("i=5\n");}
	if(i!=4)printf("i!=4\n");/* 这样写只会执行到; (可以用逗号隔开)*/
	if(i==4){printf("i=4\n");/* 不执行，因为i不等于4*/}else /*{ 可以省略 */ printf("i!=4\n");/* } */ /* 执行，因为上个if没有执行*/
	if(i<7){printf("i<7\n");if(i<6)printf("i<6\n");/* 语句可以嵌套*/
	}else if(i<7){
		printf("i<7\n");/* 不执行，因为上个if执行 */
	}else{
			printf("i=7\n");/* 不执行，因为上面有if执行*/
	}
	/* switch case 语句*/
	i=3;
	int c=6;
	const int e=1;
	switch(i){
		case 0: c=i*5;break;
		// case e: c*=100;break;/* 常量可以用作case 的值*/
		case 2: c=2;break;
		case 3: i=4,printf("未break;\n");/* 有时不用break会出bug;*/ /* 比如用switch(i) 给i赋值时*/
		case 4: i=5,printf("switch仍然在运行\n");break;
		case 5: printf("switch停止\n");break;
		default: c=0,printf("err!\n");break;/* 默认的处理方式，未break;执行 */
	}
	i=0;
	c=5;
	switch(i){
		case 1: printf("1;\n");break;
			switch(c){/* 位置不对，不被执行 */
				case 0: printf("c=0\n");break;/* switch 可以嵌套 */
				case 5: printf("c=5\n");break;
			}
		case 0: printf("0;\n");
			switch(c){
				case 5: printf("extra: c=5\n");break;
		}
	}
}
long func_8_add(long a,long b){
	long c;
	while(1){
		c=a^b;
		if((b=(a&b)<<1)==0)break;
		a=c;
	}
	return c;
}
void func_8(){
	int i;
	int n;
	/* 循环 */
	/* while(条件){循环体} */
	i=0;
	while(i<5){
		printf("i: %d\n",i);
		i++;
	}
	i=0;
	while(i++<5){printf("i: %d\n",i);/* 这里i从1开始是因为表达式中i++先被执行一次 */}
	/* for */
	/* for ( init; condition; increment ) {statement(s);}
	 * init只在开始时执行一次，condition是判断条件，条件不为0 for语句才能继续执行 increment在tatement执行完成后执行 */
	for(i=0;i<5;i++){
		printf("i: %d\n",i);
	}
	/*for 相当于 第一个例子while */
	for(i=5;i>5&&i<11;i++){
		printf("不和条件不执行\n");
	}
	i=10;
	for( ; ; ){printf("i: %d\n",i);if(i<6)break;/* 跳出循环 */i--;}/* 可以省略部分参数，*/
	/* do while循环 do{循环体}while(条件)*/
	i=1;
	do{
		printf("i: %d\n",i);
		i*=2;
	}while(i<1025);
	i=23;
	do{printf("i: %d\n",i);/* 这里先被执行一次，甚至while 不符合条件 */
	}while(--i>20);
	/* 相当于 while(1){循环体if(!())break;}*/
	/* goto 语句 */
	i=5;
	tag_1:i++;/* goto不是一行，而是一直向下执行 */ /* 这里开始被执行一次 */
	      if(i==6)goto tag_1; /* 向上跳转 */
	      if(i==7)goto tag_2; /* 向下跳转 */
	      i=0;
	      tag_2:
	printf("i:%d\n",i); /* i=7 表示执行正常 */
	/* 但跨函数问题和难以追踪控制，不建议使用，可以用其他写法代替 */
	/* break; 和continue; 语句*/
	/* break; continue; 可用于 while,for,do while 语句中 */
	for(i=0,n=1;i<100;i++,n++){
		printf("i: %d n: %d \n",i,n);
		while(1){
			if(n>9){n=-1;break;}
			if(n>6)break; /* 跳出循环 (单层) */
			n++;
			printf("n1: %d\n",n);
			if(n>4)continue; /* 使用后，下面语句被跳过，不执行 (只适用于单层) */
			printf("n2: %d\n",n);
		}
		if(n==-1)break;/* 跳出循环 */
	}
	printf("i: %d n: %d \n",i,n);
	//可以用循环和位运算做一个加法
	printf("i: %d %ld\n",258+1345,func_8_add(258,1345));
}
void func_9a(){
	/* 没有参数，没有返回值得函数 */
	printf("func_9a();\n");
}
int func_9b(){
	/* 返回int 值*/
	int a=5;
	return a;// 或 return 0;
}
int func_9c(int i){/* 一个返回接受到int类型数据的函数 */return i;}
int func_9d(int a,int b){
	return a+b;
}
char *func_9e(char a[]){return a;}
char *func_9f(char *a){return a;}

void func_9(/* void 可有可无 */){
	int a,b;
	char c[10]="and me!";
	char *m;/* 字符串指针 */
	/* return_type function_name( parameter list ){body of the function} */
	/* 函数返会值得数据类型 函数名称 (函数参数列表){函数体}*/
	/* 函数参数是列表，调用时按照顺序调用 参数值与原来调用时相同，但指针地址不同*/
	/*  函数返回值的数据类型由函数名前的数据类型决定 由 return 语句返回*/
	func_9a(); /* 此函数没有参数，也没有返回值 */
	func_9b(); /* 可以不接收函数返回值 */
	a=func_9b(); 
	printf("a: %d\n",a);
	printf("func_9c(%d): %d\n",a,func_9c(a));
	b=func_9c(a)%2+20; /* b=5%2+20 */
	printf("b: %d\n",b);
	printf("a+b: %d\n",func_9d(a,b));
	m=c;
	/* 传递字符串指针 */
	if(func_9e(c)==func_9e(m)&&func_9e(m)==func_9f(c))printf("testok\n");
}
int func_10a=0,func_10b=1,func_10c=2;/* 全局变量 */
/* 全局变量会初始化，局部变量不会 */
int func_10d(int);//形式参数
/* 可用在main函数 这样就不必把所有函数都写在main前了 */
void func_10e(){printf("%d\n",func_10d(4));}
int func_10d(int a){return a+1;}
void func_10(){
	/* 作用域 */
	int i=0; /* 局部变量 */
	/* 局部变量可在作用域(函数)内读取/修改 */
	/* 局部变量作用域仅在函数内 */
	printf("i:%d\n",i);
	i=5;
	printf("i: %d\n",i);
	int func_10a; /* 也是局部变量，因为没有在前面加extern */
	printf("i: %d\n",func_10a); /* 不等于0，因局部变量未赋值为随机值*/
	printf("i: %d\n",func_10b);/* 全局变量 */
	extern int func_10c; /* 全局变量 */
	printf("i: %d\n",func_10c);
	/* 形式参数 */
	int func_10d(int /*a 可有可无*/);
	printf("i:%d\n",func_10d(6));
	func_10e();

}
int *func_11a(int a[],int *b,size_t size){
	/* 函数调用 */
	/* 数组以指针形式传递 */
	static int c[3]; /* 没有static报错，使用时容易出bug，传入指针或是动态申请内存可以解决 */
	int i;
	if(a[0]==b[0])printf("yes\n");/* 值 */
	if(a==b)printf("yes\n");/* 指针 */
	printf("%lu %lu %lu \n",size,sizeof(/* a *//* 显示大小为int *类型大小，(报错)*/int *),sizeof(b)); /* 这里已经无法获取数组大小了(sizeof(array)/sizeof(type)) */
	for(i=0;i<3;i++)c[i]=a[i];
	/* 返回值 */
	return c; /* 通常函数结束时，内存会被释放，局部变量也被释放，无法确定长度的数组以指针形式返回 */	
}
void func_11(){
	/* 数组 */
	/* 数组是连续内存空间(大小: 长度*sozeof(数据类型))，数组相当于非数组为一个连续的空间(容器)，指针加减括号的使用都会造成指针的某个位置(第几个) */
	//type arrayName [ arraySize ]; //type为数据类型arrayName 为变量名，arratSize是数组容纳type类型变量个数。 占用内存 arraySize*sizeof(type) 
	int a[6];/* 数字>0，且为常数，动态申请用malloc */
	/* 数组申请的格式，申请连续的内存，[]内的数字决定数组长度，使用[]或*()时数字从0开始 */
	if(a[0]==*a&&a[1]==*(a+1)&&*a==*(a+0))printf("yes\n");
	int i;
	long b[2]={0}; /* 每个都等于0 */
	char *m;
	long *l;
	int e[6][2]={{4,2},{1,3},{21,2},{7,47},{9,1},{97,100}};/* 嵌套数组 */
	char d[5]={'c','h','a','r','\0'};
	int *c;
	/* 访问元素 */
	a[0]=6;/* 第0个 */
	a[1]=4;/* 第1个 */
	a[4]=47;/* 第4个 */
	i=3;
	a[i]=7;/* 第i个 */
	a[++i]=21; /* 第++i个 */
	for(i=0;i<6;i++)
		printf("i[%d]: %d\n",i,a[i]);/* 遍历 */
	/* 传递 */
	c=func_11a(a,a,sizeof(a));
	printf("%d %d %d\n",c[0],c[1],c[2]);
	printf("%s\n",d);
	/* 实际上字符串也是数组 */
	printf("%c%c%c%c\n",d[0],d[1],d[2],d[3]);
	printf("%d %d %d %d\n",a[0],*a,a[1],*(a+1));
	/* extra 指针 */
	printf("%lu %lu\n",sizeof(int),sizeof(a));
	printf("%p-%p=%lu\n",b+1,b,sizeof(long));
	m=(char *)a;
	c=(int *)(m+1);
	l=(long *)a;
	printf("%d %d %d %ld\n",a[0],a[1],c[0],(*l)>>8);
	//printf("%ld\n",&a[1]-&a[0]);
}
void func_12(){
	/* 枚举 */
	/* 枚举可理解为自动给变量赋值(连续)的方法 */
	/* 它可以使代码更简洁 */
	// enum 名称 {常量名称/ *=0初始值 * /,名称,名称}
	int i=2;
	enum DAY /* 例子 */
	{
		MON=1, TUE, WED, THU, FRI, SAT, SUN
	};
	enum DAY day;
	day=MON;
	/* 转换 */
	/* day=(enum DAY)i*/
	printf("day: %d %d\n",day,MON);
	switch(day){
		case MON: printf("MON\n");break;
		case TUE: printf("TUE\n");break;
		case WED: printf("WED\n");break;
		case THU: printf("THU\n");break;
		case FRI: printf("FRI\n");break;
		case SAT: printf("SAT\n");break;
		case SUN: printf("SUN\n");break;
	}
}
void func_13swp(int *a,int *b){
	int c;
	c=*a;
	*a=*b;
	*b=c;
}
int func_13add1(int a){return a+1;}
char *func_13z(char *c){
	c++; /* 指针+1并返回 */
	return c;
}
void func_13r(char *(*a)(char *),int (*b)(int),void (*c)(int *a,int *b)){
	int i=5,u=4;
	char w[]="?ab";
	c(&i,&u);
	printf("%d %d %d %s\n",i,u,b(u),a(w));
}
void func_13(){
	/* 指针 */
	/* 指针为纪录了变量内存地址的指向位置的值 */
	/* 指针的值是变量的内存地址 */
	/* 相对的，变量是指向内存地址的值 */
	int i=5; /* int 类型变量 i */
	int u=4;
	int *a; /* int *  指针变量，指向int */
	int *b=NULL; /* NULL 为空指针 */
	int **c; /* 指向指针的指针 */
	int d[16]; /* 数组 */
	int *y[4]; /* 指针数组 */
	char *w="_word";
	a=&i;/* &用于输出变量指针*/
	c=&a;
	b=&u;
	/* 指针可以跨函数 */
	printf("p: %p %p %p %p\n",a,b,c,&c);
	/* 不同指针占用内存大小相同 */
	printf("%lu %lu %lu %lu %lu %lu %lu\n",sizeof(int *),sizeof(char *),sizeof(long *),sizeof(short *),sizeof(long double *),sizeof(FILE *),sizeof(int **));
	/* 显示 */
	u=*a;
	if(a==b)printf("yes\n");/* 指针的值相同，指针指向同一个变量 */
	if(*a==*b)printf("yes\n");/* 指针指向的值相同 */
	printf("v: %d %d %d %d\n",i,u,*a,**c);
	/* 更改 */ 
	a=&i;b=&u;
	*b=15; /* 赋值 */
	printf("i: %d u: %d \n",i,u);
	func_13swp(a,b);
	printf("i: %d u: %d \n",i,u);
	func_13swp(&i,&u);
	printf("i: %d u: %d \n",*a,*b);
	if(a[0]==*a)printf("yes\n");/* 另一种写法，也可以指向地址 */
	d[0]=0;
	d[1]=42;
	a=&d[0];
	b=&d[1];
	printf("%d %d\n",(*a)++,(*b)++);
	printf("%d %d\n",a[0],a[1]);
	/* 指针加减 */
	for(i=0;i<16;i++)d[i]=i*i;
	a=d;
	printf("*a: %d\n",*a);
	printf("*(a+1): %d\n",*(a+1));
	for(i=2;i<6;i++)printf("*(a+%d): %d\n",i,*(a+i));
	a+=4;
	printf("d[4]: %d %d\n",*a,d[4]);
	a--;
	printf("d[3]: %d %d\n",*a,d[3]);
	/* 指针数组 */
	for(i=0;i<4;i++)y[i]=&d[i];/* */
	for(i=0;i<4;i++)printf("i(%d): %d %d\n",i,d[i],*y[i]);
	/* 指针指向指针 */
	a=&i;b=&u;
	c=&a;
	printf("%d %d %d\n",*a,*b,**c);
	*c=b;
	printf("%d %d %d\n",*a,*b,**c);	
	/* 指针传递返回 */
	// 即函数接受的为变量类型，(指针、指针的指针等等)
	char *(*p)(char *); /* 函数指针 */
	p=&func_13z;
	printf("%s %s %s\n",w,func_13z(w),p(w+3));
	int (*add1)(int);add1=func_13add1;
	void (*swp)(int *,int *);swp=func_13swp;
	/* 回调函数 */
	func_13r(p,add1,swp);
}
char *func_14a(char *a,char **b){
	int i=strlen(a)+1;
	*b=(char *)malloc(i*sizeof(char));
	strcpy(*b,a);
	/* 使用第二种方式可以 */
	return a;
}
/*
size_t func_14strlen(char *s){
	// 简单实现
	size_t i=0;
	for(i=0;s[i]!='\0';i++);
	return i;
}

char *func_14strcpy(char *s1,char *s2){
	while((*(s1++)=*(s2++))!=NULL);
	return s1;
}
char *func_14strcat(char *s1,char *s2){
	return func_14strcpy(s1+func_14strlen(s1),s2);
}
int func_14strcmp(char *s1,char *s2){
	for(size_t i=0;s1[i]==s2[i];i++){
		if(s1[i]=='\0')return 0;
	}
	return -1;
}
char *func_strchr(char *s,char ch){
	for(char *p=s;*p!='\0';p++){
		if(*p==ch)return p;
	}
	return NULL;
}
char *func_14strstr(char *s1,char *s2){
	char *p;
	for(char *p=s1;*p!='\0';p++){
		if(func_14strcmp(s1,s2)==0)return *p;
	}
	return NULL;
}
(未测试)*/
void func_14(){
	/* 字符串 */
	/* 字符串本质是char 类型 数组 */
	char s[]={'h','e','l','l','o',' ','w','o','r','l','d','!','\0'};
	char s1[64];
	char s2[64]="world!";
	char *m;
	int i;
	/* */
	s1[0]='a'; /* 单个字符的值用 ' */
	s1[1]='b';
	s1[2]='\0';
	printf("s1: %s\nstrlen(s1):%zd\n",s1,strlen(s1));/* 格式化输出 字符串长度 */
	
	m=strcpy(s1,"hello "); /* 字符串复制 */ /* 返回s1 */
	printf("s1: %s %s\n",s1,m);
	m=strcat(s1,s2); /* 字符串连接 */
	/* strcpy(s1+strlen(s1),s2)*/ /* 字符串连接的另一种写法 */
	printf("s1: %s %s\n",s1,m);
	if(strcmp(s1,s)==0)printf("yes\n"); /*字符串的值相同 */
	s1[5]='\0';
	m=NULL;
	func_14a(s1,&m);/* 指针传递参数 */ /* 可改变m的值; 动态分配内存 */
	printf("%s %s\n",s1,m);
	free(m); /* 也可以retun 在 free() */
	m=strcpy(s1,"https://100define.com/link");
	printf("%s\n",m);
	m=strstr(s1,"//"); /* 寻找字符串并返回指针 */
	printf("%s\n",m);
	m+=2;
	m=strchr(m,'/'); /* 寻找单个字符 */ /* 单个字符用 ' (仅英文字符)(格式化显示%c) */
	printf("%s\n",m);
	strncpy(s1,"hello, world!",5); /* 更安全的函数，防止内存溢出 */
	printf("%%s: %s\n",s1);/* 不过有是就要手动 '\0' 了 */
	s1[5]='\0';
	printf("%%s: %s\n",s1);
}
struct func_15st1{
	int i; /* 在这地方写注释是个好习惯 */
	double r;
	char c;
	long double x;
}func_15s1={5,0.5,'m'},func_15s2;
/*};*/  /* 也可以直接结束 */
struct func_15st1 *func_15a(struct func_15st1 *h){
	/* 参数传递 */
	printf("i: %d\n",h->i);
	return h;
}
struct func_15st2{
	int a;
	struct func_15st1 b;
	struct func_15st1 *h;
};
struct{ /* 匿名 */
	int a;
	int b;
}func_15s3;
struct func_15bs{
	unsigned int a:1; /* 仅仅占用1位 */
	unsigned int b:1; /* 超出范围可能影响下面的变量 */
	unsigned int  :1; /* 无名位域不能使用 */
	int c:1;
	int d:4;
};
struct func_15bs1{
	unsigned int a:6;
	unsigned int b:6;
	unsigned int c:4;
};
void func_15(){
	/* 结构体 */
	/* 结构体就是把多个变量定义成一个整体 */
	/* 这样方便参数传递，也可以使程序相对高效 */
	extern struct func_15st1 func_15s1,func15s2; /* 外部结构体声明 */
	struct func_15st1 s,k[2]; /* 普通结构体的声明和结构体数组声明 */
	struct func_15st1 *h; /* 结构体指针 */
	/* 结构体访问 */
	printf("i: %d\n",func_15s1.i); /* 当做正常变量来用，不过非指针类型变量名后用 . 表示下一级，指针型用 -> */
	/* 结构体指针 */
	h=&func_15s1;
	/* 访问 */
	printf("%d\n",h->i);
	/* 传参 */
	func_15a(h);
	h=func_15a(&func_15s1);
	/* 结构体复制 */
	memcpy(&func_15s2,&func_15s1,sizeof(struct func_15st1));
	printf("c: %c %c\n",func_15s1.c,func_15s2.c);
	/* 结构体数组 */
	for(int i=0;i<2;i++)memcpy(&k[i],&func_15s2,sizeof(struct func_15st1));
	for(int i=0;i<2;i++)printf("i%d: %d\n",i,k[i].i);
	/* 嵌套 */
	struct func_15st2 st,*pst;
	pst=&st;
	printf("a: %d %d\n",st.a,pst->a);
	st.h=&func_15s1;
	printf("i: %d %d\n",st.h->i,pst->h->i);
	pst->h=&st.b;// &pst->b
	printf("i: %d %d %d %d\n",st.b.i,pst->b.i,st.h->i,pst->h->i);
	/* 位域 */
	/* 位域可用来节省内存(多用于只有几个值) */
	struct func_15bs bit;
	bit.a=1;
	printf("%u\n",bit.a);
	/* bit.a=2; / * 超范围，报错 * /
	printf("%u\b",bit.a);*/
	printf("%lu %lu\n",(size_t)6+6+4,8*sizeof(struct func_15bs1)); /* 注意大小 (行成了空位域)*/
}
union func_16un{
	int a;
	short m;
	char b;
};
struct func_16st{
	int a;
	short m;
	char b;
};

void func_16(){
	/* 共用体 */
	/* 共用体可以当时结构体来用，但每个变量都公用一份内存，内存是变量最大值，当一个变量赋值时，其他变量可能会变化 */
	
	printf("size: %lu %lu\n",sizeof(struct func_16st),sizeof(union func_16un));
	union func_16un h;
	h.a=5;
	printf("a: %d %hhu\n",h.a,h.b);
	h.b='p';
	printf("a: %d %hhu\n",h.a,h.b);
	h.a=300;
	printf("a: %d %hhu\n",h.a,h.b);
}
void func_17(){
	/* typedef */
	/* 为数据类型定义别名 */
	typedef int A; //习惯大写
	A a; //等效于 int a;
	A b;
	printf("%d %d\n",a,b);
	typedef unsigned long long UNL;
	UNL c;
	printf("%llu\n",c);
	typedef struct Books{
		unsigned int size;
		char name[100];
		char author[50];
	}Book;
	Book book; //相当于 Books book
}
int func_18(){
	/* 输入输出 */
	char buf[257];
	int c=0;
	printf("继续?(\\n跳过)");
	//return 0;
	if(getchar()=='\n')return 0;/* 结束函数 */
	/* 标准文件 
	 * stdin 标准输入 键盘
	 * stdout 标准输出 屏幕
	 * stderr 标准错误 屏幕
	 */
	printf("start\n");
	fprintf(stdout,"ok\n");
	/* 继续 */
	/* getchar putchar */
	c=getchar();
	putchar(c);
	printf("你输入了%c\n",c);
	//int getchar(void) 从stdin 获取一个字符
	//int putchar(int c) 向stdout 输出一个字符
	/* gets puts */
	printf("Enter...\n");
	fgets(buf,256,stdin); //貌似C99没有，代替一下
	puts(buf);
	//char *gets(char *s) 从stdin 获取一些字符 (容易造成内存溢出)
	//int puts(char *s) 向stdout 输出一些字符
	/* printf scanf */
	strcpy(buf,"字符串 数字");
	printf("%s ",buf);
	scanf("%*s %d",&c); /* %*% 假读 */
	printf("read:%d\n",c);
	//scanf 还支持一定的表达式
	strcpy(buf,"https://100define.com/linker");
	char d[64];
	sscanf(buf,"http%*[s]://%*[0-9]%*[a-z].%*[^/]/%4s",d);
	printf("%s\n",d);
	return 0;
}
int func_19(){
	/* 文件读写 标准读写(不包括open,write等)*/
	char buf[256];
	int i=5;
	FILE *foo=NULL; /* 文件指针 */
	foo=fopen("note_test.txt","w+");/* 打开文件(当前路径) (w+ 打开文件，不存在创建文件，存在覆盖文件，如果有权限允许读写 )*/
	/* 更多
	 * r 打开文本文件，允许读
	 * w 打开文件，不存在创建文件，存在则在文件开头写，会覆盖文件，允许写
	 * a 追加写，即不存在会创建，存在回在文件末尾写，允许写
	 * r+ 在r的基础上，允许写
	 * w+ 在w的基础上，允许读
	 * a+ 在a的基础上，允许读 (读会从开头开始，写从文件末尾)
	 * b 读写二进制文件 如(ab rb+ wb+)
	 */
	fprintf(foo,"hello, world!");/* 向文件写入字符串(像printf()) */
	fputc('\n',foo); /* 写一个字符 */
	fputs("well\n",foo); /* 写字符串 */
	fprintf(foo,"i: %d\n",i);
	i=0;
	/* fseek
	 * int fseek(FILE *stream, long int offset, int whence);
	 * stream FILE * 对象
	 * offset 是相对 whence的偏移量
	 * whence 文件开始偏移的位置，它通常是以下值
	 *  SEEK_SET 文件开头
	 *  SEEK_CUR 文件指针当前位置
	 *  SEEK_END 文件末尾
	 * 成功会返回 0
	 * (一般读取文件的操作会使指针后移)
	 */
	if(fseek(foo,0,SEEK_SET)!=0){fclose(foo);return -1;}
	fgets(buf,255,foo);
	printf("read: %s\n",buf);/* 有\n */
	if(fseek(foo,-1*strlen(buf),SEEK_CUR)!=0){fclose(foo);return -1;}
	fgets(buf,255,foo);
	printf("read: %s\n",buf);
	fscanf(foo,"%*[^\n]");/* 读一行，无\n */
	if(fgetc(foo)=='\n')printf("yes\n");
	fscanf(foo,"i: %d\n",&i);
	printf("i: %d\n",i);
	/* fflush fflush(FILE *stream); 把缓冲区的内容写到文件中(缓冲区用完后可自动fflush，但最后可能会有剩余内容) */
	fclose(foo);/* 关闭文件，(最后会fflush) */
	/* 二进制读写
	 * size_t fwrite(const void* buffer,size_t size,size_t count,FILE* stream);
	 * buffer 要写入的数据 (可以写入普通文本，结构体等着)
	 * size 要写入内容的单字节数
	 * count 要写入size字节的数据个数
	 * stream 目标文件
	 * 返回值 count
	 * fread 类似
	 */
	 strcpy(buf,"and\n");
	 fwrite(buf,1,strlen(buf),stdout);
	 //参数不当可能导致 '\0' 被写入
	 /* 如
	 * struct xxx a[5];
	 * fwrite(&a,sizeof(struct xxx),5,foo);
	 */
	return 0;
}
void func_20(){
	/* 预处理器 */
	/* 预处理器内容和注释通常不会留在程序里 */
#define my_dl 0x1 /* 定义宏 */ /* 即在程序中吧所有的my_dl 替换成0x1*/
	//#include 包含一个头文件 (写在开头) 
#ifdef my_dl/* 如果定义，返回真 */
#undef my_dl /* 取消已经定义的宏 */
#endif /* 结束条件 */
#ifndef my_dl /* 如果没有定义，返回真 */
#define my_dl 0x7
#endif
#if 0 /* 条件为真，向下 (0为假) */
这里就相当于注释了，甚至可以写shell(仅开头)
#elif 0 /* 否则如果 */

#else
#endif
// #error 遇到标准错误时输出

//#pragma 特殊命令到编译器中
	printf("Date: %s\nTime: %s\nFile: %s\nLine: %d\nSTDC: %d\n",__DATE__,__TIME__,__FILE__,__LINE__,__STDC__);
	/* 当前日期、时间 当前文件名 行号 (以ANSI为标准时，定义为1)*/
#define func_dl(a, b) /* 延续到下一行 */ \
	printf(#a " and " #b) /* # 字符串常量化 */
#define tokenpaster(n) \
	printf ("token" #n " = %d", token##n) /* 粘贴运算符 ## */
	int token34=40;
	tokenpaster(34);
}
int main(int argc,char **argv){
	printf("hello, world!\n");
	func_0(); /* 第一个C程序 */
	func_1(); /**/
	func_2(); /**/
	func_3(); /* 数据类型 */
	func_4(); /* 变量 */
	func_5(); /* 储存类 */
	func_6(); /* 运算符号 */
	func_7(); /* 判断 */
	func_8(); /* 循环 */
	func_9(); /* 函数 */
	func_10(); /* 作用域 */
	func_11(); /* 数组 */
	func_12(); /* 枚举 */
	func_13(); /* 指针 */
	func_14(); /* 字符串 */
	func_15(); /* 结构体 */
	func_16(); /* 共用体 */
	func_17(); /* typedef */
	func_18(); /* 输入输出 */
	func_19(); /* 文件读写 */
	func_20(); /* 预处理器 */
	/*
	printf("sting: %s\n%%c: %c%c%c%c\n",a[0],a[1],a[2],a[3]);
	float float_data=3.14;
	double double_data=6.28;
	printf("float: %f,double: %lf *: \n",float_data,double_data,float_data*double_data);
	i=9;n=4;
	printf("i: %d\nn: %d\ni+n: %d\ni-n: %d\ni*n: %d\ni/n: %d\ni%n: %d\n",i,n,i+n,i-n,i*n,i\n,i%n);
	strcpy(buf,"hello, world!\n");
	strcpy(strab,"hi, world\n");
	printf("buf: %s\nstrab: %s\n",buf,strab);
	strcat(buf,strab);
	printf("buf: %s\nstrab: %s\n",buf,strab);
	m=strstr("hello");
	if(m!=NULL){printf("y\n");
		printf("%s\n",buf);
	}*/
	return 0;
}
