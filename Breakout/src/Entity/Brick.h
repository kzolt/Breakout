#pragma once

#include "Entity.h"

namespace Breakout {

	class Brick : public Entity
	{
		Brick(const glm::vec3& position, const glm::vec4& color)
			: Entity("Brick", position, glm::vec2(20, 20), color) {}
		~Brick() {}
	};

}