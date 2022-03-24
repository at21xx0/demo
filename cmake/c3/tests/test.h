#ifndef _TEST_H__
#define _TEST_H__

#define T1(ex)\
	if(!(ex))\
	fprintf(stderr,"%s errorline: %d\n",#ex,__LINE__),exit(1);
#define T2(ex)\
	if(ex)\
		printf("%s passed\n",#ex);\
	else\
		printf("%s failed %d\n",#ex,__LINE__),exit(1);
//#define T3(ex)\

#endif
