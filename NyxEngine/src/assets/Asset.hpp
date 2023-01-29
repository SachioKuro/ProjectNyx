#pragma once

#include <cstdint>

#include "../core/UUID.hpp"

namespace NYX {
	using assetTypeId = uint32_t;
	using assetId = uuid64;

	struct Asset {
		NYX_INLINE virtual ~Asset() = default;

		assetId id = GenerateUUID();
		std::string name{};
	};
}