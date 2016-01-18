// Include OpenGL ES Engine utils
#include <es_util.h>


// Initialization
bool init(yam2d::ESContext *esContext)
{

	return true;
}


// Deinitialization
void deinit(yam2d::ESContext *esContext)
{

}


// DRAW
void draw(yam2d::ESContext *esContext)
{
	glViewport(0, 0, esContext->width, esContext->height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


// UPDATE
void update(yam2d::ESContext*, float deltaTime)
{

}



//MAIN
int main(int argc, char *argv [])
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
