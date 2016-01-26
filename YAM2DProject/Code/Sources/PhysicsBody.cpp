#include "PhysicsBody.h"

#include "Input.h"
#include "es_util.h"

namespace
{
	b2Body* createDynamicBody(b2World* world, const yam2d::vec2& initialPosition, float initialRotation, void* userData, float linearDamping = 2.0f, float angularDamping = 8.0f)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(initialPosition.x, initialPosition.y);
		bodyDef.angle = initialRotation;
		bodyDef.userData = userData;
		bodyDef.bullet = true;
		bodyDef.linearDamping = linearDamping;
		bodyDef.angularDamping = angularDamping;
		bodyDef.allowSleep = false;
		bodyDef.awake = true;
		bodyDef.fixedRotation = false;
		return world->CreateBody(&bodyDef);
	}

	b2Body* createStaticBody(b2World* world, const yam2d::vec2& initialPosition, float initialRotation, void* userData)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(initialPosition.x, initialPosition.y);
		bodyDef.angle = initialRotation;
		bodyDef.userData = userData;
		bodyDef.bullet = false;
		bodyDef.allowSleep = true;
		bodyDef.awake = false;
		bodyDef.fixedRotation = true;
		return world->CreateBody(&bodyDef);
	}
}


PhysicsBody::PhysicsBody(yam2d::GameObject* parent, b2World* world, float linearDamping, float angularDamping)
	: Component(parent, Component::getDefaultProperties())
	, m_world(world)
	, m_body(0)
{
	m_body = createDynamicBody(m_world, parent->getPosition(), parent->getRotation(), this, linearDamping, angularDamping);
	m_body->SetTransform(parent->getPosition(), parent->getRotation());
}

PhysicsBody::PhysicsBody(yam2d::GameObject* parent, b2World* world)
	: Component(parent, Component::getDefaultProperties())
	, m_world(world)
	, m_body(0)
{
	m_body = createStaticBody(m_world, parent->getPosition(), parent->getRotation(), this);
}

PhysicsBody::~PhysicsBody(void)
{
	m_world->DestroyBody(m_body);
}

void PhysicsBody::setBoxFixture(const yam2d::vec2& size, const yam2d::vec2& center, float angle, bool isSensor, float density, float restitution, float friction)
{
	b2PolygonShape shape;
	shape.SetAsBox(size.x / 2, size.y / 2, center, angle);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = isSensor;
	fixtureDef.density = density;
	fixtureDef.restitution = restitution;
	fixtureDef.friction = friction;
	m_body->CreateFixture(&fixtureDef);
}

void PhysicsBody::setCircleFixture(float radius, bool isSensor, float density, float restitution, float friction)
{
	b2CircleShape shape;
	shape.m_radius = radius;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = isSensor;
	fixtureDef.density = density;
	fixtureDef.restitution = restitution;
	fixtureDef.friction = friction;
	m_body->CreateFixture(&fixtureDef);
}


void PhysicsBody::update(float deltaTime)
{
	if (m_body->GetType() == b2BodyType::b2_dynamicBody)
	{
		// Set position from body to gameObject
		b2Transform tr = m_body->GetTransform();
		yam2d::vec2 newPosition = yam2d::vec2(tr.p.x, tr.p.y);
		float newRotation = -tr.q.GetAngle();
		getGameObject()->setPosition(newPosition);
		getGameObject()->setRotation(newRotation);
	}
}