#ifndef _COUT_ALL_H__
#define _COUT_ALL_H__

#define COUT(v) \
	std::cout << (v) << std::endl;
#ifdef __cplusplus
#define C1(v) \
	static_assert(v, #v);
#endif
#define C2(v) \
	std::cout << #v << " : " << (v) << std::endl;
#define C3(v, vv) \
	(void)(v); \
	std::cout << #v << " : " << (vv) << std::endl;

#define static_assert_1(a) do{switch(0){case 0: break;case (a): break;};}while(0)


#endif

