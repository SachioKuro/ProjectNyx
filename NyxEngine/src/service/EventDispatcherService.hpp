#pragma once

#include "../event/Event.hpp"

namespace NYX {
	using EventCallback = std::function<void(Event*)>;

	class EventDispatcherService {
	public:
		EventDispatcherService() = default;
		virtual ~EventDispatcherService() = default;

		virtual void RegisterCallback(EventId evetId, EventCallback callback) = 0;
		virtual void PostEvent(Event* event) = 0;
		virtual void Dispatch(uint32_t event_mask) = 0;
		virtual void Clear() = 0;
	};
}