#pragma once

/*
* Copyright (C) Microvolution, LLC - All Rights Reserved
*
* Confidential and proprietary
*
* Microvolution, LLC retains all intellectual property and proprietary rights
* in and to this software and related documentation and any modifications
* thereto. The intellectual and technical concepts contained herein are
* proprietary to Microvolution, LLC and are protected by trade secret or
* copyright law.
* Any use, reproduction, disclosure, or distribution of this software and
* related documentation without an express license agreement from
* Microvolution, LLC is strictly prohibited.
*/

#if _WIN32
 #if MICROVOLUTION_COMPILING
  #define MICROVOLUTION_EXPORT __declspec(dllexport)
 #else
  #define MICROVOLUTION_EXPORT __declspec(dllimport)
 #endif
#else
 #define MICROVOLUTION_EXPORT __attribute__((visibility("default")))
#endif
