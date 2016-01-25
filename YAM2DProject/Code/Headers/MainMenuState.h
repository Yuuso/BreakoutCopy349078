#pragma once

#include "State.h"

#include <Map.h>
#include <GameObject.h>
#include <Layer.h>


class MainMenuState : public State
{
public:
	MainMenuState(StateManager* _stateManager);
	~MainMenuState();

	bool update(yam2d::ESContext* _context, float _deltaTime);
	void draw(yam2d::ESContext* _context);

private:
	yam2d::vec2 mouseCoords;
	yam2d::GameObject* pickObject;
	yam2d::GameObject* backgroundObject;
	yam2d::GameObject* newGameObject;
	yam2d::GameObject* exitGameObject;
	yam2d::vec2 tileSize;
	yam2d::Map* map;
	yam2d::Layer* background;
	yam2d::Layer* objects;
};