#pragma once

#include <glm/glm.hpp>

#include "Entity/Paddle.h"
#include "Entity/Brick.h"
#include "Entity/Ball.h"
#include "Entity/Label.h"

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Renderer/Texture.h"

namespace Breakout {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);
		void OnRender();

	private:
		Paddle* m_Paddle;
		Ball* m_Ball;
		std::vector<Brick*> m_Bricks;

		Label m_ScoreLabel;
		Label m_ScoreLabelValue;

		Camera* m_Camera;

		std::shared_ptr<Texture> m_BallTexture;
	};

}