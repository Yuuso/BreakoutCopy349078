#include "SplashScreenState.h"
#include "MainMenuState.h"


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
	static const float startTime = _deltaTime;
	splashTime += _deltaTime;
	if (splashTime >= (startTime + 1.3f))
		stateManager->setState(new MainMenuState(stateManager));

	return true;
}


void SplashScreenState::draw(yam2d::ESContext* _context)
{
	batch->render();
}