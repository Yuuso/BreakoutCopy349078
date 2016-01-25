#include <es_util.h>
#include "StateManager.h"


StateManager* stateManager;

// Initialization
bool init(yam2d::ESContext* _esContext)
{
	stateManager = new StateManager();
	return true;
}


// Deinitialization
void deinit(yam2d::ESContext* _esContext)
{
}


// DRAW
void draw(yam2d::ESContext* _esContext)
{
	glViewport(0, 0, _esContext->width, _esContext->height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	stateManager->draw(_esContext);
}


// UPDATE
void update(yam2d::ESContext* _esContext, float _deltaTime)
{
	if (!stateManager->update(_esContext, _deltaTime))
	{
		yam2d::esQuitApp(_esContext);
		delete stateManager;
	}
}



//MAIN
int main(int argc, char** argv)
{
	yam2d::ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Hello Triangle", 1280, 720, yam2d::ES_WINDOW_DEFAULT);


	esRegisterInitFunc(&esContext, init);
	esRegisterDrawFunc(&esContext, draw);
	esRegisterUpdateFunc(&esContext, update);
	esRegisterDeinitFunc(&esContext, deinit);

	esMainLoop(&esContext);
	return 0;
}
