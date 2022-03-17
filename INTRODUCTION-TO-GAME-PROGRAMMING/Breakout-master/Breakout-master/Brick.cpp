#include "framework.h"
#include "Point2D.h"
#include "Brick.h"
#include "Ball.h"
#include "Engine.h"

Brick::Brick(float xPos, float yPos) : m_pGreenBrush(NULL)
{
	position.x = xPos;
	position.y = yPos;
	health = 1;
}

Brick::~Brick()
{
	SafeRelease(&m_pGreenBrush);
}

void Brick::Initialize(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Creates a blue brush for drawing
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Green),
		&m_pGreenBrush
	);
}

void Brick::BallCollision(Ball* ball)
{

	if (health > 0)
	{

		float brickTop = position.y - BRICK_HEIGHT / 2;
		float brickBottom = position.y + BRICK_HEIGHT / 2;
		float brickLeft = position.x - BRICK_WIDTH / 2;
		float brickRight = position.x + BRICK_WIDTH / 2;

		float ballTop = ball->position.y - 10;
		float ballBottom = ball->position.y + 10;
		float ballLeft = ball->position.x - 10;
		float ballRight = ball->position.x + 10;

		// If it's a collision
		if (ballTop < brickBottom && ballBottom > brickTop && ballRight > brickLeft && ballLeft < brickRight)
		{
			float distanceX1 = abs(ballRight - brickLeft);
			float distanceX2 = abs(ballLeft - brickRight);
			float distanceY1 = abs(ballTop - brickBottom);
			float distanceY2 = abs(ballBottom - brickTop);

			// From bottom
			if (ball->speed.y < 0 && distanceY1 < distanceY2 && distanceY1 < distanceX1 && distanceY1 < distanceX2)
			{
				ball->speed.y = abs(ball->speed.y);
				health = 0;
			}
			// From top
			if (ball->speed.y > 0 && distanceY2 < distanceY1 && distanceY2 < distanceX1 && distanceY2 < distanceX2)
			{
				ball->speed.y = -abs(ball->speed.y);
				health = 0;
			}
			// From left
			if (ball->speed.x > 0 && distanceX1 < distanceX2 && distanceX1 < distanceY1 && distanceX1 < distanceY2)
			{
				ball->speed.x = -abs(ball->speed.x);
				health = 0;
			}
			// From right
			if (ball->speed.x < 0 && distanceX2 < distanceX1 && distanceX2 < distanceY1 && distanceX2 < distanceY2)
			{
				ball->speed.x = abs(ball->speed.x);
				health = 0;
			}
		}

	}

}

void Brick::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	if (health > 0)
	{

		// Draws a rectangle representing the brick
		D2D1_RECT_F rectangle1 = D2D1::RectF(
			position.x - BRICK_WIDTH / 2 + 1, position.y - BRICK_HEIGHT / 2 + 1,
			position.x + BRICK_WIDTH / 2 - 1, position.y + BRICK_HEIGHT / 2 - 1
		);
		m_pRenderTarget->FillRectangle(&rectangle1, m_pGreenBrush);

	}

}
