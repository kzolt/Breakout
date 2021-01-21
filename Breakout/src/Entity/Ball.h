#pragma once

#include "Entity.h"

namespace Breakout {

	class Ball : public Entity
	{
	public:
		Ball(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(0.0f))
			: Entity("Ball", position, size, color) , m_Score(0)
		{
			m_Speed = { 0.245f, -0.245 };
		}

		inline glm::vec2& GetSpeed() { return m_Speed; }
		inline int& GetScore() { return m_Score; }

		void OnUpdate(Timestep ts, Paddle* paddle);

	private:
		glm::vec2 m_Speed;
		int m_Score;
	};

}