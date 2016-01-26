#pragma once

#include <Box2d/Box2D.h>
#include <vector>
#include <algorithm>
#include <vec2.h>
#include <Object.h>

struct Contact
{
	b2Fixture *fixtureA;
	b2Fixture *fixtureB;

	bool operator==(const Contact& other) const
	{
		return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
	}
};

class ContactListener : public b2ContactListener, public yam2d::Object
{
public:
	std::vector<Contact> contacts;

	ContactListener();
	~ContactListener();

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};