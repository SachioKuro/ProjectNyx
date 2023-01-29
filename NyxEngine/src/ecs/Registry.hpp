#pragma once

#include "ECS.hpp"

namespace NYX::ECS {
	class Registry {
	public:
		NYX_INLINE void clear() {
			for (auto& [_, componentArray] : _components) {
				NYX_DELETE(componentArray);
			}
			_components.clear();
			_signatures.clear();
			_nextId = INVALID_ID;
		}

		NYX_INLINE entityId addEntity() {
			entityId entity = _nextId++;
			_signatures[entity] = signature();
			return entity;
		}

		NYX_INLINE void destroy(entityId e) {
			for (auto& [_, componentArray] : _components) {
				componentArray->erase(e);
			}
			_signatures.erase(e);
		}

		NYX_INLINE bool isAlive(entityId e) {
			return _signatures.contains(e);
		}

		template<typename T>
		NYX_INLINE entityList view() {
			entityList list;
			for (auto& [entity, signature] : _signatures) {
				if (signature.contains(TypeID<T>())) {
					list.insert(entity);
				}
			}
			return list;
		}

		template<typename T>
		NYX_INLINE T& getComponent(entityId e) {
			NYX_ASSERT(_signatures.contains(e), "out of range");
			return getComponentArray<T>()->get(e);
		}

		template<typename T, typename... Args>
		NYX_INLINE T& addComponent(entityId e, Args&&... args) {
			NYX_ASSERT(_signatures.contains(e), "out of range");
			auto data = T(std::forward<Args>(args)...);
			_signatures[e].insert(TypeID<T>());
			return getComponentArray<T>()->push(e, data);
		}

		template<typename T>
		NYX_INLINE void removeComponent(entityId e) {
			_signatures.at(e).erase(TypeID<T>());
			getComponentArray<T>()->erase(e);
		}

		template<typename T>
		NYX_INLINE bool hasComponent(entityId e) {
			return _signatures.contains(e) && _signatures.at(e).contains(TypeID<T>());
		}

		template<typename T>
		NYX_INLINE ComponentArray<T>* getComponentArray() {
			componentId cid = TypeID<T>();
			if (_components.contains(cid))
				return static_cast<ComponentArray<T>*>(_components.at(cid));
			auto array = new ComponentArray<T>();
			_components[cid] = array;
			return array;
		}

	private:
		std::unordered_map<componentId, ComponentArrayInterface*> _components;
		// TODO: Check if more cache friendly solution is needed,
		//       Currently each entity is processed one by one
		std::unordered_map<entityId, signature> _signatures;
		entityId _nextId = INVALID_ID;
	};
}