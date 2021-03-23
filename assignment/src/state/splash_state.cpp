#include "splash_state.h"

SplashState::SplashState(gef::Platform& platform) : State(platform)
{

}

SplashState* SplashState::create(gef::Platform& platform)
{
	return new SplashState(platform);
}

void SplashState::init()
{

}

void SplashState::handleInput()
{

}

void SplashState::update(float deltaTime)
{

}

void SplashState::render()
{

}

void SplashState::onEnter()
{
	gef::DebugOut("Entering splash screen\n");
}

void SplashState::onExit()
{

}