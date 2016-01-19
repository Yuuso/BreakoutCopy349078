#pragma once

#include "State.h"


class MainMenuState : public State
{
public:
	MainMenuState(StateManager* _stateManager);
	~MainMenuState();

	void update();
	void draw();
};