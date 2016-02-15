#include "PlayerController.h"
#include "Input.h"
#include "PhysicsBody.h"


PlayerController::PlayerController(yam2d::GameObject* _parent) : yam2d::Component(_parent, yam2d::Component::getDefaultProperties())
{
}
PlayerController::~PlayerController()
{
}

void PlayerController::update(float _deltaTime)
{
	if (!getGameObject()->getComponent<PhysicsBody>())
		return;

	float direction = (float) yam2d::getKeyState(yam2d::KEY_A) - yam2d::getKeyState(yam2d::KEY_D);
	if (direction)
	{
		getGameObject()->getComponent<PhysicsBody>()->getBody()->ApplyForceToCenter(yam2d::vec2(10.0f, 0.0f) * -direction);
	}
}

yam2d::GameObject* PlayerController::getGameObject()
{
	return (yam2d::GameObject*)getOwner();
}
const yam2d::GameObject* PlayerController::getGameObject() const
{
	return (const yam2d::GameObject*)getOwner();
}