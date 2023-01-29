#pragma once

#include <set>
#include <random>
#include <limits>
#include <vector>
#include <string>
#include <bitset>
#include <cassert>
#include <concepts>
#include <assert.h>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <utility>
#include <format>

#define main SDL_main
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#undef main

#include "core/Assert.hpp"
#include "core/Logging.hpp"
#include "core/Memory.hpp"

#ifdef NYX_EXPORT
	#ifdef _MSC_VER
		#define NYX_API __declspec(dllexport)
	#else
		#define NYX_API __attribute__((visibility("default")))
	#endif
#else
	#ifdef _MSC_VER
		#define NYX_API __declspec(dllimport)
	#else
		#define NYX_API
	#endif
#endif

#if defined(__clang__) || defined(__gcc__)
	#define NYX_INLINE __attribute__((always_inline)) inline
	#define NYX_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
	#define NYX_INLINE __forceinline
	#define NYX_NOINLINE __declspec(noinline)
#else
	#define NYX_INLINE inline
	#define NYX_NOINLINE
#endif