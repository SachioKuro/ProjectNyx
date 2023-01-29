#pragma once

#include "../../core/UUID.hpp"
#include "../../math/Vec2.hpp"

namespace NYX::ECS {
	struct InfoComponent {
		NYX_INLINE InfoComponent(const InfoComponent&) = default;
		NYX_INLINE InfoComponent() = default;

		uuid64 uuid = NYX::GenerateUUID();
		std::string name = "Entity";
		std::string tag = "Default";
	};

	struct TransformComponent {
		NYX_INLINE TransformComponent(const TransformComponent&) = default;
		NYX_INLINE TransformComponent() = default;

		NYX::MATH::Vec2<float> translate = NYX::MATH::Vec2<float>(0.0f, 0.0f);
		NYX::MATH::Vec2<float> scale = NYX::MATH::Vec2<float>(1.0f, 1.0f);
		float rotation = 0.0f;
	};
}