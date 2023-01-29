#pragma once

#include "../pch.hpp"

#include "../math/Vec2.hpp"
#include "../event/EventDispatcher.hpp"
#include "../service/Locator.hpp"
#include "../event/system/SystemQuitEvent.hpp"
#include "../event/mouse/MouseDownEvent.hpp"
#include "../event/mouse/MouseUpEvent.hpp"
#include "../event/mouse/MouseMotionEvent.hpp"
#include "../event/mouse/MouseWheelEvent.hpp"
#include "../event/keyboard/KeyDownEvent.hpp"
#include "../event/keyboard/KeyUpEvent.hpp"

namespace NYX {
	struct MouseState {
		MATH::Vec2<uint32_t> position{};
		MATH::Vec2<int32_t> motion{};
		MATH::Vec2<int32_t> wheel{};
		std::bitset<7> buttons{};
	};

	class NYX_API Inputs {
	public:
		static const uint8_t* keyboard;

		Inputs();

		void InitInputs(SDL_Window*);
		void DispatchInputEvents();

		bool IsKeyDown(uint8_t);

		MATH::Vec2<uint32_t> GetMousePosition() const;
		MATH::Vec2<int32_t> GetMouseMotion() const;
		MATH::Vec2<int32_t> GetMouseWheel() const;
		bool IsMouseButtonDown(uint8_t) const;
	private:
		static MouseState s_mouseState;

		EventDispatcherService* m_eventDispatcher;
	};
}