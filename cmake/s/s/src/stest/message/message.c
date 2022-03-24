#include <stdio.h>
#include <string.h>
#include "message.h"
int message(char *s) {
	fwrite(s, sizeof(char), strlen(s), stdout);
	//fwrite("\n", sizeof(char), 1, stdout);
	putc('\n',stdout);
	return 0;
}
