#pragma once

#include "State.h"


class SplashScreenState : public State
{
public:
	SplashScreenState(StateManager* _stateManager);
	~SplashScreenState();

	void update();
	void draw();
};