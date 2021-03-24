//@BridgetACasey

#include "pause_state.h"
#include "context.h"

PauseState::PauseState(gef::Platform& platform) : State(platform)
{

}

PauseState* PauseState::create(gef::Platform& platform)
{
	return new PauseState(platform);
}

void PauseState::setup()
{

}

void PauseState::onEnter()
{

}

void PauseState::onExit()
{

}

void PauseState::handleInput()
{

}

void PauseState::update(float deltaTime)
{

}

void PauseState::render()
{

}