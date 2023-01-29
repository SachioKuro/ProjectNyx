#pragma once

#include "../../pch.hpp"
#include "../System.hpp"
#include "../components/Common.hpp"
#include "../components/Graphics2D.hpp"

namespace NYX::ECS {
	class SpriteRendererSystem : public System {
		NYX_INLINE void update(float dt) {
			for (auto& entity : view<SpriteComponent>()) {
				auto& transform = entity.getComponent<TransformComponent>();
				auto& sprite = entity.getComponent<SpriteComponent>();

				auto& spriteTexture = _assets->get<TextureAsset>(sprite.sprite)->instance;

				SDL_FRect dst {
					transform.translate.x, transform.translate.y,
					spriteTexture.width * transform.scale.x, spriteTexture.height * transform.scale.y
				};

				SDL_RenderCopyExF(_renderer, spriteTexture.data, NULL, &dst, transform.rotation, NULL, sprite.flip);
			}
		}
	};
}