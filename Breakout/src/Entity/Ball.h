#pragma once

#include "Entity.h"

namespace Breakout {

	class Ball : public Entity
	{
	public:
		// TODO: Change to radius
		Ball(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f))
			: Entity("Ball", position, size, color) {}

	};

}