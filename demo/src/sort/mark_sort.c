#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mark_sort.h"





typedef int32_t L32;
typedef int64_t L64;
//#define L32_MAX ((uint32_t)(-1) >> 1)
//#define T_MAX(T) (((T)(-1) < 0)?(unsigned T)(-1) >> 1:(T)(-1))

#define SIGNED(p, size, e) (*(uint8_t *)(p + size * e + size - 1) & (1 << 7))
#define SIGNED_UINT8 (1 << 7)
#define SIGNED_HIGH_OFF(size) (size - 1)
//#define SIGNED_HIGH_OFF(size) 0




#define T_SIZE 8

#define T_SWAP(T) \
{ \
	tmp = *(T *)a; \
	*(T *)a = *(T *)b; \
	*(T *)b = (T)tmp; \
	a += sizeof(T); \
	b += sizeof(T); \
}
#define T_CP(T) \
{ \
	*(T *)a = *(T *)b; \
	a += sizeof(T); \
	b += sizeof(T); \
}
#if T_SIZE == 8
typedef uint64_t T_T;
#define T_SIZE2 3
#elif T_SIZE == 4
typedef uint32_t T_T;
#define T_SIZE2 2
#elif T_SIZE == 1
typedef uint8_t T_T;
#define T_SIZE2 1
#endif

static inline void memswap(void *a, void *b, size_t size)
{
	register T_T tmp;
	unsigned int s;
	for(s = size & (T_SIZE - 1), size >>= T_SIZE2;size;--size)
	{
		T_SWAP(T_T);
	}
	switch(s)
	{
#if T_SIZE == 8
		case 7:
			T_SWAP(uint8_t);
			/* fall through */
		case 6:
			T_SWAP(uint16_t);
			T_SWAP(uint32_t);
			break;
		case 5:
			T_SWAP(uint8_t);
			/* fall through */
		case 4:
			T_SWAP(uint32_t);
			break;
#endif
#if T_SIZE == 4 || T_SIZE == 8
		case 3:
			T_SWAP(uint8_t);
			break;
		case 2:
			T_SWAP(uint16_t);
			break;
		case 1:
			T_SWAP(uint8_t);
			break;
		case 0:
			break;
		default:
			break;
#endif
	}
}
static inline void memcpy2(void *a, void *b, size_t size)
{
	unsigned int s;
	for(s = size & (T_SIZE - 1), size >>= T_SIZE2;size;--size)
	{
		T_CP(T_T);
	}
	switch(s)
	{
#if T_SIZE == 8
		case 7:
			T_CP(uint8_t);
			/* fall through */
		case 6:
			T_CP(uint16_t);
			T_CP(uint32_t);
			break;
		case 5:
			T_CP(uint8_t);
			/* fall through */
		case 4:
			T_CP(uint32_t);
			break;
#endif
#if T_SIZE == 4 || T_SIZE == 8
		case 3:
			T_CP(uint8_t);
			break;
		case 2:
			T_CP(uint16_t);
			break;
		case 1:
			T_CP(uint8_t);
			break;
		case 0:
			break;
		default:
			break;
#endif
	}
}
#undef T_SWAP
#undef T_CP







/*
void temp_t1()
{
	char a[64] = "1234567890\n";
	char b[64] = "abcdefghijklmn!\n";
	memswap8((void *)a, (void *)b, 4);
	printf("%s\n%s\n", a, b);
	abort();
}
*/


