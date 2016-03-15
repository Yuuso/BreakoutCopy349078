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
	- magnetic board (stick y, let x be)
	- multiple balls
	- board speed boost
	- 

levels

score
	- combo timer (circle around the ball? + text)
	- different values

y movement

graphics & sounds
*/

GameLevelState::GameLevelState(StateManager* _stateManager) : State(_stateManager), playerPosition(0.0f, 4.0f), ballPosition(0.0f, 0.0f), ballVelocity(0.0f, 0.1f),
ballSize(40.0f, 40.0f), playerSize(150, 35.0f)
{
	map = new yam2d::TmxMap();
	compFac = new CustomComponentFactory();
	compFac->setCurrentMap(map);
	contactListener = new ContactListener();
	compFac->getPhysicsWorld()->SetContactListener(contactListener);
	if (map->loadMapFile("Maps/test_map.tmx", compFac))
	{
		map->getCamera()->setPosition(yam2d::vec2(map->getWidth() / 2.0f, map->getHeight() / 2.0f));
	}
	else
	{
		msgstream("Error loading TmxMap!");
		stateManager->setState(new MainMenuState(stateManager));
	}
	tileSize = yam2d::vec2(map->getWidth(), map->getHeight());

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
		}
		else if (tileObjects[i]->getName() == "Ball")
		{
			ballObject = tileObjects[i];
		}
	}

	tileAmount = tileObjects.size() - 3; //3 = ball, player, background
	textObject = createTextObject();
	textObject->setPosition(tileSize.x - tileSize.x * 0.15f, tileSize.y - tileSize.y * 0.85f);

	map->getLayer("Tiles")->addGameObject(textObject);
}
GameLevelState::~GameLevelState()
{
	delete map;
	delete compFac;
	delete contactListener;
}


