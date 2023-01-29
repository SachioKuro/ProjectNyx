#pragma once

#include "../../pch.hpp"
#include "../../core/TypeId.hpp"
#include "MouseEvent.hpp"

namespace NYX {
	class MouseMotionEvent : public MouseEvent {
	public:
		MouseMotionEvent() : MouseEvent(TypeID<MouseMotionEvent>()) {}
		virtual ~MouseMotionEvent() override = default;

		std::string GetName() const override { return "MouseMotionEvent"; }
		std::string ToString() const override { return GetName(); }
	};
}