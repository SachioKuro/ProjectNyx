#pragma once

#include "Asset.hpp"

namespace NYX {
	struct Tilemap {
		std::set<assetId> tilesets;
		int colCount, rowCount, tilesize = 0;
	};

	struct TilemapAsset : Asset {
		NYX_INLINE TilemapAsset() = default;
		
		Tilemap instance;
	};
}