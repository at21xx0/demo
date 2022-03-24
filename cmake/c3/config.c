#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k1.h"

#ifdef IS_INTEL_CXX_COMPILER
#define F1 "INTEL"
#elif IS_GNU_CXX_COMPILER
#define F1 "GNU"
#elif IS_PGI_CXX_COMPILER
#define F1 "PGI"
#elif IS_XL_CXX_COMPILER
#define F1 "XL"
#else
#define F1 "UNKOWN"
#endif
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

const static char *program_version=PROGRAM_VERSION;
int d1();
int main(int argc,char **argv)
{
	printf("hello, world!\n");
	printf("Version: %s.%s\n",PROJECT_VERSION_MAJOR,PROJECT_VERSION_MINOR);
	printf("k1(5): %d\n",k1(5));
	printf("hello %s compiler!\ncompiler name is %s\n",F1,COMPILER_NAME);
	printf("arch: %s\n",TOSTRING(ARCHITECTURE));
	printf("%s\n",PROJECT_VERSION);
	printf("%s\n",program_version);
	d1();

	return 0;
}

int d1(void)
{
	printf("Number of logical cores: %d\n",NUMBER_OF_LOGICAL_CORES);
	printf("Number of physical cores: %d\n",NUMBER_OF_PHYSICAL_CORES);
	printf("Total virtual memory in megabytes: %d\n",TOTAL_VIRTUAL_MEMORY);
	printf("Available virtual memory in megabytes: %d\n",AVAILABLE_VIRTUAL_MEMORY);
	printf("Total physical memory in megabytes: %d\n",TOTAL_PHYSICAL_MEMORY);
	printf("Available physical memory in megabytes: %d\n",AVAILABLE_PHYSICAL_MEMORY);
	printf("Processor is 64Bit: %d\n",IS_64BIT);
	printf("Processor has floating point unit: %d\n",HAS_FPU);
	printf("Processor supports MMX instructions: %d\n",HAS_MMX);
	printf("Processor supports Ext. MMX instructions: %d\n",HAS_MMX_PLUS);
	printf("Processor supports SSE instructions: %d\n",HAS_SSE);

	printf("Processor supports SSE2 instructions: %d\n",HAS_SSE2);
	printf("Processor supports SSE FP instructions: %d\n",HAS_SSE_FP);
	printf("Processor supports SSE MMX instructions: %d\n",HAS_SSE_MMX);
	printf("Processor supports 3DNow instructions: %d\n",HAS_AMD_3DNOW);
	printf("Processor supports 3DNow+ instructions: %d\n",HAS_AMD_3DNOW_PLUS);
	printf("IA64 processor emulating x86 : %d\n",HAS_IA64);
	printf("OS name: %s\n",OS_NAME);
	printf("OS sub-type: %s\n",OS_RELEASE);
	printf("OS build ID: %s\n",OS_VERSION);
	printf("OS platform: %s\n",OS_PLATFORM);
	printf("host name: %s\n",HOSTNAME);
	//printf("FQDN: %s\n",FQDN);
	//printf("PROCESSOR: %s\n",PROCESSOR);
	//printf("PROCESSOR_DESCRIPTION: %s\n",PROCESSOR_DESCRIPTION);

	return 0;
}
