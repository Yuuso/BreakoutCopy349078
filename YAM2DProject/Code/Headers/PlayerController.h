#pragma once

#include <SpriteComponent.h>
#include <GameObject.h>

class PlayerController : public yam2d::Component, public yam2d::Updatable
{
public: 
	PlayerController(yam2d::GameObject* _parent);
	virtual ~PlayerController();

	virtual void update(float _deltaTime);

	yam2d::GameObject* getGameObject();
	const yam2d::GameObject* getGameObject() const;
};