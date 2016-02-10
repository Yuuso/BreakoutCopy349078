#pragma once

#include "Map.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "Box2D\Box2D.h"
#include "ContactListener.h"
#include "PhysicsBody.h"

using namespace yam2d;

class CustomComponentFactory : public yam2d::DefaultComponentFactory
{
public:
	CustomComponentFactory();
	virtual ~CustomComponentFactory();

	void setCurrentMap(Map* map);

	b2World* getPhysicsWorld();
	ContactListener* getContactListener();

	virtual Component* createNewComponent(const std::string& type, Entity* owner, const yam2d::PropertySet& properties);
	virtual Entity* createNewEntity(ComponentFactory* componentFactory, const std::string& type, Entity* parent, const yam2d::PropertySet& properties);

private:
	Map* m_map; // HACK. Player to set for each enemy

	yam2d::Ref<b2World> m_world;
	yam2d::Ref<ContactListener> m_contactListener;
};