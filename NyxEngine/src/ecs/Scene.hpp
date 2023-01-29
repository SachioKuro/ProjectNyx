#pragma once

#include "../pch.hpp"
#include "../assets/Registry.hpp"
#include "components/Common.hpp"
#include "systems/TestSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "systems/SpriteRendererSystem.hpp"
#include "systems/TextRendererSystem.hpp"
#include "systems/TilemapRendererSystem.hpp"
#include "Registry.hpp"

namespace NYX::ECS {
	class Scene {
	public:
		NYX_INLINE Scene(SDL_Renderer* renderer) : _renderer(renderer) {
			//registerSystem<TestSystem>();
			registerSystem<SpriteAnimationSystem>();
			registerSystem<SpriteRendererSystem>();
			registerSystem<TextRendererSystem>();
			registerSystem<TilemapRendererSystem>();
		}

		NYX_INLINE ~Scene() {
			for (auto& s : _systems) {
				NYX_DELETE(s);
			}
			_registry.clear();
			_systems.clear();
		}

		NYX_INLINE Entity addEntity(const std::string& name) {
			auto entity = Entity(&_registry);
			entity.addComponent<InfoComponent>().name = name;
			entity.addComponent<TransformComponent>();
			return entity;
		}

		NYX_INLINE void update(float dt) {
			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			for (auto& system : _systems)
				system->update(dt);
		}

		NYX_INLINE void start() {
			//{
			//	auto sprite = _assets.loadTexture("D:\\Dev\\ProjectNyx\\out\\x64\\Debug\\ProjectNyx\\sprite.png", "test", _renderer);
			//	Entity entity = addEntity("sprite_entity");
			//	entity.addComponent<SpriteComponent>().sprite = sprite->id;
			//}
			auto root = std::string("D:\\Dev\\ProjectNyx\\out\\x64\\Debug\\ProjectNyx\\");

			{
				auto tilesetTexture = _assets.loadTexture(root + "stone_house_interior.png", "", _renderer);

				auto tilemap = _assets.add<TilemapAsset>("tilemap");
				tilemap->instance.tilesets.insert(tilesetTexture->id);
				tilemap->instance.colCount = 16;
				tilemap->instance.rowCount = 16;
				tilemap->instance.tilesize = 32;

				addEntity("tilemap").addComponent<TilemapComponent>().tilemap = tilemap->id;

				for (int col = 0; col < tilemap->instance.colCount; ++col) {
					for (int row = 0; row < tilemap->instance.rowCount; ++row) {
						Entity entity = addEntity("tile");
						auto& tileComponent = entity.addComponent<TileComponent>();
						tileComponent.tileset = tilesetTexture->id;
						tileComponent.tilemap= tilemap->id;
						tileComponent.offset_x = col;
						tileComponent.offset_y = row;
						tileComponent.tile_x = col;
						tileComponent.tile_y = row;
					}
				}
			}
			
			{
				auto frames = std::vector<std::string>{
					root + "chara2_4\\down_stand.png",
					root + "chara2_4\\down_walk1.png",
					root + "chara2_4\\down_walk2.png",
					root + "chara2_4\\laugh1.png",
					root + "chara2_4\\laugh2.png",
					root + "chara2_4\\laugh3.png",
					root + "chara2_4\\left_stand.png",
					root + "chara2_4\\left_walk1.png",
					root + "chara2_4\\left_walk2.png",
					root + "chara2_4\\nod1.png",
					root + "chara2_4\\nod2.png",
					root + "chara2_4\\nod3.png",
					root + "chara2_4\\pose1.png",
					root + "chara2_4\\pose2.png",
					root + "chara2_4\\pose3.png",
					root + "chara2_4\\right_stand.png",
					root + "chara2_4\\right_walk1.png",
					root + "chara2_4\\right_walk2.png",
					root + "chara2_4\\shake1.png",
					root + "chara2_4\\shake2.png",
					root + "chara2_4\\shake3.png",
					root + "chara2_4\\surprise.png",
					root + "chara2_4\\up_stand.png",
					root + "chara2_4\\up_walk1.png",
					root + "chara2_4\\up_walk2.png"
				};

				auto animationAsset = _assets.add<AnimationAsset>("walk");
				for (auto& frame : frames) {
					auto texture = _assets.loadTexture(frame, "test", _renderer);
					animationAsset->instance.frames.push_back(texture->id);
				}
				animationAsset->instance.speed = 50;
				
				Entity entity = addEntity("sprite_animation_entity");
				auto& transform = entity.addComponent<TransformComponent>();
				transform.translate.x = 200;
				transform.translate.y = 200;
				auto& animationComponent = entity.addComponent<AnimationComponent>();
				animationComponent.animation = animationAsset->id;
			}

			{
				auto font = _assets.loadFont(root + "angel.ttf", "test_font", 24);
				Entity entity = addEntity("text_entity");
				auto& text = entity.addComponent<TextComponent>();
				text.font = font->id;
				text.text = "Hello Universe!";
				
			}

			for (auto& system : _systems)
				system->start();
		}

		template<typename T> requires (std::is_base_of<System, T>::value)
		NYX_INLINE void registerSystem() {
			auto sys = new T();
			sys->prepare(&_registry, _renderer, &_assets);
			_systems.push_back(sys);
		}
	private:
		std::vector<System*> _systems;
		SDL_Renderer* _renderer = NULL;
		Registry _registry;
		AssetRegistry _assets;
	};
}