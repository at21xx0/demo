#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include <assert.h>
#include "mark_sort.h"
//#include <math.h>


typedef struct stable_test_t
{
	int i;
	int j;
}ST;

int test_sort(const void *a, const size_t len, const size_t size, int (*cmpf)(const void *a, const void *b))
{
	const void *b, *e;
	e = a + len * size;
	while(1)
	{
		b = a + size;
		if(b == e)
			return 0;
		if(cmpf(b, a) < 0)
			return 1;
		a = b + size;
		if(a == e)
			return 0;
		if(cmpf(a, b) < 0)
			return 1;
	}
	return 0;
}


int c(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}
int cd(const void *a, const void *b)
{
	if(*(double *)a == *(double *)b)
		return 0;
	else if(*(double *)a < *(double *)b)
		return (-1);
	else
		return 1;
}

int cR(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}

int cdR(const void *a, const void *b)
{
	if(*(double *)b == *(double *)a)
		return 0;
	else if(*(double *)b < *(double *)a)
		return (-1);
	else
		return 1;
}

void sort_int()
{
	int i;
	int arr[20] = {127, 64, 32, 55, 13, 648, 32767, 884, 10479, 47, 99, 46, -10, -1, 9999, 65536, 7, 8, 9, 97};
	//int arr[20] = {127, 64, 32, 55, 13, 648, 32767, 884, 10479, 47, 99, 46, 10, 1, 9999, 65536, 7, 8, 9, 97};
	//qsort((void *)arr, 20, sizeof(int), &c);
	//mark256_sort((void *)arr, 20, sizeof(int), 0, sizeof(int), MARK_SORT_SIGNED);
	radix_sort((void *)arr, 20, sizeof(int), 0, sizeof(int), 0 | RADIX_SORT_SIGNED);
	putc('\n', stdout);
	for(i = 0;i < 20;++i)
	{
		printf("%d\n", arr[i]);
	}
	assert(test_sort(arr, 20, sizeof(int), &c) == 0);
}
void sort_double()
{
	int i;
	double arrd[20] = {47.0, 50.8, 23.9, 1555559.0, 32768.9, 45555.669999, 323253368467676787667.785866464849946, 2556679767679797.0, -3.0, -4.0, -99.0, 6555.0, 6e-8, 1e-23, 2e-23, 3e-23, 17.0, 18.0, 1.0, 0.5};
	//mark256_sort((void *)arrd, 20, sizeof(double), 0, sizeof(double), MARK_SORT_FLOAT);
	//qsort((void *)arrd, 20, sizeof(double), &cd);
	/*
	for(i = 0;i != 20;++i)
	{
		if(arrd[i] < 0.0)
			arrd[i] *= (double)(-1);
	}
	*/
	radix_sort((void *)arrd, 20, sizeof(double), 0, sizeof(double), RADIX_SORT_R | RADIX_SORT_FLOAT);
	for(i = 0;i != 20;++i)
	{
		printf("%-16le %.9lf\n", arrd[i], arrd[i]);
	}
	assert(test_sort(arrd, 20, sizeof(double), &cdR) == 0);
}
int sort_str()
{
	int i;
	char *p[20];
	int plen;
	char *m;
	char *str = "file.c\0" \
							 "file.h\0" \
							 "a.c\0" \
							 "a.h\0" \
							 "CMakeLists.txt\0" \
							 ".gitignore\0" \
							 "src\0" \
							 "init\0" \
							 "yhooo.md\0" \
							 "README.md\0" \
							 "LICENSE\0" \
							 "file_14.c\0" \
							 "file_16.c\0" \
							 "file_8.c\0";
	for(plen = 0, m = str;*m != '\0';)
	{
		p[plen] = m;
		m += strlen(m);
		++m;
		++plen;
	}
	printf("len: %d\n", plen);
	for(i = 0;i != plen; ++i)
	{
		printf("%s\n", p[i]);
	}

	/*
	mark256_sort_str((void *)p, plen, sizeof(void *), 0, 0);
	for(i = 0;i != plen;++i)
	{
		printf("%s\n", p[i]);
	}
	*/

	return 0;
}
int ci(const void *a, const void *b)
{
	return ((ST *)a)->i - ((ST *)b)->i;
}
int cj(const void *a, const void *b)
{
	return ((ST *)a)->j - ((ST *)b)->j;
}
void stable_test()
{
#define TEST_SIZE 1024
	int i;
	ST *p, *m;
	int map[64] = {0};
	srand((unsigned int)time(NULL));
	p = (ST *)malloc(TEST_SIZE * sizeof(ST));
	for(i = 0, m = p;i != TEST_SIZE;++i)
	{
		m->j = rand();
		m->i = m->j % 64;
		++map[m->i];
		++m;
	}
	mark256_sort_struct((void *)p, TEST_SIZE, sizeof(ST), ST, j, 0);
	mark256_sort_struct((void *)p, TEST_SIZE, sizeof(ST), ST, i, 0);
#if 0
	qsort((void *)p, TEST_SIZE, sizeof(ST), &cj);
	qsort((void *)p, TEST_SIZE, sizeof(ST), &ci);
#endif
	assert(test_sort((void *)p, TEST_SIZE, sizeof(ST), &ci) == 0);
	for(i = 0, m = p;i != 64;++i)
	{
		if(test_sort((void *)m, map[i], sizeof(ST), &cj) != 0)
			break;
		m += map[i];
	}
	assert(i == 64);
	free((void *)p);
#undef TEST_SIZE
}
void benchmark()
{
	int i;
	clock_t t1, t2, t3, t4;
	double t[3], mt;
#define TEST_SIZE 1024 * 8 * 256
#define CL(s,e) ((double)(e - s) / CLOCKS_PER_SEC)
	int *p = (int *)malloc(sizeof(int) * TEST_SIZE * 2);
	int *q;
	srand((unsigned)time(NULL));
	for(i = 0, q = p;i != TEST_SIZE;++i)
	{
		*q = rand();
		++q;
	}
	memcpy(q, p, sizeof(int) * TEST_SIZE);
	t1 = clock();
	qsort((void *)p, TEST_SIZE, sizeof(int), &c);
	//mark256_sort((void *)q, TEST_SIZE, sizeof(int), 0, sizeof(int), 0);
	t2 = clock();
	//mark256_sort((void *)q, TEST_SIZE, sizeof(int), 0, sizeof(int), MARK_SORT_CP);
	radix_sort((void *)q, TEST_SIZE, sizeof(int), 0, sizeof(int), 0);
	//radix_sort2((void *)q, TEST_SIZE, sizeof(int), 0, sizeof(int), 0);
	t3 = clock();
	//printf("%p\n", q);
	assert(test_sort((void *)q, TEST_SIZE, sizeof(int), &c) == 0);
	t4 = clock();
	t[0] = CL(t1, t2);
	t[1] = CL(t2, t3);
	t[2] = CL(t3, t4);
	mt = t[0];
	if(t[1] < mt)
		mt = t[1];
	printf("time\n");
	printf("%lf %lf\n", t[0], t[1]);
	t[0] /= mt;
	t[1] /= mt;
	printf("%lf %lf\n", t[0], t[1]);

	free(p);
#undef TEST_SIZE
}


int main(void)
{
	sort_int();
	sort_double();
	stable_test();
	benchmark();

	return 0;
}



