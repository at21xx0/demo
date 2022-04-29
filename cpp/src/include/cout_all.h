#ifndef _COUT_ALL_H__
#define _COUT_ALL_H__

#define COUT(v) \
	cout << (v) << endl;
#define C2(v) \
	cout << #v << ": " << (v) << endl;
#define C3(v, vv) \
	(void)v; \
	cout << #v << ": " << (vv) << endl;


#endif

