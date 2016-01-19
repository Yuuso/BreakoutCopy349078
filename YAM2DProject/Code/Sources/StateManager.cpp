#include "StateManager.h"
#include "SplashScreenState.h"

#include <iostream>

StateManager::StateManager()
{
	currentState = new SplashScreenState();
}
StateManager::~StateManager()
{
	delete currentState;
}


void StateManager::update(yam2d::ESContext *context, float deltaTime)
{
	currentState->update();
}


void StateManager::draw()
{
	currentState->draw();
}


void StateManager::setState(State* state)
{
	if (state == nullptr)
	{
		std::cout << "Given state is a nullptr!\nPress any key to continue." << std::endl;
		std::cin.ignore();
	}
	delete currentState;
	currentState = state;
}