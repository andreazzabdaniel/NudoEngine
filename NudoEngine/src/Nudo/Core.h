#pragma once

#include "Log.h"

#define BIT(x) (1 << x)

#ifdef NUDO_DEBUG
	#define ND_ENABLE_ASSERTS
#endif

#ifdef ND_ENABLE_ASSERTS
	#define ND_ASSERT(x, ...) { if(!(x)) { ND_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ND_CORE_ASSERT(x, ...) { if(!(x)) { ND_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ND_ASSERT(x, ...)
	#define ND_CORE_ASSERT(x, ...)
#endif