#pragma once

#include "resource.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

#define RESOLUTION_X 800
#define RESOLUTION_Y 600
#define PAUSE_SECONDS 5.0

class Engine
{
public:
	Engine();
	~Engine();

	HRESULT InitializeD2D(HWND m_hwnd);
	void Reset();
	void MousePos(int x, int y);
	void Logic(double elapsedTime);
	HRESULT Draw();

private:
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	Ball* ball;
	Paddle* paddle;
	Brick *bricks[75];

	int mouseXPos;

	boolean playing;
};

