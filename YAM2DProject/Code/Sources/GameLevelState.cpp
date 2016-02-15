#include "GameLevelState.h"
#include "CreateGameObject.h"
#include "MainMenuState.h"
#include "PhysicsBody.h"
#include "CreateTextObject.h"
#include "CustomComponentFactory.h"

#include <Camera.h>
#include <Input.h>
#include <TextComponent.h>

#include "DEBUGiostream.h"


/*
Power ups
levels
score
tile hitting physics
*/

GameLevelState::GameLevelState(StateManager* _stateManager) : State(_stateManager), playerPosition(0.0f, 4.0f), ballPosition(0.0f, 0.0f), ballVelocity(0.0f, 0.1f),
ballSize(40.0f, 40.0f), playerSize(150, 35.0f)
{
	map = new yam2d::TmxMap();
	compFac = new CustomComponentFactory();
	compFac->setCurrentMap(map);
	if (map->loadMapFile("Maps/test_map.tmx", compFac))
	{
		map->getCamera()->setPosition(yam2d::vec2(map->getWidth() / 2.0f, map->getHeight() / 2.0f));
	}
	else
	{
		msgstream("Error loading TmxMap!");
		stateManager->setState(new MainMenuState(stateManager));
	}
	tileSize = yam2d::vec2(map->getTileWidth(), map->getTileHeight());

	yam2d::Map::LayerMap layers = map->getLayers();
	yam2d::Layer::GameObjectList goList;
	for (unsigned i = 0; i < layers.size(); i++)
	{
		if (layers[i])
		{
			goList = layers[i]->getGameObjects();
			for (unsigned i = 0; i < goList.size(); i++)
			{
				tileObjects.push_back(goList[i]);
			}
		}
	}
	for (unsigned i = 0; i < tileObjects.size(); i++)
	{
		if (tileObjects[i]->getName() == "Player")
		{
			playerObject = tileObjects[i];
			//tileObjects.erase[i];
		}
		else if (tileObjects[i]->getName() == "Ball")
		{
			ballObject = tileObjects[i];
			//tileObjects.erase[i];
		}
	}
}
GameLevelState::~GameLevelState()
{
	delete map;
	delete compFac;
}


bool GameLevelState::update(yam2d::ESContext* _context, float _deltaTime)
{
	compFac->getPhysicsWorld()->Step(_deltaTime, 10, 10);
	map->update(_deltaTime);

	//static bool ballHit;
	//ballHit = false;
	////Collisions
	//unsigned int numContacts = contactListener->contacts.size();
	//for (unsigned int i = 0; i < numContacts; i++)
	//{
	//	const Contact& contact = contactListener->contacts[i];
	//	yam2d::GameObject* A = ((PhysicsBody*) contact.fixtureA->GetBody()->GetUserData())->getGameObject();
	//	yam2d::GameObject* B = ((PhysicsBody*) contact.fixtureB->GetBody()->GetUserData())->getGameObject();
	//	if ((A->getName() == "Player" && B->getName() == "Ball") || (B->getName() == "Player" && A->getName() == "Ball"))
	//	{
	//		if (!ballHit)
	//		{
	//			ballVelocity.y = -ballVelocity.y;
	//			ballObject->getComponent<PhysicsBody>()->getBody()->SetTransform(ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition() - (ballVelocity / 2.0f), 0.0f);
	//			ballVelocity.x -= (playerObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x - ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x) / 20.0f;
	//		}
	//		ballHit = true;
	//	}
	//	if ((A->getName() == "Ball" && B->getName() == "Tile"))
	//	{
	//		//Physics
	//		if (!ballHit)
	//		{
	//			ballVelocity.y = -ballVelocity.y;
	//			if (A->getComponent<PhysicsBody>()->getBody()->GetPosition().x > B->getComponent<PhysicsBody>()->getBody()->GetPosition().x)
	//			{
	//				ballVelocity.x = -ballVelocity.x;
	//			}
	//		}
	//		ballHit = true;

	//		//Tile actions
	//		map->deleteGameObject(B);
	//		tileAmount--;
	//	}
	//	else if ((B->getName() == "Ball" && A->getName() == "Tile"))
	//	{
	//		//Physics
	//		if (!ballHit)
	//		{
	//			ballVelocity.y = -ballVelocity.y;
	//		}
	//		ballHit = true;

	//		//Tile actionss
	//		map->deleteGameObject(A);
	//		tileAmount--;

	//	}
	//}

	//Restrict ball
	//if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x > ((float)_context->width/2.0f) / tileSize.x
	//	|| ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x < -((float) _context->width / 2.0f) / tileSize.x)
	//{
	//	ballVelocity.x = -ballVelocity.x;
	//}
	//if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().y < -((float) _context->height / 2.0f) / tileSize.y)
	//{
	//	ballVelocity.y = -ballVelocity.y;
	//}

	////Win-Lose
	//if (tileAmount == 0)
	//{
	//	//Win
	//	textObject->getComponent<yam2d::TextComponent>()->getText()->setText("YOU WIN!");
	//	textObject->setPosition(0.0f, 0.0f);
	//	endTimer -= _deltaTime;
	//}
	//else if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().y > ((float) _context->height / 2.0f) / tileSize.y)
	//{
	//	//Lose
	//	textObject->getComponent<yam2d::TextComponent>()->getText()->setText("YOU LOSE!");
	//	textObject->setPosition(0.0f, 0.0f);
	//	endTimer -= _deltaTime;
	//}
	//if (endTimer <= 0.0f)
	//{
	//	stateManager->setState(new MainMenuState(stateManager));
	//	return true;
	//}
	
	//Input
	if (yam2d::getKeyState(yam2d::KEY_BACK) || yam2d::getKeyState(yam2d::KEY_ESCAPE))
	{
		stateManager->setState(new MainMenuState(stateManager));
		return true;
	}
	//if (yam2d::getKeyState(yam2d::KEY_D))
	//{
	//	playerObject->getComponent<PhysicsBody>()->getBody()->SetTransform(playerObject->getPosition() + yam2d::vec2(0.1f, 0.0f), 0.0f);
	//}
	//if (yam2d::getKeyState(yam2d::KEY_A))
	//{
	//	playerObject->getComponent<PhysicsBody>()->getBody()->SetTransform(playerObject->getPosition() + yam2d::vec2(-0.1f, 0.0f), 0.0f);
	//}

	//
	//ballObject->getComponent<PhysicsBody>()->getBody()->SetTransform(ballObject->getPosition() + ballVelocity, 0.0f);
	ballObject->getComponent<PhysicsBody>()->getBody()->ApplyForceToCenter(ballVelocity*50.0f);
	//if (endTimer >= 3.0f)
	//{
	//	textObject->getComponent<yam2d::TextComponent>()->getText()->setText("Tiles Left: " + std::to_string(tileAmount));
	//}

	return true;
}


void GameLevelState::draw(yam2d::ESContext* _context)
{
	map->getCamera()->setScreenSize(_context->width, _context->height, 768.0f, 1280.0f / 768.0f);
	map->render();
}