#pragma once

#include <GameObject.h>
#include <Box2D\Box2D.h>

class PhysicsBody : public yam2d::Component, public yam2d::Updatable
{
public:
	PhysicsBody(yam2d::GameObject* parent, b2World* world, float linearDamping, float angularDamping); //Dynamic
	PhysicsBody(yam2d::GameObject* parent, b2World* world); //Static

	virtual ~PhysicsBody(void);

	void setBoxFixture(const yam2d::vec2& size, const yam2d::vec2& center, float angle, bool isSensor, float density = 1.0f, float restitution = 1.0f, float friction = 0.9f);
	void setCircleFixture(float radius, bool isSensor, float density = 1.0f, float restitution = 1.0f, float friction = 0.9f);

	b2Body* getBody() { return m_body; }

	virtual void update(float deltaTime);

	yam2d::GameObject* getGameObject() { return (yam2d::GameObject*)getOwner(); }
	const yam2d::GameObject* getGameObject() const { return (const yam2d::GameObject*)getOwner(); }

private:
	yam2d::Ref<b2World> m_world;
	b2Body* m_body;
};