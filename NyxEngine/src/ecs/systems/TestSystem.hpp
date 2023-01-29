#pragma once

#include "../System.hpp"
#include "../components/Common.hpp"

namespace NYX::ECS {
	class TestSystem : public System {
	public:
		void update(float dt) {
			for (auto& e : view<TransformComponent>()) {
				auto& t = e.getComponent<TransformComponent>();
				NYX_INFO("id: [%d], x: %f\n", e.id(), t.translate.x++);
			}
		}
	};
}