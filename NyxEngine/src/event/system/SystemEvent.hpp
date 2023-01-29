#pragma once

#include "../../pch.hpp"
#include "../Event.hpp"

namespace NYX {
	class SystemEvent : public Event {
	public:
		SystemEvent(EventId id) : Event(id) {}
		virtual ~SystemEvent() override = default;

		EventType GetType() const override { return EventType::SystemEvent; }
	};
}