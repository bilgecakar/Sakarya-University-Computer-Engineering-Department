#pragma once

#include "resource.h"
#include "Point2D.h"

#define PADDLE_WIDTH 100

class Paddle
{
public:
	Paddle(float yPos);
	~Paddle();

	void Initialize(ID2D1HwndRenderTarget* m_pRenderTarget);
	void MoveToPosition(int xPos);
	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget);

	Point2D position;

private:

	ID2D1SolidColorBrush* m_pBlueBrush;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;
};

