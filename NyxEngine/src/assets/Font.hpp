#pragma once

#include "../pch.hpp"
#include "Asset.hpp"

namespace NYX {
	struct Font {
		TTF_Font* data = NULL;
		std::string filename{};
		int size = 20;
	};

	struct FontAsset : Asset {
		NYX_INLINE FontAsset() = default;
		NYX_INLINE ~FontAsset() {
			TTF_CloseFont(instance.data);
		}

		Font instance;
	};
}