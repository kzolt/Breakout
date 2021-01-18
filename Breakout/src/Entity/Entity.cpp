#include "bkout.h"

#include "System/Application.h"

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

namespace Breakout {

	//////////////////////////////////////////////////////////////////////////////
	// Helpers
	//////////////////////////////////////////////////////////////////////////////

	static bool EntityCollision(Entity* entity1, Entity* entity2)
	{
		return (entity1->GetPosition().x + (entity2->GetSize().x / 2) < entity2->GetPosition().x + entity2->GetSize().x &&
			entity1->GetPosition().x + entity1->GetSize().x > entity2->GetPosition().x &&
			entity1->GetPosition().y < entity2->GetPosition().y + entity2->GetSize().y &&
			entity1->GetPosition().y + entity1->GetSize().y > entity2->GetPosition().y);
	}

	//////////////////////////////////////////////////////////////////////////////
	// Paddle
	//////////////////////////////////////////////////////////////////////////////

	void Paddle::OnUpdate(Timestep ts)
	{
		auto mousePos = Application::GetWindow()->GetMousePos();											// Get Mouse Position (Screen Space)
		float mousePosRel = (float)(mousePos.first / Application::GetWindow()->GetWindowProps().Width);		// Convert Mouse Position from Screen Width to value between 0 and 1
		float mouseX = (mousePosRel * 32) - 16;																// Convert between 0 and 1 to -16 and 16

		// Set Position
		m_Position.x = mouseX;

		// If mouse goes beyond bounds set the position of the paddle to the edge of the screen
		if (mouseX <= -13.5f)
			m_Position.x = -13.5f;
		if (mouseX >= 13.5f)
			m_Position.x = 13.5f;
	}

	//////////////////////////////////////////////////////////////////////////////
	// Ball
	//////////////////////////////////////////////////////////////////////////////

	void Ball::OnUpdate(Timestep ts, Paddle* paddle)
	{
		// Change Ball Position
		m_Position.x += m_Speed.x;
		m_Position.y += m_Speed.y;


		// Collision
		if (EntityCollision(this, paddle))
			m_Speed *= -1.0f;

		// Bounds Check
		if (m_Position.x <= -16.0f)
			m_Speed.x *= -1.0f;
		if (m_Position.x >= 16.0f)
			m_Speed.x *= -1.0f;
		if (m_Position.y <= -9.0f)
			m_Speed.y *= -1.0f;
		if (m_Position.y >= 9.0f)
			m_Speed.y *= -1.0f;
	}

	//////////////////////////////////////////////////////////////////////////////
	// Brick
	//////////////////////////////////////////////////////////////////////////////
	void Brick::OnUpdate(Timestep ts, Ball* ball)
	{
		if (EntityCollision(this, ball))
		{
			m_Health -= 11;
			m_Color.r -= 0.1f;

			ball->GetSpeed() *= -1;
		}
	}


}