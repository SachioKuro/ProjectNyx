#pragma once

#include "../pch.hpp"

namespace NYX::MATH {
	template <class T> requires (std::integral<T> || std::floating_point<T>)
	class Vec2 {
	public:
		T x, y;

		std::string ToString() {
			return std::format("<Vec2 {} {}>", x, y);
		}
	private:
		
	};
}