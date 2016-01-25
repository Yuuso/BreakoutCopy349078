#include "MainMenuState.h"
#include "GameState.h"
#include "CreateGameObject.h"
#include "Input.h"
#include "Camera.h"
#include "SpriteComponent.h"


MainMenuState::MainMenuState(StateManager* _stateManager) : State(_stateManager), tileSize(64.0f, 64.0f), mouseCoords(0.0f, 0.0f)
{
	map = new yam2d::Map(tileSize.x, tileSize.y);

	background = new yam2d::Layer(map, "Background", 1.0f, true, false);
	objects = new yam2d::Layer(map, "Objects", 1.0f, true, false);

	map->addLayer(yam2d::Map::BACKGROUND0, background);
	map->addLayer(yam2d::Map::MAPLAYER0, objects);

	backgroundObject = createSpriteGameObject("Textures/menu_background.png", 1280.0f, 720.0f);
	newGameObject = createSpriteGameObject("Textures/new_game_button.png", 300.0f, 100.0f);
	exitGameObject = createSpriteGameObject("Textures/exit_game_button.png", 300.0f, 100.0f);

	background->addGameObject(backgroundObject);
	objects->addGameObject(newGameObject);
	objects->addGameObject(exitGameObject);

	newGameObject->setPosition(0.0f, -1.0f);
	exitGameObject->setPosition(0.0f, 1.0f);
}
MainMenuState::~MainMenuState()
{
	delete map;
}


bool MainMenuState::update(yam2d::ESContext* _context, float _deltaTime)
{
	map->update(_deltaTime);
	mouseCoords = map->screenToMapCoordinates((float)yam2d::getMouseAxisX(), (float)yam2d::getMouseAxisY());

	pickObject = map->getLayer("Objects")->pick(mouseCoords);
	if (pickObject == newGameObject)
	{
		newGameObject->getComponent<yam2d::SpriteComponent>()->getSprite()->setColor(0.5, 0.5, 0.5);
		if (yam2d::getMouseButtonState(yam2d::MOUSE_LEFT))
		{
			stateManager->setState(new GameState(stateManager));
			return true;
		}
	}
	else
	{
		newGameObject->getComponent<yam2d::SpriteComponent>()->getSprite()->setColor(1.0, 1.0, 1.0);
	}
	if (pickObject == exitGameObject)
	{
		exitGameObject->getComponent<yam2d::SpriteComponent>()->getSprite()->setColor(0.5, 0.5, 0.5);
		if (yam2d::getMouseButtonState(yam2d::MOUSE_LEFT))
		{
			return false;
		}
	}
	else
	{
		exitGameObject->getComponent<yam2d::SpriteComponent>()->getSprite()->setColor(1.0, 1.0, 1.0);
	}

	return true;
}


void MainMenuState::draw(yam2d::ESContext* _context)
{
	map->getCamera()->setScreenSize(_context->width, _context->height, 720, 1280.0f / 720.0f);
	map->render();
}