void mark256_sort_L32(void *p, L32 len, L32 size, L32 t_off, L32 t_size, int info)
{
	//int next[n];
	L32 i; // index
	L32 n; // off
	L32 *next; // off_next
	L32 s; // start
	L32 e; // end
	L32 *ms;//L32 ms[256];  // mark_end
	L32 *me; //L32 me[256]; // mark_start
	L32 cs; // chain_start
	L32 ce; // chain_end
	void *m;

	/*
	if(size < 256)
	{
		// 其他排序算法
	}
	*/
	next = (L32 *)malloc((len + 256 + 256 + 1) * sizeof(L32)); // off_next
	if(!next)
		return;
	for(i = 0;i != len;)
	{
		*next = ++i;
		++next;
	}
	ms = next;
	me = ms + 256;
	for(n = i + 256;i != n;++i, ++next, ++me)
	{
		*next = len;
		*me = i;
	}
	next -= n;
	me -= 256;
	cs = len;
	if(info & MARK_SORT_FLOAT)
	{
		p += SIGNED_HIGH_OFF(size);
		for(i = 0;i != len;++i)
		{
			n = *(uint8_t *)(p + size * i) & SIGNED_UINT8;
			next[me[n]] = i;
			me[n] = i;
		}
		p -= SIGNED_HIGH_OFF(size);
		if(ms[0] != len && ms[SIGNED_UINT8] != len)
		{
			next[me[0]] = len;
			next[me[SIGNED_UINT8]] = len;
			if(info & MARK_SORT_R)
			{
				s = ms[0];
				cs = ms[SIGNED_UINT8];
			}
			else
			{
				info ^= MARK_SORT_R;
				s = ms[SIGNED_UINT8];
				cs = ms[0];
			}
			ms[0] = me[0] = ms[SIGNED_UINT8] = len;
			me[SIGNED_UINT8] = len + SIGNED_UINT8;
		}
		else
		{
			if(ms[0] == len)
				n = 0;
			else
			{
				info ^= MARK_SORT_R;
				n = SIGNED_UINT8;
			}
			s = ms[n];
			//e = len;
			next[me[n]] = len;
			ms[n] = len;
			me[n] = len + n;
		}
	}
	else
	{
		s = 0; // 从零开始
		//e = len; // 好像并没有什么用
	}
mark256_sort_re0:
	p += t_off;
	for(i = 0;i != t_size;)
	{
		for(;s != len;s = next[s])
		{
			n = *(uint8_t *)(p + s * size); //
			next[me[n]] = s;
			me[n] = s;
		}
		e = len + 256 * 2;
		++p;
		if(++i == t_size && (info & MARK_SORT_SIGNED))
			break;
		if(info & MARK_SORT_R)
		{
			for(n = 256 - 1;n != (-1);--n)
			{
				if(ms[n] != len)
				{
					next[e] = ms[n];
					e = me[n];
					ms[n] = len;
					me[n] = len  + n;
				}
			}
		}
		else
		{
			for(n = 0;n != 256;++n)
			{
				if(ms[n] != len)
				{
					next[e] = ms[n];
					e = me[n];
					ms[n] = len;
					me[n] = len  + n;
				}
			}
		}
		next[e] = len;
		s = next[len + 256 * 2];
	}
	p -= t_off + t_size;

	if(cs != len)
	{
		ce = 0;
		if(info & MARK_SORT_FLOAT)
		{
			info ^= MARK_SORT_R | MARK_SORT_FLOAT;
			ce = cs;
			cs = s;
			s = ce;
			ce = e;
			goto mark256_sort_re0;
		}
		next[ce] = s;
		s = cs;
	}
	else if(info & MARK_SORT_SIGNED)
	{
		e = len + 256 * 2;
		if(info & MARK_SORT_R)
		{
			n = SIGNED_UINT8;
			i = (-1);
mark256_sort_re1:
			for(;n != i;--n)
			{
				if(ms[n] != len)
				{
					next[e] = ms[n];
					e = me[n];
				}
			}
			if(i == (-1))
			{
				i = SIGNED_UINT8;
				n = 256 - 1;
				goto mark256_sort_re1;
			}
		}
		else
		{
			n = SIGNED_UINT8;
			i = 256;
mark256_sort_re2:
			for(;n != i;++n)
			{
				if(ms[n] != len)
				{
					next[e] = ms[n];
					e = me[n];
				}
			}
			if(i == 256)
			{
				i = SIGNED_UINT8;
				n = 0;
				goto mark256_sort_re2;
			}
		}
		next[e] = len;
		s = next[len + 256 * 2];
	}
	if(info & MARK_SORT_CP)
	{
		m = malloc(len *	size);
		memcpy2(m, p, size * len);
		for(;s != len;s = next[s])
		{
			memcpy2(p, m + s * size, size);
			p += size;
		}
		free(m);
		free((void *)next);
		return;
	}

	//#define off next
#define tmp ((void *)ms)
	i = 0;
	while(1)
	{
		if(s < i)
		{
#if 0
			s = next[s];
#else
			//n = s;
 			s = next[s];
			next[n] = s;
#endif
			continue;
		}
		else if(s == len)
			break;

		memswap(p + size * s, p + size * i, size);
		n = next[s];
		next[s] = next[i];
		next[i] = s;
		s = n;
		++i;
	}
#undef tmp
	free((void *)next);
}


