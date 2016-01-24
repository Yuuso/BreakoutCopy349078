#pragma once

#include "State.h"

#include <SpriteBatch.h>
#include <Texture.h>
#include <Sprite.h>


class SplashScreenState : public State
{
public:
	SplashScreenState(StateManager* _stateManager);
	~SplashScreenState();

	bool update(yam2d::ESContext* _context, float _deltaTime);
	void draw(yam2d::ESContext* _context);

private:
	yam2d::SpriteBatchGroup* batch;
	yam2d::Sprite* sprite;
	yam2d::Texture* texture;

	float splashTime;
};