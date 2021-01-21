#pragma once

#include "Entity.h"

namespace Breakout {

	enum class PaddleDirection
	{
		None = 0, Left, Right, Stationary
	};

	class Paddle : public Entity
	{
	public:
		Paddle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
			: Entity(std::string("Paddle"), position, size, color), m_CurrentDirection(PaddleDirection::None), m_LastMousePosition(0.0f) {}
		~Paddle() {}

		inline PaddleDirection GetDirection() const { return m_CurrentDirection; }
		
		void OnUpdate(Timestep ts);

	private:
		PaddleDirection m_CurrentDirection;
		float m_LastMousePosition;
	};

}