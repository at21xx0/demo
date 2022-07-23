#include <stdio.h>
#include <dlfcn.h>

#include "m.h"


int main2(void)
{
	void *handle;
#define test(symbol) \
	s = dlsym(handle, #symbol); \
	if(s) \
	{ \
		printf("%s(5): %d\n",#symbol, s(5)); \
	} \
	else \
	{ \
		printf("%s\n", dlerror()); \
	} 
	int (*s)(int);
	handle	= dlopen("../lib/libs2.so.1", RTLD_NOW);
	if(!handle)
	{
		printf("error: %s\n", dlerror());
		return 1;
	}
	test(s2);
	test(s2s);
	test(s2k);
	dlclose(handle);
	return 0;
#undef test
}
