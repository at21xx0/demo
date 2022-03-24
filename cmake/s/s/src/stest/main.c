#include<stdio.h>
#include<pthread.h>

#include "message.h"
#include "s1.h"
#include "s2.h"

int main(void)
{
	printf("hello, world!\n");
	message("hello, message!");
	printf("s1(5): %d\n", s1(5));
	printf("s2(5): %d\n", s2(5));
	//printf("s2e(5): %d\n",s2e(5)); // 报 隐藏所有符号 有时也不报错 尝试执行dlt
	//printf("s2k(5): %d\n", s2k(5)); //报错
	printf("S2_VERSION: %s\n", S2_VERSION);
	printf("s2ex(5): %d\n", s2ex(5));
	return 0;
}
