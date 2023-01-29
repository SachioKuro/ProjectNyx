#pragma once

#include "../../pch.hpp"
#include "../System.hpp"
#include "../components/Graphics2D.hpp"
#include "../components/Common.hpp"

namespace NYX::ECS {
	class TilemapRendererSystem : public System {
	public:
		NYX_INLINE void update(float) {
			for (auto& entity : view<TilemapComponent>()) {
				auto& transformComponent = entity.getComponent<TransformComponent>();
				auto& tilemapComponent = entity.getComponent<TilemapComponent>().tilemap;
				auto& tilemap = _assets->get<TilemapAsset>(tilemapComponent)->instance;

				for (auto& tileEntity : view<TileComponent>()) {
					auto& tileComponent = tileEntity.getComponent<TileComponent>();
					if (tileComponent.tilemap != tilemapComponent && !tilemap.tilesets.contains(tileComponent.tileset)) {
						continue;
					}

					float x = tileComponent.offset_x + transformComponent.translate.x;
					float y = tileComponent.offset_y + transformComponent.translate.y;

					drawTile(
						tileComponent.tileset,
						x,
						y,
						tileComponent.tile_x,
						tileComponent.tile_y,
						tilemap.tilesize,
						tileComponent.flip
					);
				}
			}
		}
	private:
		NYX_INLINE void drawTile(assetId tilesetId, float x, float y, int row, int col, int size, SDL_RendererFlip flip) {
			SDL_Rect srcRect = { row * size, col * size, size, size };
			SDL_FRect dstRect = { x * size, y * size, size, size };

			auto& tileset = _assets->get<TextureAsset>(tilesetId)->instance;

			SDL_RenderCopyExF(_renderer, tileset.data, &srcRect, &dstRect, 0, NULL, flip);
			SDL_RenderDrawRectF(_renderer, &dstRect);
		}
	};
}