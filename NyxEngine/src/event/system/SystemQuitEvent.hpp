#pragma once

#include "../../pch.hpp"
#include "../../core/TypeId.hpp"
#include "SystemEvent.hpp"

namespace NYX {
	class SystemQuitEvent : public SystemEvent {
	public:
		SystemQuitEvent() : SystemEvent(TypeID<SystemQuitEvent>()) {}
		virtual ~SystemQuitEvent() override = default;

		std::string GetName() const override { return "SystemQuitEvent"; }
		std::string ToString() const override { return GetName(); }
	};
}