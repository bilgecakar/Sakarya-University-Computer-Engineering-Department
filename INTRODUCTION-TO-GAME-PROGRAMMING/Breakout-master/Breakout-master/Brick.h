#pragma once

#include "resource.h"
#include "Point2D.h"
#include "Ball.h"

#define BRICK_WIDTH 40
#define BRICK_HEIGHT 20

class Brick
{
public:
	Brick(float xPos, float yPos);
	~Brick();

	void Initialize(ID2D1HwndRenderTarget* m_pRenderTarget);
	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget);
	void BallCollision(Ball* ball);

	Point2D position;
	int health;

private:

	ID2D1SolidColorBrush* m_pGreenBrush;
};

