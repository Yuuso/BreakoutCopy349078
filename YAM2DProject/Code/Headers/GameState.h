#pragma once

#include "State.h"
#include <Map.h>


class GameState : public State
{
public:
	GameState(StateManager* _stateManager);
	~GameState();

	bool update(yam2d::ESContext* _context, float _deltaTime);
	void draw(yam2d::ESContext* _context);

private:
	yam2d::vec2 tileSize;
	yam2d::Map* map;
};