#pragma once

#include "../../pch.hpp"
#include "../Event.hpp"

namespace NYX {
	class KeyEvent : public Event {
	public:
		KeyEvent(EventId id, uint8_t key) : Event(id), m_key(key) {}
		virtual ~KeyEvent() override = default;

		EventType GetType() const override { return EventType::KeyEvent; }
	protected:
		uint8_t m_key;
	};
}