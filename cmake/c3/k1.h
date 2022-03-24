#ifndef _D_H__
#define _D_H__

#include "k1Export.h" // 区分静态库和动态库是否导出所有符号

k1_EXPORT int k1(int i);
k1_NO_EXPORT int k1e(int i);

#endif
