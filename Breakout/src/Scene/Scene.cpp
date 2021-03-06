#include "bkout.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
#include "Renderer/Renderer.h"
#include "System/Application.h"

namespace Breakout {

	Scene::Scene()
		: m_ScoreLabel(Label("Score: ", glm::vec3(-10.0f, -8.0f, 0.0f), glm::vec4(1.0f))),
		  m_ScoreLabelValue(Label("0", glm::vec3(-8.0f, -8.0f, 0.0f), glm::vec4(1.0f)))
	{
		m_Camera = new Camera(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		m_Paddle = new Paddle(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec2(5.0f, 1.0f));
		m_Ball = new Ball(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		m_BallTexture = std::make_shared<Texture>("res/textures/ball.png");
		
		// Bricks
		float xpos = -13.2f;
		float ypos = 6.5f;
		glm::vec4 brickColor = glm::vec4(0.501f, 0.0f, 0.125f, 1.0f);
		float healths[] = { 40, 30, 20, 10 };
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 6; y++)
			{
				m_Bricks.push_back(new Brick(glm::vec3(xpos, ypos, 0.0f), brickColor, healths[x]));
				xpos += 5.3;
			}

			xpos = -13.2f;
			ypos -= 1.5f;

			brickColor.r -= 0.1f;
		}

	}

	Scene::~Scene()
	{
		delete m_Paddle;
		delete m_Ball;
		for (size_t i = 0; i < m_Bricks.size(); i++)
			delete m_Bricks[i];
		
		delete m_Camera;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Paddle Movement (Note: Only works in 16:9 aspect ratio)
		m_Paddle->OnUpdate(ts);

		// Ball Movement
		m_Ball->OnUpdate(ts, m_Paddle);

		// Brick Stuff
		for (size_t i = 0; i < m_Bricks.size(); i++)
		{
			m_Bricks[i]->OnUpdate(ts, m_Ball);

			if (m_Bricks[i]->GetHealth() < 0)
				m_Bricks.erase(m_Bricks.begin() + i);
		}

		if (m_Bricks.empty())
			m_Ball->GetSpeed() = { 0.0f, 0.0f };

		// Update Score
		m_ScoreLabelValue.SetText(std::to_string(m_Ball->GetScore()));
	}

	void Scene::OnRender()
	{
		Renderer::Clear();
		
		// Render
		Renderer::BeginScene(m_Camera->GetViewProjection());
		Renderer::DrawQuad(m_Paddle->GetPosition(), m_Paddle->GetSize(), m_Paddle->GetColor());

		for (size_t i = 0; i < m_Bricks.size(); i++)
			Renderer::DrawQuad(m_Bricks[i]->GetPosition(), m_Bricks[i]->GetSize(), m_Bricks[i]->GetColor());

		Renderer::DrawQuad(m_Ball->GetPosition(), m_Ball->GetSize(), m_BallTexture);

		Renderer::DrawLabel(m_ScoreLabel);
		//Renderer::DrawLabel(m_ScoreLabelValue);

		Renderer::EndScene();
	}

}