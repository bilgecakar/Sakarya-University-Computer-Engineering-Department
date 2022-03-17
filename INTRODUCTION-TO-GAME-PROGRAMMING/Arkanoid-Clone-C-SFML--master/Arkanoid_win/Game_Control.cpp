#include "pch.h"
#include "Game_Control.h"
#include "Ball.h"

void Game_Control::speedup(Bar& bari, Ball& balli)
{
	bari.speedup(speedStep);
	balli.speedup(speedStep);
}

void Game_Control::setStep(double time, double speed)
{
	timeStep = time;
	speedStep = speed;
}
