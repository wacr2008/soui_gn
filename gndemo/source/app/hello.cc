// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>

extern "C" {
	#include "colorspace.h"
	#include "cpuid.h"
}

#include "hello_shared.h"
#include "hello_static.h"

int main(int argc, char* argv[]) {
  printf("%s, %s\n", GetStaticText(), GetSharedText());

  #ifdef _DEBUG
  	printf("Debug mode \n");
  #endif

  #ifdef NDEBUG
  	printf("Release mode \n");	
  #endif

  colorspace_init();

  	int nCpuFlags = check_cpu_features();
	if (nCpuFlags & XVID_CPU_MMX)
	{
		printf("support MMX \n");	 
	}
	else
	{
		printf("not support MMX \n");	 
	}

	if (nCpuFlags & XVID_CPU_3DNOW)
	{
		printf("support 3DNOW \n");	
	}
	else
	{
		printf("not support 3DNOW \n");	
	}

	if (nCpuFlags & XVID_CPU_MMXEXT)
	{
		printf("support MMXEXT \n");	
	}
	else
	{
		printf("not support MMXEXT \n");	
	}

  getchar();
  return 0;
}
