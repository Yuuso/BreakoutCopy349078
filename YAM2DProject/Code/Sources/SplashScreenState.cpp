#include "SplashScreenState.h"
#include "MainMenuState.h"
#include "Input.h"


SplashScreenState::SplashScreenState(StateManager* _stateManager) : State(_stateManager), splashTime(0.0f)
{
	batch = new yam2d::SpriteBatchGroup();
	texture = new yam2d::Texture("Textures/splash_screen.png");
	sprite = new yam2d::Sprite(0);

	batch->addSprite(texture, sprite, yam2d::vec2(0.0f, 0.0f), 0.0f, yam2d::vec2(2.0f, 2.0f));
}
SplashScreenState::~SplashScreenState()
{
	delete batch;
	delete sprite;
}


bool SplashScreenState::update(yam2d::ESContext* _context, float _deltaTime)
{
	static const float startTime = 0.0f;
	splashTime += _deltaTime;
	if (splashTime >= 1.2f)
	{
		stateManager->setState(new MainMenuState(stateManager));
		return true;
	}
	else if (GetKeyState(yam2d::KEY_RETURN))
	{
		stateManager->setState(new MainMenuState(stateManager));
		return true;
	}
	
	return true;
}


void SplashScreenState::draw(yam2d::ESContext* _context)
{
	batch->render();
}