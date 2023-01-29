#pragma once

#include "Animation.hpp"
#include "Asset.hpp"
#include "Audio.hpp"
#include "Font.hpp"
#include "Texture.hpp"
#include "Tilemap.hpp"
#include "../core/TypeId.hpp"

namespace NYX {
	class AssetRegistry {
	public:
		NYX_INLINE void clear() {
			for (auto& [_, list] : _data)
				for (auto d : list) 
					NYX_DELETE(d);
			_data.clear();
		}

		template<typename T> requires (std::is_base_of<Asset, T>::value)
		NYX_INLINE T* get(assetId id) {
			const auto type = TypeID<T>();
			
			if (!_data.contains(type))
				return NULL;

			for (auto& asset : _data.at(type))
				if (asset->id == id)
					return static_cast<T*>(asset);

			return NULL;
		}

		template<typename T> requires (std::is_base_of<Asset, T>::value)
		NYX_INLINE T* get(const std::string& name) {
			assetId id = getId<T>(name);
			return get<T>(id);
		}

		template<typename T> requires (std::is_base_of<Asset, T>::value)
		NYX_INLINE assetId getId(const std::string& name) {
			const auto type = TypeID<T>();

			if (!_data.contains(type))
				return INVALID_ID;

			for (auto& asset : _data.at(type))
				if (!asset->name.compare(name))
					return asset->id;
			
			return INVALID_ID;
		}

		template<typename T>
		NYX_INLINE T* add(const std::string& name) {
			auto asset = new T();
			asset->name = name;
			_data[TypeID<T>()].push_back(asset);
			return asset;
		}

		// ####### Textures #######
		NYX_INLINE TextureAsset* loadTexture(
			const std::string& src,
			const std::string& name,
			SDL_Renderer* renderer
		) {
			Texture texture = {
				.data = IMG_LoadTexture(renderer, src.c_str()),
				.filename = src
			};

			if (!texture.data) {
				NYX_ERROR("%s\n", IMG_GetError());
				return NULL;
			}

			SDL_QueryTexture(texture.data, NULL, NULL, &texture.width, &texture.height);
			auto asset = new TextureAsset();
			asset->instance = texture;
			asset->name = name;
			_data[TypeID<TextureAsset>()].push_back(asset);
			return asset;
		}

		// ####### Fonts #######
		NYX_INLINE FontAsset* loadFont(const std::string& src, const std::string& name, int size) {
			Font font{
				.data = TTF_OpenFont(src.c_str(), size),
				.filename = src,
				.size = size
			};
			
			if (!font.data) {
				NYX_ERROR("%s\n", TTF_GetError());
				return NULL;
			}
			
			auto asset = new FontAsset();
			asset->instance = font;
			asset->name = name;
			
			_data[TypeID<FontAsset>()].push_back(asset);
			return asset;
		}

	private:
		std::unordered_map<assetId, std::vector<Asset*>> _data;
	};
}