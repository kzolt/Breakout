#pragma once

#include <glm/glm.hpp>

#include "Entity/Paddle.h"
#include "Entity/Brick.h"
#include "Entity/Ball.h"

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"

// ---- Remove ----
#include "Graphics/VertexArray.h"
#include "Graphics/Buffer.h"
// ----------------

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

		Camera* m_Camera;
		Shader* m_Shader;
	};

}