#pragma once

#include "Registry.hpp"

namespace NYX::ECS {
	class Entity {
	public:
		NYX_INLINE Entity(Registry* r) : _registry(r) {
			_id = r->addEntity();
		}

		NYX_INLINE Entity(entityId e, Registry* r) : _id(e), _registry(r) {}

		NYX_INLINE operator entityId() {
			return _id;
		}

		NYX_INLINE Entity() = default;

		template<typename T, typename... Args>
		NYX_INLINE T& addComponent(Args&&... args) {
			return _registry->addComponent<T>(_id, std::forward<Args>(args)...);
		}

		template<typename T>
		NYX_INLINE T& getComponent() {
			return _registry->getComponent<T>(_id);
		}

		template<typename T>
		NYX_INLINE void removeComponent() {
			_registry->removeComponent<T>(_id);
		}

		template<typename T>
		NYX_INLINE bool hasComponent() {
			return _registry->hasComponent<T>(_id);
		}

		template<typename T>
		NYX_INLINE bool isAlive() {
			return _registry && _registry->isAlive(_id);
		}

		NYX_INLINE entityId id() {
			return _id;
		}

		NYX_INLINE void destroy() {
			_registry->destroy(_id);
		}


	private:
		entityId _id = INVALID_ID;
		Registry* _registry = NULL;
	};
}