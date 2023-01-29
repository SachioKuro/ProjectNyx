#include "Locator.hpp"

namespace NYX {
	std::unordered_map<uint32_t, void*> Locator::s_services = {};
}