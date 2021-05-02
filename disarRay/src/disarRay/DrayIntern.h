#pragma once

#include <stdio.h>
#include <random>

#ifdef DRAY_PLAT_WIN
	#ifdef DRAY_BUILD
		#define DRAY_API __declspec(dllexport)
	#else
		#define DRAY_API __declspec(dllimport)
	#endif
#else
	#error Platform not supported by disarRay.
#endif

#define draysbyte std::int8_t
#define draybyte std::uint8_t

#define drayint std::int32_t
#define drayuint std::uint32_t

#define draylong std::int64_t
#define drayulong std::uint64_t

#define drayfloat std::float_t
#define draydouble std::double_t
