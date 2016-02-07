#include "GameState.h"
#include "CreateGameObject.h"
#include "MainMenuState.h"
#include "PhysicsBody.h"
#include "CreateTextObject.h"

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

GameState::GameState(StateManager* _stateManager) : State(_stateManager), tileSize(64.0f, 64.0f), playerPosition(0.0f, 4.0f), ballPosition(0.0f, 0.0f), ballVelocity(0.0f, 0.1f)
{
	tileAmount = 5;

	boxWorld = new b2World(yam2d::vec2(0.0f, 0.0f));
	boxWorld->SetAllowSleeping(false);
	contactListener = new ContactListener();
	boxWorld->SetContactListener(contactListener);

	map = new yam2d::Map(tileSize.x, tileSize.y);

	background = new yam2d::Layer(map, "Background", 1.0f, true, true);
	objects = new yam2d::Layer(map, "Objects", 1.0f, true, false);

	map->addLayer(yam2d::Map::BACKGROUND0, background);
	map->addLayer(yam2d::Map::MAPLAYER0, objects);

	backgroundObject = createSpriteGameObject("Textures/menu_background.png", 1280.0f, 720.0f);
	
	yam2d::vec2 playerSize(220.0f, 50.0f);
	playerObject = createSpriteGameObject("Textures/player.png", 220.0f, 50.0f);
	PhysicsBody* Playerbody = new PhysicsBody(playerObject, boxWorld, 1.0f, 1.0f);
	Playerbody->setBoxFixture(playerSize / tileSize, yam2d::vec2(0.0f, 0.0f), playerObject->getRotation(), true);
	playerObject->addComponent(Playerbody);
	playerObject->setName("Player");
	playerObject->getComponent<PhysicsBody>()->getBody()->SetTransform(playerPosition, 0.0f);

	yam2d::vec2 ballSize(50.0f, 50.0f);
	ballObject = createSpriteGameObject("Textures/ball.png", 50.0f, 50.f);
	PhysicsBody* ballBody = new PhysicsBody(ballObject, boxWorld, 1.0f, 1.0f);
	ballBody->setCircleFixture((ballSize.x / tileSize.x) / 2 , true);
	ballObject->addComponent(ballBody);
	ballObject->setName("Ball");
	ballObject->getComponent<PhysicsBody>()->getBody()->SetTransform(ballPosition, 0.0f);

	for (int i = 0; i < tileAmount; i++)
	{
		yam2d::vec2 tilesSize(100.0f, 50.0f);
		tileObjects.push_back(createSpriteGameObject("Textures/tile.png", 100.0f, 50.0f));
		objects->addGameObject(tileObjects.back());
		PhysicsBody* tileBody = new PhysicsBody(tileObjects.back(), boxWorld, 1.0f, 1.0f);
		tileBody->setBoxFixture(tilesSize / tileSize, yam2d::vec2(0.0f, 0.0f), tileObjects.back()->getRotation(), true);
		tileObjects.back()->addComponent(tileBody);
		tileObjects.back()->setName("Tile");
		tileObjects.back()->getComponent<PhysicsBody>()->getBody()->SetTransform(yam2d::vec2(-3.0f + 2 * i, -2.0f), 0.0f);
	}

	textObject = createTextObject();
	textObject->setPosition(8.0f, -5.0f);

	background->addGameObject(backgroundObject);
	objects->addGameObject(playerObject);
	objects->addGameObject(ballObject);
	objects->addGameObject(textObject);
}
GameState::~GameState()
{
	delete map;
	delete contactListener;
}


bool GameState::update(yam2d::ESContext* _context, float _deltaTime)
{
	boxWorld->Step(_deltaTime, 10, 10);
	map->update(_deltaTime);

	static bool ballHit;
	ballHit = false;
	//Collisions
	unsigned int numContacts = contactListener->contacts.size();
	for (unsigned int i = 0; i < numContacts; i++)
	{
		const Contact& contact = contactListener->contacts[i];
		yam2d::GameObject* A = ((PhysicsBody*) contact.fixtureA->GetBody()->GetUserData())->getGameObject();
		yam2d::GameObject* B = ((PhysicsBody*) contact.fixtureB->GetBody()->GetUserData())->getGameObject();
		if ((A->getName() == "Player" && B->getName() == "Ball") || (B->getName() == "Player" && A->getName() == "Ball"))
		{
			if (!ballHit)
			{
				ballVelocity.y = -ballVelocity.y;
				ballObject->getComponent<PhysicsBody>()->getBody()->SetTransform(ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition() - (ballVelocity / 2.0f), 0.0f);
				ballVelocity.x -= (playerObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x - ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x) / 20.0f;
			}
			ballHit = true;
		}
		if ((A->getName() == "Ball" && B->getName() == "Tile") || (B->getName() == "Ball" && A->getName() == "Tile"))
		{
			if (!ballHit)
				ballVelocity.y = -ballVelocity.y;
			ballHit = true;
			if (B->getName() == "Tile")
			{
				map->deleteGameObject(B);
				tileAmount--;
			}
			else if (A->getName() == "Tile")
			{
				map->deleteGameObject(A);
				tileAmount--;
			}
		}
	}
	//Restrict ball
	if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x > ((float)_context->width/2.0f) / tileSize.x
		|| ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().x < -((float) _context->width / 2.0f) / tileSize.x)
	{
		ballVelocity.x = -ballVelocity.x;
	}
	if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().y < -((float) _context->height / 2.0f) / tileSize.y)
	{
		ballVelocity.y = -ballVelocity.y;
	}
	//Win-Lose
	if (tileAmount == 0)
	{
		//Win
		textObject->getComponent<yam2d::TextComponent>()->getText()->setText("YOU WIN!");
		textObject->setPosition(0.0f, 0.0f);
		endTimer -= _deltaTime;
	}
	else if (ballObject->getComponent<PhysicsBody>()->getBody()->GetPosition().y > ((float) _context->height / 2.0f) / tileSize.y)
	{
		//Lose
		textObject->getComponent<yam2d::TextComponent>()->getText()->setText("YOU LOSE!");
		textObject->setPosition(0.0f, 0.0f);
		endTimer -= _deltaTime;
	}
	if (endTimer <= 0.0f)
	{
		stateManager->setState(new MainMenuState(stateManager));
		return true;
	}
	
	//Input
	if (yam2d::getKeyState(yam2d::KEY_BACK))
	{
		stateManager->setState(new MainMenuState(stateManager));
		return true;
	}
	if (yam2d::getKeyState(yam2d::KEY_D))
	{
		playerObject->getComponent<PhysicsBody>()->getBody()->SetTransform(playerObject->getPosition() + yam2d::vec2(0.1f, 0.0f), 0.0f);
	}
	if (yam2d::getKeyState(yam2d::KEY_A))
	{
		playerObject->getComponent<PhysicsBody>()->getBody()->SetTransform(playerObject->getPosition() + yam2d::vec2(-0.1f, 0.0f), 0.0f);
	}

	//
	ballObject->getComponent<PhysicsBody>()->getBody()->SetTransform(ballObject->getPosition() + ballVelocity, 0.0f);
	if (endTimer >= 3.0f)
	{
		textObject->getComponent<yam2d::TextComponent>()->getText()->setText("Tiles Left: " + std::to_string(tileAmount));
	}

	return true;
}


void GameState::draw(yam2d::ESContext* _context)
{
	map->getCamera()->setScreenSize(_context->width, _context->height, 720, 1280.0f / 720.0f);
	map->render();
}