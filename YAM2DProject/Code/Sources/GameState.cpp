#include "GameState.h"
#include "CreateGameObject.h"
#include "MainMenuState.h"
#include "PhysicsBody.h"

#include <Camera.h>
#include <Input.h>

#define TILEAMOUNT 0


GameState::GameState(StateManager* _stateManager) : State(_stateManager), tileSize(64.0f, 64.0f), playerPosition(0.0f, 4.0f), ballPosition(0.0f, 0.0f), ballVelocity(0.0f, 0.2f)
{
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
	
	playerObject = createSpriteGameObject("Textures/player.png", 220.0f, 50.0f);
	playerObject->setPosition(playerPosition);
	PhysicsBody* Playerbody = new PhysicsBody(playerObject, boxWorld, 1.0f, 1.0f);
	Playerbody->setBoxFixture(playerObject->getSizeInTiles()*0.95f, playerObject->getPosition(), playerObject->getRotation(), false);
	playerObject->addComponent(Playerbody);
	playerObject->setName("Player");

	ballObject = createSpriteGameObject("Textures/ball.png", 50.0f, 50.f);
	ballObject->setPosition(ballPosition);
	PhysicsBody* ballBody = new PhysicsBody(ballObject, boxWorld, 1.0f, 1.0f);
	Playerbody->setBoxFixture(playerObject->getSizeInTiles()*0.95f, playerObject->getPosition(), playerObject->getRotation(), false);
	ballObject->addComponent(ballBody);
	ballObject->setName("Ball");

	for (int i = 0; i < TILEAMOUNT; i++)
	{
		tileObjects.push_back(createSpriteGameObject("Textures/tile.png", 100.0f, 50.0f));
		objects->addGameObject(tileObjects.back());
		tileObjects.back()->setPosition(-3.0f + 2*i, -4.0f);
		PhysicsBody* tileBody = new PhysicsBody(tileObjects.back(), boxWorld, 1.0f, 1.0f);
		tileBody->setBoxFixture(tileObjects.back()->getSizeInTiles()*0.95f, tileObjects.back()->getPosition(), tileObjects.back()->getRotation(), true);
		tileObjects.back()->addComponent(tileBody);
		tileObjects.back()->setName("Tile");
	}

	background->addGameObject(backgroundObject);
	objects->addGameObject(playerObject);
	objects->addGameObject(ballObject);
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

	unsigned int numContacts = contactListener->contacts.size();
	for (unsigned int i = 0; i < numContacts; i++)
	{
		const Contact& contact = contactListener->contacts[i];
		yam2d::GameObject* A = ((PhysicsBody*) contact.fixtureA->GetBody()->GetUserData())->getGameObject();
		yam2d::GameObject* B = ((PhysicsBody*) contact.fixtureB->GetBody()->GetUserData())->getGameObject();
		if ((A->getName() == "Player" && B->getName() == "Ball") || (B->getName() == "Player" && A->getName() == "Ball"))
		{
			ballVelocity.y = -ballVelocity.y;
		}
	}
	
	if (yam2d::getKeyState(yam2d::KEY_ESCAPE))
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
	ballObject->getComponent<PhysicsBody>()->getBody()->SetTransform(ballObject->getPosition() + ballVelocity, 0.0f);

	return true;
}


void GameState::draw(yam2d::ESContext* _context)
{
	map->getCamera()->setScreenSize(_context->width, _context->height, 720, 1280.0f / 720.0f);
	map->render();
}