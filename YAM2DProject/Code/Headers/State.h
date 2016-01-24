#pragma once

#include "StateManager.h"

class StateManager;
class State
{
public:
	State(StateManager* _stateManager)
	{
		stateManager = _stateManager;
	}
	virtual ~State(){}

	virtual bool update(yam2d::ESContext* _context, float _deltaTime){ return true; }
	virtual void draw(yam2d::ESContext* _context){}

protected:
	StateManager* stateManager;
};