#pragma once

#ifdef NYX_DEBUG
	#define NYX_ASSERT(condition, message, ...) \
		if (!(condition)) { \
			fprintf(stderr, "[ASSERT] %s:%d: %s\n", __FILE__, __LINE__, message); \
			assert(condition); \
		}
	#define NYX_STATIC_ASSERT(condition, message) \
		static_assert(condition, message)
#else
	#define NYX_ASSERT(condition, message, ...)
	#define NYX_STATIC_ASSERT(condition, message)
#endif