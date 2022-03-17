#pragma once

#include "resource.h"
#include "Point2D.h"

#define RECOIL_X_MAX 300

class Ball
{
public:
	Ball();
	~Ball();

	void Reset();
	void Initialize(ID2D1HwndRenderTarget* m_pRenderTarget);
	void Advance(double elapsedTime);
	void CheckHitsPaddle(float paddleX);
	boolean IsOutside();
	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget);

	Point2D position;
	Point2D speed;
private:

	ID2D1SolidColorBrush* m_pRedBrush;
};

