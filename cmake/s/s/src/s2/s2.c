#include <stdio.h>
#include "s2.h"

#if !defined(s2_VERSION) && defined(s2_win32_VERSION)
#define s2_VERSION s2_win32_VERSION
#endif
char *S2_VERSION = s2_VERSION; //默认定义

int s2(int i) {
	return s2e(i);
}
