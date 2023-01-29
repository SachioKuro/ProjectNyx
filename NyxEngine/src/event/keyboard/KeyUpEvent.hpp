#pragma once

#include "../../pch.hpp"
#include "../../core/TypeId.hpp"
#include "KeyEvent.hpp"

namespace NYX {
	class KeyUpEvent : public KeyEvent {
	public:
		KeyUpEvent(uint8_t key) : KeyEvent(TypeID<KeyUpEvent>(), key) {}
		virtual ~KeyUpEvent() override = default;

		std::string GetName() const override { return "KeyUpEvent"; }
		std::string ToString() const override { return GetName(); }
	};
}