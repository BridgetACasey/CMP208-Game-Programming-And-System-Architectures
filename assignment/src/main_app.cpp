#include "main_app.h"

MainApp::MainApp(gef::Platform& platform) : Application(platform)
{
	context = new Context(platform);
}

void MainApp::Init()
{
	context->setActiveState(StateLabel::LEVEL);

	context->getActiveState()->init();
}

void MainApp::CleanUp()
{
	delete context;
	context = NULL;
}

bool MainApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	context->getActiveState()->handleInput();
	context->getActiveState()->update(frame_time);

	return true;
}

void MainApp::Render()
{
	context->getActiveState()->render();
}