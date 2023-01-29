#pragma once

#include "../pch.hpp"
#include "Asset.hpp"

namespace NYX {
	struct Texture {
		SDL_Texture* data = NULL;
		std::string filename{};
		int width, height = 0;
	};

	struct TextureAsset : Asset {
		NYX_INLINE TextureAsset() = default;
		NYX_INLINE ~TextureAsset() {
			SDL_DestroyTexture(instance.data);
		}

		Texture instance;
	};
}