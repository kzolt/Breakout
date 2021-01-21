#include "bkout.h"

#include "System/Application.h"

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

namespace Breakout {

	//////////////////////////////////////////////////////////////////////////////
	// Helpers
	//////////////////////////////////////////////////////////////////////////////

	static bool RangeIntersect(float min0, float max0, float min1, float max1)
	{
		return (std::max(min0, max0) >= std::min(min1, max1)) && (std::min(min0, max0) <= std::max(min1, max1));
	}

	// Entity 1 can be any shape
	// Entity 2 is required to be a rectangle
	static bool EntityCollision(Entity* entity1, Entity* entity2)
	{
		return RangeIntersect(entity1->GetPosition().x, entity1->GetPosition().x + entity1->GetSize().x, entity2->GetPosition().x - (entity2->GetSize().x / 2), entity2->GetPosition().x + (entity2->GetSize().x / 2)) &&
			RangeIntersect(entity1->GetPosition().y, entity1->GetPosition().y + entity1->GetSize().y, entity2->GetPosition().y, entity2->GetPosition().y + entity2->GetSize().y);
	}

	//////////////////////////////////////////////////////////////////////////////
	// Paddle
	//////////////////////////////////////////////////////////////////////////////

	void Paddle::OnUpdate(Timestep ts)
	{
		auto mousePos = Application::GetWindow()->GetMousePos();											// Get Mouse Position (Screen Space)
		float mousePosRel = (float)(mousePos.first / Application::GetWindow()->GetWindowProps().Width);		// Convert Mouse Position from Screen Width to value between 0 and 1
		float mouseX = (mousePosRel * 32) - 16;																// Convert between 0 and 1 to -16 and 16

		m_LastMousePosition = mouseX;

		if (mouseX > m_Position.x)
			m_CurrentDirection = PaddleDirection::Right;
		else if (mouseX < m_Position.x)
			m_CurrentDirection = PaddleDirection::Left;
		else if (mouseX == m_LastMousePosition)
			m_CurrentDirection = PaddleDirection::Stationary;

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
		{
			// Ball Going left and paddle going right make it change directions, otherwise if the ball is going left and the paddle is going left then make it bounce
			if (m_Speed.x < 0 && paddle->GetDirection() == PaddleDirection::Right)
				m_Speed *= -1;
			else if (m_Speed.x < 0 && paddle->GetDirection() == PaddleDirection::Left)
				m_Speed.y *= -1;

			// Ball going right and paddle going right make it bounce, otherwise if the paddle is going left and the ball is going right, change directions
			if (m_Speed.x > 0 && paddle->GetDirection() == PaddleDirection::Right)
				m_Speed.y *= -1;
			else if (m_Speed.x > 0 && paddle->GetDirection() == PaddleDirection::Left)
				m_Speed *= -1;

			// If the paddle hasn't moved from it's spot then bounce in a random direction (to keep people on their toes)
			if (paddle->GetDirection() == PaddleDirection::Stationary)
			{
				if (Random::Float() < 0.5f)
					m_Speed *= -1;
				else
					m_Speed.y *= -1;
			}
		}

		// Bounds Check
		if (m_Position.x <= -16.0f || m_Position.x >= 16.0f)
			m_Speed.x *= -1.0f;
		if (m_Position.y <= -9.0f || m_Position.y >= 9.0f)
			m_Speed.y *= -1.0f;
	}

	//////////////////////////////////////////////////////////////////////////////
	// Brick
	//////////////////////////////////////////////////////////////////////////////
	void Brick::OnUpdate(Timestep ts, Ball* ball)
	{
		if (EntityCollision(ball, this))
		{
			m_Health -= 11;
			m_Color.r -= 0.1f;

			if (Random::Float() < 0.5f)
				ball->GetSpeed() *= -1;
			else
				ball->GetSpeed().y *= -1;
		}
	}


}