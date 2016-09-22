// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is used as a precompiled header for both C and C++ files. So
// any C++ headers must go in the __cplusplus block below.

#if defined(BUILD_PRECOMPILE_H_)
#error You shouldn't include the precompiled header file more than once.
#endif

#define BUILD_PRECOMPILE_H_

#include "config.h"
#include "x264_config.h"