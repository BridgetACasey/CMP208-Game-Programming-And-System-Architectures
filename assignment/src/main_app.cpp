#include "main_app.h"

MainApp::MainApp(gef::Platform& platform) : Application(platform)
{
	context = new Context(platform);
}

void MainApp::Init()
{
	context->setActiveState(StateLabel::SPLASH_SCREEN);
}

void MainApp::CleanUp()
{
	delete context;
	context = NULL;
}

bool MainApp::Update(float frame_time)
{
	context->getActiveState()->handleInput();

	return context->getActiveState()->update(frame_time);
}

void MainApp::Render()
{
	context->getActiveState()->render();
}