bool GameLevelState::update(yam2d::ESContext* _context, float _deltaTime)
{
	compFac->getPhysicsWorld()->Step(_deltaTime, 10, 10);
	map->update(_deltaTime);

	static bool ballHit = false;
	static bool ballHitThisFrame;
	static b2Vec2 directionVec;//Vector from player to ball when hit

	ballHitThisFrame = false;
	//Collisions
	unsigned int numContacts = contactListener->contacts.size();
	for (unsigned int i = 0; i < numContacts; i++)
	{
		const Contact& contact = contactListener->contacts[i];
		yam2d::GameObject* A = ((PhysicsBody*) contact.fixtureA->GetBody()->GetUserData())->getGameObject();
		yam2d::GameObject* B = ((PhysicsBody*) contact.fixtureB->GetBody()->GetUserData())->getGameObject();
		if ((A->getName() == "Ball" && B->getName() == "Player"))
		{
			//Physics
			if (!ballHit)
			{
				//Reverse last movements ( separate objects )
				A->getComponent<PhysicsBody>()->getBody()->SetTransform(b2Vec2(A->getComponent<PhysicsBody>()->getBody()->GetPosition().x - ballVelocity.x, A->getComponent<PhysicsBody>()->getBody()->GetPosition().y - ballVelocity.y), A->getComponent<PhysicsBody>()->getBody()->GetAngle());
				B->getComponent<PhysicsBody>()->getBody()->SetTransform(b2Vec2(B->getComponent<PhysicsBody>()->getBody()->GetPosition().x - playerSpeed.x, B->getComponent<PhysicsBody>()->getBody()->GetPosition().y - playerSpeed.y), B->getComponent<PhysicsBody>()->getBody()->GetAngle());

				//Direction
				directionVec = A->getComponent<PhysicsBody>()->getBody()->GetPosition() - B->getComponent<PhysicsBody>()->getBody()->GetPosition();
				directionVec.Normalize();
				directionVec *= 0.1f;

				//Check for side hits
				if (A->getComponent<PhysicsBody>()->getBody()->GetPosition().x + A->getSizeInTiles().x * 0.5f <
					B->getComponent<PhysicsBody>()->getBody()->GetPosition().x - B->getSizeInTiles().x * 0.5f
					||
					A->getComponent<PhysicsBody>()->getBody()->GetPosition().x - A->getSizeInTiles().x * 0.5f >
					B->getComponent<PhysicsBody>()->getBody()->GetPosition().x + B->getSizeInTiles().x * 0.5f)
				{
					ballVelocity.x = -ballVelocity.x + playerSpeed.x;
					ballVelocity.y -= directionVec.y;
				}
				else //No side hit
				{
					ballVelocity.y = -ballVelocity.y;
				}
				ballVelocity.x -= (playerObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x - ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x) / 22.0f;

			ballHit = true;
			ballHitThisFrame = true;
			}
		}
		else if ((B->getName() == "Ball" && A->getName() == "Player"))
		{
			//Physics
			if (!ballHit)
			{
				//Reverse last movements ( separate objects )
				B->getComponent<PhysicsBody>()->getBody()->SetTransform(b2Vec2(B->getComponent<PhysicsBody>()->getBody()->GetPosition().x - ballVelocity.x, B->getComponent<PhysicsBody>()->getBody()->GetPosition().y - ballVelocity.y), B->getComponent<PhysicsBody>()->getBody()->GetAngle());
				A->getComponent<PhysicsBody>()->getBody()->SetTransform(b2Vec2(A->getComponent<PhysicsBody>()->getBody()->GetPosition().x - playerSpeed.x, A->getComponent<PhysicsBody>()->getBody()->GetPosition().y - playerSpeed.y), A->getComponent<PhysicsBody>()->getBody()->GetAngle());

				//Direction
				directionVec = B->getComponent<PhysicsBody>()->getBody()->GetPosition() - A->getComponent<PhysicsBody>()->getBody()->GetPosition();
				directionVec.Normalize();
				directionVec *= 0.1f;

				//Check for side hits
				if (B->getComponent<PhysicsBody>()->getBody()->GetPosition().x + B->getSizeInTiles().x * 0.5f <
					A->getComponent<PhysicsBody>()->getBody()->GetPosition().x - A->getSizeInTiles().x * 0.5f
					||
					B->getComponent<PhysicsBody>()->getBody()->GetPosition().x - B->getSizeInTiles().x * 0.5f >
					A->getComponent<PhysicsBody>()->getBody()->GetPosition().x + A->getSizeInTiles().x * 0.5f)
				{
					ballVelocity.x = -ballVelocity.x + playerSpeed.x;
					ballVelocity.y -= directionVec.y;
				}
				else //No side hit
				{
					ballVelocity.y = -ballVelocity.y;
				}
				ballVelocity.x -= (playerObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x - ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x) / 22.0f;

			ballHit = true;
			ballHitThisFrame = true;
			}
		}

		if ((A->getName() == "Ball" && B->getName() == "Tile"))
		{
			//Physics
			if (!ballHit)
			{
				//Check for side hits
				if (A->getComponent<PhysicsBody>()->getBody()->GetPosition().x + A->getSizeInTiles().x * 0.5f <
					B->getComponent<PhysicsBody>()->getBody()->GetPosition().x - B->getSizeInTiles().x * 0.5
					||
					A->getComponent<PhysicsBody>()->getBody()->GetPosition().x - A->getSizeInTiles().x * 0.5f >
					B->getComponent<PhysicsBody>()->getBody()->GetPosition().x + B->getSizeInTiles().x * 0.5)
				{
					ballVelocity.x = -ballVelocity.x;
				}
				else
				{
					ballVelocity.y = -ballVelocity.y;
				}
			ballHit = true;
			ballHitThisFrame = true;
			}

			//Tile actions
			map->deleteGameObject(B);
			tileAmount--;
		}
		else if ((B->getName() == "Ball" && A->getName() == "Tile"))
		{
			//Physics
			if (!ballHit)
			{
				//Check for side hits
				if (B->getComponent<PhysicsBody>()->getBody()->GetPosition().x + B->getSizeInTiles().x * 0.5f <
					A->getComponent<PhysicsBody>()->getBody()->GetPosition().x - A->getSizeInTiles().x * 0.5
					||
					B->getComponent<PhysicsBody>()->getBody()->GetPosition().x - B->getSizeInTiles().x * 0.5f >
					A->getComponent<PhysicsBody>()->getBody()->GetPosition().x + A->getSizeInTiles().x * 0.5)
				{
					ballVelocity.x = -ballVelocity.x;
				}
				else
				{
					ballVelocity.y = -ballVelocity.y;
				}
			ballHit = true;
			ballHitThisFrame = true;
			}

			//Tile actionss
			map->deleteGameObject(A);
			tileAmount--;

		}
	}
	if (!ballHitThisFrame)
	{
		ballHit = false;
	}

	//Restrict ball
	if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x + ballObject->getSizeInTiles().x * 0.5f > tileSize.x
		|| ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x - ballObject->getSizeInTiles().x * 0.5f < 0.0f)
	{
		ballVelocity.x = -ballVelocity.x;
	}
	if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().y - ballObject->getSizeInTiles().x * 0.5f < 0.0f)
	{
		ballVelocity.y = -ballVelocity.y;
	}

	//Win-Lose
	if (tileAmount == 0)
	{
		//Win
		textObject->getComponent<yam2d::TextComponent>()->getText()->setText("YOU WIN!");
		textObject->setPosition(tileSize.x * 0.5f, tileSize.y * 0.5f);
		endTimer -= _deltaTime;
	}
	else if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().y > tileSize.y)
	{
		//Lose
		textObject->getComponent<yam2d::TextComponent>()->getText()->setText("YOU LOSE!");
		textObject->setPosition(tileSize.x * 0.5f, tileSize.y * 0.5f);
		endTimer -= _deltaTime;
	}
	if (endTimer <= 0.0f)
	{
		stateManager->setState(new MainMenuState(stateManager));
		return true;
	}
	
	//Input
	if (yam2d::getKeyState(yam2d::KEY_BACK) || yam2d::getKeyState(yam2d::KEY_ESCAPE))
	{
		stateManager->setState(new MainMenuState(stateManager));
		return true;
	}
	playerSpeed = yam2d::vec2(0.0f);
	if (!ballHit)
	{
		if (yam2d::getKeyState(yam2d::KEY_D))
		{
			playerSpeed = yam2d::vec2(0.1f, 0.0f);
		}
		if (yam2d::getKeyState(yam2d::KEY_A))
		{
			playerSpeed = yam2d::vec2(-0.1f, 0.0f);
		}
	}
	playerObject->getComponent<PhysicsBody>()->getBody()->SetTransform(playerObject->getPosition() + playerSpeed, 0.0f);

	//Restrict
	if (playerObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x + playerObject->getSizeInTiles().x * 0.5f  > tileSize.x)
	{
		playerObject->getComponent<PhysicsBody>()->getBody()->SetTransform(playerObject->getPosition() - b2Vec2(0.1f, 0.0f), 0.0f);
	}
	else if (playerObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x - playerObject->getSizeInTiles().x * 0.5f  < 0.0f)
	{
		playerObject->getComponent<PhysicsBody>()->getBody()->SetTransform(playerObject->getPosition() + b2Vec2(0.1f, 0.0f), 0.0f);
	}

	//
	ballObject->getComponent<PhysicsBody>()->getBody()->SetTransform(ballObject->getPosition() + (ballVelocity), 0.0f);
	if (endTimer >= 3.0f)
	{
		textObject->getComponent<yam2d::TextComponent>()->getText()->setText("Tiles Left: " + std::to_string(tileAmount));
	}

	return true;
}


void GameLevelState::draw(yam2d::ESContext* _context)
{
	map->getCamera()->setScreenSize(_context->width, _context->height, 768.0f, 1280.0f / 768.0f);
	map->render();
}