void radix_sort(void *p, size_t len, size_t size, size_t t_off, size_t t_size, int info)
{
#if 0
#define T_STEP (-1)
#else
#define T_STEP 1
#endif
	void *q; // tmp
	void *m; // loop_ptr_m
	void *e; // loop_ptr_e
	uintptr_t *ct; // count
	uintptr_t *kt;
	size_t sl;
	size_t p_off;
	sl = size * len;
	q = malloc(sl + 256 * sizeof(uintptr_t));
	if(!q)
		return;
	ct = (void *)(q + sl);
#if T_STEP == 1
	t_size += t_off;
#elif T_STEP == (-1)
#error "not ready"
	len = t_off;
	t_off += t_size;
	t_size = len;
#else
#error
#endif
#define t_e t_size
#define t_off2 len
#define p_off2 len
	p_off = p_off2 = 0;
	if(info & RADIX_SORT_FLOAT)
	{
		t_off2 = t_off;
#if T_STEP == 1
		t_off = t_e - T_STEP;
#endif
		info |= RADIX_SORT_SIGNED;
		p_off = sl;
	}

	while(1)
	{
		for(kt = ct, e = kt + 256;kt != e;++kt)
			*kt = 0;
		for(m = p + t_off, e = m + sl;m != e;m += size)
		{
			ct[*(uint8_t *)m] += size;
		}
		if(ct[0] != (uintptr_t)sl)
		{
			m = (void *)ct;
			do
			{
				switch(info & ((t_off + T_STEP == t_e)?RADIX_SORT_R | RADIX_SORT_SIGNED | RADIX_SORT_S :RADIX_SORT_R | RADIX_SORT_S))
				{
					case 0:
						e = (void *)(ct + 254);
						*ct += (uintptr_t)q;
						break;
					case RADIX_SORT_SIGNED:
						e = (void *)(ct + 254);
						ct += 128;
						info |= RADIX_SORT_S;
						*ct += (uintptr_t)q;
						break;
					case RADIX_SORT_SIGNED | RADIX_SORT_S:
						e = (void *)(ct + 126);
						*ct += *kt;
						info &= ~(RADIX_SORT_S);
						break;

					case RADIX_SORT_R:
						e = (void *)(ct + 1);
						ct += 255;
						*ct += (uintptr_t)q;
						break;
					case RADIX_SORT_R | RADIX_SORT_SIGNED:
						e = (void *)(ct + 1);
						ct += 127;
						info |= RADIX_SORT_S;
						*ct += (uintptr_t)q;
						break;
					case RADIX_SORT_R | RADIX_SORT_SIGNED | RADIX_SORT_S:
						e = (void *)(ct + 129);
						ct += 255;
						*ct += *kt;
						info &= ~(RADIX_SORT_S);
						break;
					default:
						//abort();
						break;
				}
				if(info & RADIX_SORT_R)
					*(intptr_t *)q = (-1);
				else
					*(intptr_t *)q = 1;
				while(ct != e)
				{
					kt = ct + *(intptr_t *)q;
					*kt += *ct;
					ct = kt + *(intptr_t *)q;
					*ct += *kt;
				}
				kt = ct + *(intptr_t *)q;
				*kt += *ct;
				ct = (uintptr_t *)m;
			}
			while(info & RADIX_SORT_S);

			for(e = p + t_off - size, m = e + sl;m != e;m -= size)
			{
				memcpy2((void *)(ct[*(uint8_t *)m] -= size), m - t_off, size);
			}
			m = p;
			p = q;
			q = m;
		}
		if(info & RADIX_SORT_FLOAT)
		{
			t_off = t_off2;
			info &= ~(RADIX_SORT_SIGNED | RADIX_SORT_FLOAT);
			if(ct[0] != ct[127] && ct[128] != ct[255])
			{
				//t_off2 = t_off;
				if(info & RADIX_SORT_R)
				{
					p_off = ct[0] - ct[127];
					info &= ~(RADIX_SORT_R);
				}
				else
					p_off = ct[255] - ct[128];
				p += p_off;
				q += p_off;
				sl -= p_off;
			}
			else
			{
				if(ct[128] != ct[255])
					info ^= RADIX_SORT_R;
				p_off = 0;
			}

			continue;
		}
		if((t_off += T_STEP) == t_e)
		{
			if(p + sl == (void *)ct || p + sl + p_off2 == (void *)ct)
			{
				memcpy2(q, p, sl);
				m = p;
				p = q;
				q = m;
			}
			if(p_off != 0)
			{
				m = p;
				p = q;
				q = m;
				p -= p_off;
				q -= p_off;
				t_off = t_off2;
				p_off2 = sl;
				sl = p_off;
				p_off = 0;
				info ^= RADIX_SORT_R;
			}
			else
				break;
		}
	}
	free(q);
#undef t_e
}
/*
void radix_sort2(void *p, size_t len, size_t size, size_t t_off, size_t t_size, int info)
{
	extern int mark_sort_max;
	L32 *zone; // zone_count
	L32 *next; // buf
	L32 cz; // current_zone
#if 0
	L32 zone = len / mark_sort_max;
	L32 lz = len % mark_sort_max;
#else
	div_t zz = div(len, mark_sort_max);
	L32 n;
#define tz zz.quot // total_zone
#define lz zz.rem; // last_zone
#endif
	(void)p;
	(void)len;
	(void)size;
	(void)t_off;
	(void)t_size;
	(void)info;
	(void)next;
	(void)cz;
	(void)n;
	next = (L32 *)malloc((len + 256 + 256 + 1) * sizeof(L32)); 
	zone = (L32 *)malloc((tz + 1) * 256);
	free((void *)next);
	free((void *)zone);
}
*/

