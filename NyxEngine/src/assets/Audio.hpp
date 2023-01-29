#pragma once

#include "../pch.hpp"
#include "Asset.hpp"

namespace NYX {
	struct AudioClip {
		Mix_Chunk* data = NULL;
		std::string filename{};
	};

	struct AudioAsset : Asset {
		NYX_INLINE AudioAsset() = default;
		NYX_INLINE ~AudioAsset() {
			Mix_FreeChunk(instance.data);
		}

		AudioClip instance;
	};
}