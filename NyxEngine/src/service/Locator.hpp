#pragma once

#include "../pch.hpp"
#include "../core/TypeId.hpp"

namespace NYX {
	class Locator {
	public:
		template<typename T>
		static T* GetService() {
			return static_cast<T*>(s_services[TypeID<T>()]);
		}

		template<typename T>
		static void SetService(T* service) {
			s_services[TypeID<T>()] = service;
		}
	private:
		static std::unordered_map<uint32_t, void*> s_services;
	};
}