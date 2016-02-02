#pragma once

#include "State.h"
#include "ContactListener.h"

#include <Map.h>
#include <Layer.h>
#include <GameObject.h>
#include <TextComponent.h>
#include <Box2D\Box2D.h>

#include <vector>


class GameState : public State
{
public:
	GameState(StateManager* _stateManager);
	~GameState();

	bool update(yam2d::ESContext* _context, float _deltaTime);
	void draw(yam2d::ESContext* _context);

private:
	yam2d::vec2 playerPosition;
	yam2d::vec2 ballPosition;
	yam2d::vec2 tileSize;
	yam2d::vec2 ballVelocity;
	yam2d::Map* map;
	yam2d::GameObject* backgroundObject;
	yam2d::GameObject* playerObject;
	yam2d::GameObject* ballObject;
	yam2d::GameObject* textObject;
	yam2d::Layer* background;
	yam2d::Layer* objects;
	std::vector<yam2d::GameObject*> tileObjects;

	int tileAmount;
	float endTimer = 3.0f;

	b2World* boxWorld;
	ContactListener* contactListener;
};