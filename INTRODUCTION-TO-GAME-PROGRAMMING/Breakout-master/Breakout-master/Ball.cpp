#include "framework.h"
#include "Point2D.h"
#include "Ball.h"
#include "Paddle.h"
#include "Engine.h"

Ball::Ball() : m_pRedBrush(NULL)
{
	// Initial ball position and speed
	this->Reset();
}

Ball::~Ball()
{
	SafeRelease(&m_pRedBrush);
}

void Ball::Reset()
{
	// Sets an initial ball position and speed. Y is fixed, X is random
	position.x = (double)rand() / (RAND_MAX + 1) * RESOLUTION_X;
	position.y = RESOLUTION_Y - 100;

	speed.x = 200;
	speed.y = -300;
}

void Ball::Initialize(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Initializes Direct2D red brush for drawing
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&m_pRedBrush
	);
}

void Ball::Advance(double elapsedTime)
{
	// Logic of the ball movement. If it hits the upper or lower walls it bounces back
	position.x += speed.x * elapsedTime;
	position.y += speed.y * elapsedTime;

	if (position.x > RESOLUTION_X - 10)
		speed.x = -abs(speed.x);
	if (position.x < 10)
		speed.x = abs(speed.x);
	if (position.y < 10)
		speed.y = abs(speed.y);
}

void Ball::CheckHitsPaddle(float paddleX)
{
	// Checks if the ball hits the paddle. If it does, it bounces back
	if (position.y > RESOLUTION_Y - 20 && speed.y > 0)
	{
		if (position.x > paddleX - PADDLE_WIDTH / 2 && position.x < paddleX + PADDLE_WIDTH / 2)
		{
			// We don't simply want to reverse the speed. In order to make the game more interesting, we change the X speed based on where on the paddle the ball hits
			float paddleHitPos = (position.x - paddleX) / (PADDLE_WIDTH / 2);
			speed.y = -speed.y;
			speed.x = paddleHitPos * RECOIL_X_MAX;
			return;
		}
	}
}

boolean Ball::IsOutside()
{
	// Returns true if the ball is outside the play area on the right side
	return position.y > RESOLUTION_Y;
}

void Ball::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Draws the ball using Direct2D
	D2D1_ELLIPSE ellipseBall = D2D1::Ellipse(
		D2D1::Point2F(position.x, position.y),
		10, 10
	);
	m_pRenderTarget->FillEllipse(&ellipseBall, m_pRedBrush);
}