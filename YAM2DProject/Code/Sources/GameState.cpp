#include "GameState.h"


GameState::GameState(StateManager* _stateManager) : State(_stateManager)
{

}
GameState::~GameState()
{

}


bool GameState::update(yam2d::ESContext* _context, float _deltaTime)
{
	return true;
}


void GameState::draw(yam2d::ESContext* _context)
{

}