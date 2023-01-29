#include "Event.hpp"

namespace NYX {
    std::string EventTypeToString(EventType type) {
        switch (type) {
        case WindowEvent: return "WindowEvent";
        case KeyEvent: return "KeyEvent";
        case MouseEvent: return "MouseEvent";
        case MouseButtonEvent: return "MouseButtonEvent";
        case MouseScrollEvent: return "MouseScrollEvent";
        case MouseMoveEvent: return "MouseMoveEvent";
        case MouseEnterEvent: return "MouseEnterEvent";
        case MouseLeaveEvent: return "MouseLeaveEvent";
        case MouseDragEvent: return "MouseDragEvent";
        case MouseDropEvent: return "MouseDropEvent";
        case SystemEvent: return "SystemEvent";
        default: return "UnknownEvent";
        }
    }
}