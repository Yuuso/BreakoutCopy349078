#pragma once

#include "State.h"


class GameState : public State
{
public:
	GameState(StateManager* _stateManager);
	~GameState();

	bool update(yam2d::ESContext* _context, float _deltaTime);
	void draw(yam2d::ESContext* _context);
};