#pragma once

#include "../../pch.hpp"
#include "../../core/TypeId.hpp"
#include "../../assets/Asset.hpp"

namespace NYX::ECS {
	struct TextComponent {
		NYX_INLINE TextComponent(const TextComponent&) = default;
		NYX_INLINE TextComponent() = default;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_Color color = { 
			.r = 0, 
			.g = 0,
			.b = 0, 
			.a = 255
		};
		assetId font = INVALID_ID;
		std::string text{};
	};
}