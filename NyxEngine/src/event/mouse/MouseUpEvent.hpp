#pragma once

#include "../../pch.hpp"
#include "../../core/TypeId.hpp"
#include "MouseEvent.hpp"

namespace NYX {
	class MouseUpEvent : public MouseEvent {
	public:
		MouseUpEvent(uint8_t button) : MouseEvent(TypeID<MouseUpEvent>()), m_button(button) {}
		virtual ~MouseUpEvent() override = default;

		std::string GetName() const override { return "MouseUpEvent"; }
		std::string ToString() const override { return GetName(); }
	protected:
		uint8_t m_button;
	};
}