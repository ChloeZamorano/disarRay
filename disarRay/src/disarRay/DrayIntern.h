#pragma once

// DLL importing/exporting
#ifdef DRAY_PLAT_WIN
	#ifdef DRAY_SHARED_LIB
		#ifdef DRAY_BUILD
			#define DRAY_API __declspec(dllexport)
		#else
			#define DRAY_API __declspec(dllimport)
		#endif
	#else
		#define DRAY_API
	#endif
#else
	#error Platform not supported by disarRay.
#endif


// Bit masks
#define BIT(x) (1 << x)

// Bind function
#define DRAY_BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

// File without path
#ifdef DRAY_PLAT_WIN
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif



// Universal includes
#include "TypedefsINeed.h"
#include "Logging/Log.h"



// Dynamic loggers
#ifdef DRAY_BUILD
	#define DRAY_DYN_TRACE(x, ...)	DRAY_ENGINE_TRACE(x, __VA_ARGS__)
	#define DRAY_DYN_INFO(x, ...)	DRAY_ENGINE_INFO(x, __VA_ARGS__)
	#define DRAY_DYN_WARN(x, ...)	DRAY_ENGINE_WARN(x, __VA_ARGS__)
	#define DRAY_DYN_ERROR(x, ...)	DRAY_ENGINE_ERROR(x, __VA_ARGS__)
	#define DRAY_DYN_FATAL(x, ...)	DRAY_ENGINE_FATAL(x, __VA_ARGS__)
#else
	#define DRAY_DYN_TRACE(x, ...)	DRAY_TRACE(x, __VA_ARGS__)
	#define DRAY_DYN_INFO(x, ...)	DRAY_INFO(x, __VA_ARGS__)
	#define DRAY_DYN_WARN(x, ...)	DRAY_WARN(x, __VA_ARGS__)
	#define DRAY_DYN_ERROR(x, ...)	DRAY_ERROR(x, __VA_ARGS__)
	#define DRAY_DYN_FATAL(x, ...)	DRAY_FATAL(x, __VA_ARGS__)
#endif



// Procedural breakpoint
#ifdef DRAY_PLAT_WIN
	#define DRAY_BREAK __debugbreak()
#else
	#define DRAY_BREAK int dray_debug_break_int = (int)1 / (int)0;
#endif



// Verification
#ifndef DRAY_DEPLOY
	#define DRAY_ENGINE_VERIFY(x, y, z)							\
	{															\
		if(x == 0)												\
		{														\
			DRAY_ENGINE_ERROR("Verification failed: {2}", y);	\
			DRAY_BREAK;											\
		}														\
		else													\
		{														\
			DRAY_ENGINE_INFO("Verification successful: {2}", z);\
		}														\
	}
	#define DRAY_VERIFY(x, y, z)							\
	{														\
		if(x == 0)											\
		{													\
			DRAY_ERROR("Verification failed: {2}", y);		\
			DRAY_BREAK;										\
		}													\
		else												\
		{													\
			DRAY_INFO("Verification successful: {2}", z);	\
		}													\
	}
#elif
	#define DRAY_ENGINE_VERIFY(x, ...) x;
	#define DRAY_VERIFY(x, ...) x;
#endif

// Assertion
#ifdef DRAY_DEBUG
	#define DRAY_ENGINE_ASSERT(x, y, z)						\
	{														\
		if(x == 0)											\
		{													\
			DRAY_ENGINE_ERROR("Assetion failed: {2}", y);	\
			DRAY_BREAK;										\
		}													\
		else												\
		{													\
			DRAY_ENGINE_INFO("Assetion successful: {2}", z);\
		}													\
	}
	#define DRAY_ASSERT(x, y, z)						\
	{													\
		if(x == 0)										\
		{												\
			DRAY_ERROR("Assetion failed: {2}", y);		\
			DRAY_BREAK;									\
		}												\
		else											\
		{												\
			DRAY_INFO("Assetion successful: {2}", z);	\
		}												\
	}
#else
	#define DRAY_ENGINE_ASSERT(x, ...)
	#define DRAY_ASSERT(x, ...)
#endif



// Result codes
enum DRAY_FAILMASK
{
	DRAY_FAILMASK_SUCCESS				= BIT(0),
	DRAY_FAILMASK_INSUFFICIENT_MEMORY	= BIT(1),
	DRAY_FAILMASK_INVALID_FILE			= BIT(2),
	DRAY_FAILMASK_COULD_NOT_OPEN_FILE	= BIT(3),
};



// Endianness
#define DRAY_SWAP_16(x) (		\
	((x << 8) & 0xFF00) |		\
	((x >> 8) & 0x00FF))
#define DRAY_SWAP_32(x) (		\
	((x >> 24) & 0x000000FF) |	\
	((x << 8)  & 0x00FF0000) |	\
	((x >> 8)  & 0x0000FF00) |	\
	((x << 24) & 0xFF000000))
