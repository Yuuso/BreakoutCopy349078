#pragma once

#include "StateManager.h"


class State
{
public:
	State(StateManager* _stateManager)
	{
		stateManager = _stateManager;
	}
	~State(){}

	virtual void update(){}
	virtual void draw(){}

private:
	StateManager* stateManager;
};