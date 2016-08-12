#ifndef _COMMON_CPU_ID_H
#define _COMMON_CPU_ID_H

extern "C"
{
	#include "emms.h"
}

//确认这些和cpuid.asm定义是一致的
#define XVID_CPU_MMX      (1<< 0)
#define XVID_CPU_MMXEXT   (1<< 1)
#define XVID_CPU_SSE      (1<< 2)
#define XVID_CPU_SSE2     (1<< 3)
#define XVID_CPU_SSE3     (1<< 8)
#define XVID_CPU_SSE41    (1<< 9)
#define XVID_CPU_3DNOW    (1<< 4)
#define XVID_CPU_3DNOWEXT (1<< 5)
#define XVID_CPU_TSC      (1<< 6)

#endif