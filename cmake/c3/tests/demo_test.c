#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k1.h"
#include "test.h"

#define TEST T2
int main(int argc,char **argv)
{
	printf("demo_test\n");
	TEST(1+1==2);
	TEST(k1(5)==5);
	//TEST(k1(5)==6);


	return 0;
}