void mark256_sort_L32z(void *p, L32 len, L32 size, L32 t_off, L32 t_size, int info)
{
	extern int mark_sort_max;
	L32 *zone; // zone_count
	L32 *next; // buf
	L32 cz; // current_zone
#if 0
	L32 zone = len / mark_sort_max;
	L32 lz = len % mark_sort_max;
#else
	div_t zz = div(len, mark_sort_max);
	L32 n;
#define tz zz.quot // total_zone
#define lz zz.rem; // last_zone
#endif
	(void)p;
	(void)len;
	(void)size;
	(void)t_off;
	(void)t_size;
	(void)info;
	(void)next;
	(void)cz;
	(void)n;
	next = (L32 *)malloc((len + 256 + 256 + 1) * sizeof(L32)); 
	zone = (L32 *)malloc((tz + 1) * 256);
	free((void *)next);
	free((void *)zone);
}

void mark256_sort(void *p, size_t len, size_t size, size_t t_off, size_t t_size, int info)
{
	if(p == NULL || size == 0 || t_size == 0 || len == 0)
		return;
	if(size <= (size_t)mark_sort_max)
		mark256_sort_L32(p, len, size, t_off, t_size, info);
	else
		mark256_sort_L32z(p, len, size, t_off, t_size, info);
}
int mark_sort_max = 1024 * 8;




