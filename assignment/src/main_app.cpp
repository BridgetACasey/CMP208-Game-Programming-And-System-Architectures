//@BridgetACasey

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

bool MainApp::Update(float deltaTime)
{
	context->getActiveState()->handleInput();

	return context->getActiveState()->update(deltaTime);
}

void MainApp::Render()
{
	context->getActiveState()->render();
}