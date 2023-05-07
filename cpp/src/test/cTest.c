
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cTest.h"

int c_int = 0;

int cTest1()
{
	return cppTest1();
}

int c_sum_1(int n, ...)
{
	int i;
	int ret;
	va_list args;
	va_start(args, n);
	for(i = 0, ret = 0;i != n;++i)
	{
		ret += va_arg(args, int); // ret += *(int *)args; args += sizeof(int);
	}
	va_end(args);
	return ret;
}



