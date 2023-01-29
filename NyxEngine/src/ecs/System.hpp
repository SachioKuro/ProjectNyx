#pragma once

#include "../pch.hpp"
#include "Entity.hpp"
#include "../assets/Registry.hpp"

namespace NYX::ECS {
	class System {
	public:
		NYX_INLINE virtual ~System() = default;

		NYX_INLINE void prepare(Registry* registry, SDL_Renderer* renderer, AssetRegistry* assets) {
			_registry = registry;
			_renderer = renderer;
			_assets = assets;
		}

		template<typename T>
		NYX_INLINE auto view() {
			std::vector<Entity> entities;
			for (auto& e : _registry->view<T>()) {
				entities.push_back(Entity(e, _registry));
			}
			return entities;
		}

		NYX_INLINE virtual void update(float) {}
		NYX_INLINE virtual void start() {}

	protected:
		AssetRegistry* _assets = NULL;
		SDL_Renderer* _renderer = NULL;

	private:
		Registry* _registry = NULL;
	};
}