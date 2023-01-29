#pragma once

#include "../../pch.hpp"
#include "../../core/TypeId.hpp"
#include "MouseEvent.hpp"

namespace NYX {
	class MouseDownEvent : public MouseEvent {
	public:
		MouseDownEvent(uint8_t button) : MouseEvent(TypeID<MouseDownEvent>()), m_button(button) {}
		virtual ~MouseDownEvent() override = default;

		std::string GetName() const override { return "MouseDownEvent"; }
		std::string ToString() const override { return GetName(); }
	protected:
		uint8_t m_button;
	};
}