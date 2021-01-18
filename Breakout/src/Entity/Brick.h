#pragma once

#include "Entity.h"

namespace Breakout {

	class Brick : public Entity
	{
	public:
		Brick(const glm::vec3& position, const glm::vec4& color, int health = 10)
			: Entity("Brick", position, glm::vec2(5.0f, 1.0f), color), m_Health(health) {}
		~Brick() {}

	private:
		int m_Health;
	};

}