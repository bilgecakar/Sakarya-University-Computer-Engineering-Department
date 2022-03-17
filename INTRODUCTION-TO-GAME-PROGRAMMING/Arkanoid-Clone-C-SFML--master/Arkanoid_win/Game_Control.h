#pragma once

#include "pch.h"
#include "Bar.h"

class Ball; //forward declaration to resolve circular dependency

class Game_Control
{
public:
	bool pause = true;
	bool start = true;
	bool GO = false;

	Game_Control() {}

	void gameOver()
	{
		GO = true;
		pause = true;
	}

	void speedup(Bar& bari, Ball& balli);
	void setStep(double time, double speed);

private:
	Clock clock;
	double timeStep;
	double speedStep;
};