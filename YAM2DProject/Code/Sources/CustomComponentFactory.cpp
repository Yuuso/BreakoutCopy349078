#include "CustomComponentFactory.h"
#include "PlayerController.h"


CustomComponentFactory::CustomComponentFactory() :DefaultComponentFactory(), m_map(0)
{
	m_world = new b2World(vec2(0, 0.0f));
	m_world->SetAllowSleeping(false);
	//m_contactListener = new ContactListener();
	//m_world->SetContactListener(m_contactListener);
}
CustomComponentFactory::~CustomComponentFactory()
{
}

void CustomComponentFactory::setCurrentMap(Map* map)
{
	m_map = map;
}
b2World* CustomComponentFactory::getPhysicsWorld()
{
	return m_world;
}
//ContactListener* CustomComponentFactory::getContactListener()
//{
//	return m_contactListener;
//}

Component* CustomComponentFactory::createNewComponent(const std::string& type, Entity* owner, const yam2d::PropertySet& properties)
{
	// TODO: Implementation... Use now default implementation instead.
	return DefaultComponentFactory::createNewComponent(type, owner, properties);
}


Entity* CustomComponentFactory::createNewEntity(ComponentFactory* componentFactory, const std::string& type, Entity* parent, const yam2d::PropertySet& properties)
{
	float linearDamping = 0.5f;
	float angularDamping = 0.5f;
	if ("Player" == type)
	{
		GameObject* gameObject = new GameObject(parent, properties);
		PhysicsBody* body = new PhysicsBody(gameObject, m_world, linearDamping, angularDamping);
		PlayerController* playerController = new PlayerController(gameObject);

		body->setBoxFixture(gameObject->getSizeInTiles() * 0.8f/*?*/, yam2d::vec2(0, 0), gameObject->getRotation(), true);

		gameObject->addComponent(body);
		gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
		gameObject->addComponent(playerController);
		gameObject->setName("Player");
		return gameObject;
	}
	else if ("Ball" == type)
	{
		GameObject* gameObject = new GameObject(parent, properties);
		PhysicsBody* body = new PhysicsBody(gameObject, m_world, linearDamping, angularDamping);

		body->setCircleFixture(gameObject->getSizeInTiles().x * 0.8f/*?*/, true);

		gameObject->addComponent(body);
		gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
		gameObject->setName("Ball");

		return gameObject;
	}
	else if ("Tile" == type)
	{
		GameObject* gameObject = new GameObject(parent, properties);
		PhysicsBody* body = new PhysicsBody(gameObject, m_world, linearDamping, angularDamping);
		vec2 center = yam2d::vec2(0, 0);
		body->setBoxFixture(gameObject->getSizeInTiles() * 0.8f/*?*/, center, gameObject->getRotation(), true);

		gameObject->addComponent(body);
		gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
		gameObject->setName("Tile");

		return gameObject;
	}
	else if ("Background" == type)
	{
		GameObject* gameObject = new GameObject(parent, properties);

		gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
		gameObject->setName("Background");

		return gameObject;
	}
	// Default functionality.
	Entity* res = DefaultComponentFactory::createNewEntity(componentFactory, type, parent, properties);
	assert(res != 0);
	return res;
}