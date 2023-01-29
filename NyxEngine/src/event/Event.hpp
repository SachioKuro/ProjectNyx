#pragma once

#include "../pch.hpp"
#include "../core/Bit.hpp" 

namespace NYX {
	using EventId = uint32_t;

	enum EventType {
		WindowEvent = BIT(1),
		KeyEvent = BIT(2),
        MouseEvent = BIT(3),
        MouseButtonEvent = BIT(4),
        MouseScrollEvent = BIT(5),
        MouseMoveEvent = BIT(6),
        MouseEnterEvent = BIT(7),
        MouseLeaveEvent = BIT(8),
        MouseDragEvent = BIT(9),
        MouseDropEvent = BIT(10),
        SystemEvent = BIT(11)
	};

    std::string EventTypeToString(EventType type);

    class Event {
    public:
        Event(EventId id) : m_id(id) {}
        virtual ~Event() = default;
        
        NYX_INLINE virtual EventId GetId() const { return m_id; }
        NYX_INLINE virtual std::string GetName() const = 0;
        NYX_INLINE virtual std::string ToString() const = 0;
        NYX_INLINE virtual EventType GetType() const = 0;

        NYX_INLINE virtual bool Is(EventId id) const { return m_id == id; }
        NYX_INLINE virtual bool IsHandled() const { return m_handled; }
        NYX_INLINE virtual void SetHandled() { m_handled = true; }
    private:
        EventId m_id;
        bool m_handled = false;
    };
}