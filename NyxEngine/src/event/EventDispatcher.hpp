#pragma once

#include "../service/EventDispatcherService.hpp"

namespace NYX {
	class EventDispatcher : public EventDispatcherService {
	public:
		EventDispatcher() = default;
		~EventDispatcher() = default;

		void RegisterCallback(EventId eventId, EventCallback callback) override {
			m_callbacks[eventId] = callback;
		}

		void PostEvent(Event* event) override {
			m_events.push_back(event);
		}

		void Dispatch(uint32_t event_mask) override;

		void Clear() override {
			m_events.clear();
		}
	private:
		std::unordered_map<EventId, EventCallback> m_callbacks;
		std::vector<Event*> m_events;
	};
}