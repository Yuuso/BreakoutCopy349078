#include "ContactListener.h"

ContactListener::ContactListener() : contacts()
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	//We need to copy out the data because the b2Contact passed in
	//is reused.
	b2Manifold* manifold = contact->GetManifold();
	manifold->localPoint;
	Contact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	contacts.push_back(myContact);
}

void ContactListener::EndContact(b2Contact* contact)
{
	Contact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	std::vector<Contact>::iterator pos;
	pos = std::find(contacts.begin(), contacts.end(), myContact);
	if (pos != contacts.end()) {
		contacts.erase(pos);
	}
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}