#include <stdio.h>
#include <stdlib.h>
#include "s1.h"


int main(int argc, char **argv)
{
	int i, j;
	if(argc != 3)
		return 1;
	sscanf(argv[1], "%d", &i);
	sscanf(argv[2], "%d", &j);
	if(s1(i) != j)
		return 1;
	return 0;
}