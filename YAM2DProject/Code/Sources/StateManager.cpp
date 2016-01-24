#include "StateManager.h"
#include "SplashScreenState.h"
#include "MainMenuState.h"

#include <iostream>

StateManager::StateManager()
{
	currentState = new SplashScreenState(this);
}
StateManager::~StateManager()
{
	delete currentState;
}


bool StateManager::update(yam2d::ESContext* _context, float _deltaTime)
{
	return currentState->update(_context, _deltaTime);
}


void StateManager::draw(yam2d::ESContext* _context)
{
	currentState->draw(_context);
}


void StateManager::setState(State* _state)
{
	if (_state == nullptr)
	{
		std::cout << "Given state is a nullptr!\nPress any key to continue." << std::endl;
		std::cin.ignore();
	}
	delete currentState;
	currentState = _state;
}