#include "splash_state.h"
#include "context.h"

SplashState::SplashState(gef::Platform& platform) : State(platform)
{

}

SplashState* SplashState::create(gef::Platform& platform)
{
	return new SplashState(platform);
}

void SplashState::setup()
{
	if (firstSetup)
	{
		gef::DebugOut("Splash Screen: Performing first time setup!\n");
	}

	firstSetup = false;
}

void SplashState::onEnter()
{
	gef::DebugOut("Entering splash screen\n");

	setup();
}

void SplashState::onExit()
{

}

void SplashState::handleInput()
{

}

void SplashState::update(float deltaTime)
{
	if (transitionTime > 3.0f)
	{
		transitionTime = 0.0f;
		context_->setActiveState(StateLabel::MAIN_MENU);
	}

	transitionTime += 1.0f * deltaTime;
}

void SplashState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	//Render UI elements

	context_->getSpriteRenderer()->End();
}