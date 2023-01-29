#pragma once

#include "../../pch.hpp"
#include "../../core/TypeId.hpp"
#include "KeyEvent.hpp"

namespace NYX {
	class KeyDownEvent : public KeyEvent {
	public:
		KeyDownEvent(uint8_t key) : KeyEvent(TypeID<KeyDownEvent>(), key) {}
		virtual ~KeyDownEvent() override = default;

		std::string GetName() const override { return "KeyDownEvent"; }
		std::string ToString() const override { return GetName(); }
	};
}