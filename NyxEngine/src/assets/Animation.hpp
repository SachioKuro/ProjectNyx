#pragma once

#include "Asset.hpp"

namespace NYX {
	struct Animation {
		std::vector<assetId> frames;
		int speed = 100;
	};

	struct AnimationAsset : Asset {
		NYX_INLINE AnimationAsset() = default;
		Animation instance;
	};
}