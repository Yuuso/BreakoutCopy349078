#include "GameState.h"

#include <Camera.h>


GameState::GameState(StateManager* _stateManager) : State(_stateManager), tileSize(64.0f, 64.0f)
{
	map = new yam2d::Map(tileSize.x, tileSize.y);
}
GameState::~GameState()
{
	delete map;
}


bool GameState::update(yam2d::ESContext* _context, float _deltaTime)
{
	map->update(_deltaTime);

	return true;
}


void GameState::draw(yam2d::ESContext* _context)
{
	map->getCamera()->setScreenSize(_context->width, _context->height, 720, 1280.0f / 720.0f);
	map->render();
}