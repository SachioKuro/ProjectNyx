#include "EventDispatcher.hpp"

namespace NYX {
	void EventDispatcher::Dispatch(uint32_t event_mask) {
		for (auto* event : m_events) {
			if (event->GetType() & event_mask) {
				NYX_ASSERT(
					m_callbacks.find(event->GetType()) != m_callbacks.end(),
					"No callbacks registered for event type: %s",
					EventTypeToString(event->GetType())
				)
				m_callbacks[event->GetType()](event);
			}
		}
	}
}