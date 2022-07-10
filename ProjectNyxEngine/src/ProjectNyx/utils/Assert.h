#pragma once

#ifdef NYX_ASSERTION_ENABLED
#include <intrin.h>

#define NYX_ASSERT(expr) \
	if (expr) {} \
	else { \
		/*reportAssertionFailure(#expr, __FILE__, __LINE__)*/ \
		__debugbreak(); \
	}

#define NYX_STATIC_ASSERT(expr, msg) \
	static_assert(expr, msg);

#else

#define NYX_ASSERT(expr)

#endif

