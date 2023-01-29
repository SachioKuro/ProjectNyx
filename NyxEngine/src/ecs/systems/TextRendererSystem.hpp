#pragma once

#include "../System.hpp"
#include "../components/Common.hpp"
#include "../components/UI.hpp"

namespace NYX::ECS {
	class TextRendererSystem : public System {
	public:
		NYX_INLINE void update(float) {
			for (auto& entity : view<TextComponent>()) {
				auto& transform = entity.getComponent<TransformComponent>();
				auto& text = entity.getComponent<TextComponent>();
				auto& font = _assets->get<FontAsset>(text.font)->instance;
				
				SDL_Surface* surface = TTF_RenderText_Solid(font.data, text.text.c_str(), text.color);
				if (!surface) {
					SDL_Log("TTF_RenderText_Solid: %s", TTF_GetError());
					continue;
				}

				SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
				SDL_FreeSurface(surface);
				if (!texture) {
					SDL_Log("SDL_CreateTextureFromSurface: %s", SDL_GetError());
					continue;
				}

				int width, height;
				SDL_QueryTexture(texture, NULL, NULL, &width, &height);
				SDL_Rect dstrect = {
					.x = (int)transform.translate.x,
					.y = (int)transform.translate.y,
					.w = (int)(width * transform.scale.x),
					.h = (int)(height * transform.scale.y)
				};

				SDL_RenderCopyEx(_renderer, texture, NULL, &dstrect, transform.rotation, NULL, text.flip);
				SDL_DestroyTexture(texture);
			}
		}
	};
}