#pragma once

#include <es_util.h>
#include "State.h"


class StateManager
{
public:
	StateManager();
	~StateManager();

	void update(yam2d::ESContext *context, float deltaTime);
	void draw();
	void setState(State* state);

private:
	State* currentState;
};