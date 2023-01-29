#pragma once

#include "../pch.hpp"
#include "../core/TypeId.hpp"

namespace NYX::ECS {
	using entityId = uint64_t;
	using componentId = uint32_t;
	using signature = std::set<uint32_t>;
	using entityList = std::set<entityId>;

	class ComponentArrayInterface {
	public:
		NYX_INLINE virtual ~ComponentArrayInterface() = default;
		virtual void erase(entityId) = 0;
	};

	template<typename T>
	struct ComponentArrayEntry {
		NYX_INLINE ComponentArrayEntry(entityId entity, const T& data)
			: entity(entity), data(data) {}
		NYX_INLINE operator entityId() const { return entity; }

		entityId entity = INVALID_ID;
		T data;
	};

	template<typename T>
	class ComponentArray : public ComponentArrayInterface {
	public:
		NYX_INLINE T& push(entityId e, const T& data) {
			if (exist(e)) return get(e);
			_data.push_back(ComponentArrayEntry(e, data));
			return _data.back().data;
		}

		NYX_INLINE void erase(entityId e) {
			auto it = std::find(_data.begin(), _data.end(), e);
			if (it != _data.end()) _data.erase(it);
		}

		NYX_INLINE bool exist(entityId e) {
			return std::find(_data.begin(), _data.end(), e) != _data.end();
		}

		NYX_INLINE T& get(entityId e) {
			NYX_ASSERT(exist(e), "Entity out of range!");
			return (*std::find(_data.begin(), _data.end(), e)).data;
		}
	private:
		std::vector<ComponentArrayEntry<T>> _data;
	};
}