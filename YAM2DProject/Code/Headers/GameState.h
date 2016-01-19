#pragma once

#include "State.h"


class GameState : public State
{
public:
	GameState(StateManager* _stateManager);
	~GameState();

	void update();
	void draw();
};