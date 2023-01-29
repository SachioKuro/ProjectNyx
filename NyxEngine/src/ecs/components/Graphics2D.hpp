#pragma once

#include "../../pch.hpp"
#include "../../core/TypeId.hpp"
#include "../../assets/Asset.hpp"

namespace NYX::ECS {
	struct SpriteComponent {
		NYX_INLINE SpriteComponent(const SpriteComponent&) = default;
		NYX_INLINE SpriteComponent() = default;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		assetId sprite = INVALID_ID;
	};

	struct AnimationComponent { 
		NYX_INLINE AnimationComponent(const AnimationComponent&) = default;
		NYX_INLINE AnimationComponent() = default;

		assetId animation = INVALID_ID;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		float speed = 300.0f;
		float time = 0.0f;
	};

	struct TilemapComponent {
		NYX_INLINE TilemapComponent(const TilemapComponent&) = default;
		NYX_INLINE TilemapComponent() = default;

		assetId tilemap = INVALID_ID;
	};

	struct TileComponent {
		NYX_INLINE TileComponent(const TileComponent&) = default;
		NYX_INLINE TileComponent() = default;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		assetId tilemap = INVALID_ID;
		assetId tileset = INVALID_ID;
		float offset_x, offset_y = 0.0f;
		int tile_x, tile_y = 0;
	};
}