#include "Inputs.hpp"

namespace NYX {
	using MATH::Vec2;

	const uint8_t* Inputs::keyboard = NULL;
	MouseState Inputs::s_mouseState;

	Inputs::Inputs() : m_eventDispatcher(Locator::GetService<EventDispatcherService>()) {
		InitInputs(Locator::GetService<SDL_Window>());
	}

	void Inputs::InitInputs(SDL_Window* window) {
		keyboard = (uint8_t*)SDL_GetKeyboardState(NULL);
	}

	void Inputs::DispatchInputEvents() {
		static SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				m_eventDispatcher->PostEvent(new SystemQuitEvent());
				break;
			case SDL_MOUSEBUTTONDOWN:
				s_mouseState.buttons.set(event.button.button);
				m_eventDispatcher->PostEvent(new MouseDownEvent(event.button.button));
				break;
			case SDL_MOUSEBUTTONUP:
				s_mouseState.buttons.reset(event.button.button);
				m_eventDispatcher->PostEvent(new MouseUpEvent(event.button.button));
				break;
			case SDL_MOUSEMOTION:
				s_mouseState.position = Vec2<uint32_t>(event.motion.x, event.motion.y);
				s_mouseState.motion = Vec2<int32_t>(event.motion.xrel, event.motion.yrel);
				m_eventDispatcher->PostEvent(new MouseMotionEvent());
				break;
			case SDL_MOUSEWHEEL:
				m_eventDispatcher->PostEvent(new MouseWheelEvent());
				break;
			case SDL_KEYDOWN:
				keyboard = SDL_GetKeyboardState(NULL);
				m_eventDispatcher->PostEvent(new KeyDownEvent(event.key.keysym.scancode));
				break;
			case SDL_KEYUP:
				keyboard = SDL_GetKeyboardState(NULL);
				m_eventDispatcher->PostEvent(new KeyUpEvent(event.key.keysym.scancode));
				break;
			}
		}
		m_eventDispatcher->Dispatch(EventType::SystemEvent);
	}

	bool Inputs::IsKeyDown(uint8_t key) {
		return keyboard[key];
	}

	Vec2<uint32_t> Inputs::GetMousePosition() const {
		return s_mouseState.position;
	}

	Vec2<int32_t> Inputs::GetMouseMotion() const {
		return s_mouseState.motion;
	}

	Vec2<int32_t> Inputs::GetMouseWheel() const {
		return s_mouseState.wheel;
	}

	bool Inputs::IsMouseButtonDown(uint8_t button) const {
		return s_mouseState.buttons.test(button);
	}
}