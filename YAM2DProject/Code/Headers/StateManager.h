#pragma once

#include <es_util.h>
#include "State.h"

class State;
class StateManager
{
public:
	StateManager();
	~StateManager();

	bool update(yam2d::ESContext* _context, float _deltaTime);
	void draw(yam2d::ESContext* _context);
	void setState(State* _state); //NOTE: return from update immediately after calling for new state!

private:
	State* currentState;
};