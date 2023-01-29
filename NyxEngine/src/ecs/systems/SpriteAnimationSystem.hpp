#pragma once

#include "../../pch.hpp"
#include "../System.hpp"
#include "../components/Common.hpp"
#include "../components/Graphics2D.hpp"
#include "../../core/Time.hpp"

namespace NYX::ECS {
	class SpriteAnimationSystem : public System {
		NYX_INLINE void update(float dt) {
			for (auto& entity : view<AnimationComponent>()) {
				auto& transformComponent = entity.getComponent<TransformComponent>();
				auto& animationComponent = entity.getComponent<AnimationComponent>();

				auto& animation = _assets->get<AnimationAsset>(animationComponent.animation)->instance;
				
				int index = (int)(NYX_TICKS_MS() / animationComponent.speed) % animation.frames.size();
				auto& frame = _assets->get<TextureAsset>(animation.frames[index])->instance;

				SDL_FRect dst{
					transformComponent.translate.x, transformComponent.translate.y,
					frame.width * transformComponent.scale.x, frame.height * transformComponent.scale.y
				};

				SDL_RenderCopyExF(
					_renderer,
					frame.data,
					NULL,
					&dst,
					transformComponent.rotation,
					NULL,
					animationComponent.flip
				);
			}
		}
	};
}