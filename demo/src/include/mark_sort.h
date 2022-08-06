#ifndef _MARK_SORT_H__
#define _MARK_SORT_H__

#include <stdint.h>



// 类似于基数排序



#define MARK_SORT_SIGNED (1 << 0) // 排序小于0的整数
#define MARK_SORT_R (1 << 1) // 与当前顺序相反的顺序
#define MARK_SORT_NUM (1 << 2) // 字符串中数字排序
#define MARK_SORT_FLOAT (1 << 3)
#define MARK_SORT_CP (1 << 4)

void mark256_sort(void *p, size_t len, size_t size, size_t t_off, size_t t_size, int info);

static inline void mark256_sort_int(void *p, size_t len, size_t size, int info)
{
	mark256_sort(p, len, size, 0, size, info);
}
#define mark256_sort_struct(p, len, size, struct_name, member, info) \
	mark256_sort(p, len, size, (size_t)&((struct_name *)0)->member, sizeof(((struct_name *)0)->member), info);

void mark256_sort_str(void *p, int len, int size, int t_off, int info);

extern int mark_sort_max;


#define RADIX_SORT_SIGNED MARK_SORT_SIGNED
#define RADIX_SORT_R MARK_SORT_R
#define RADIX_SORT_NUM MARK_SORT_NUM

#define RADIX_SORT_H (1 << 8)
#define RADIX_SORT_FLOAT MARK_SORT_FLOAT
#define RADIX_SORT_S (1 << 9)
#define RADIX_SORT_S2 (1 << 10)




void radix_sort(void *p, size_t len, size_t size, size_t t_off, size_t t_size, int info);

void radix_sort2(void *p, size_t len, size_t size, size_t t_off, size_t t_size, int info);






#endif
