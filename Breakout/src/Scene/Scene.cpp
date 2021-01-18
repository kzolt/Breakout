#include "bkout.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Entity/Paddle.h"
#include "Scene.h"
#include "Renderer/Renderer.h"

namespace Breakout {

	Scene::Scene()
	{
		m_Shader = new Shader("res/shaders/basic.glsl");
		m_Camera = new Camera(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		m_Paddle = new Paddle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(5.0f, 5.0f), glm::vec4(0.501f, 0.0f, 0.125f, 1.0f));
	}

	Scene::~Scene()
	{
		delete m_Paddle;
		delete m_Shader;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Paddle Movement
		// Ball Movement
		// Brick Stuff
	}

	void Scene::OnRender()
	{
		Renderer::Clear();
		m_Shader->Bind();
		m_Shader->SetMat4("u_ViewProjection", m_Camera->GetViewProjection());

		// Render
		Renderer::BeginScene(m_Camera->GetViewProjection());
		Renderer::DrawQuad(m_Paddle->GetPosition(), m_Paddle->GetSize(), m_Paddle->GetColor());
		Renderer::EndScene();
	}

}