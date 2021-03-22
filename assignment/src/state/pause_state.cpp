//@BridgetACasey

#include "pause_state.h"

PauseState::PauseState(gef::Platform& platform) : State(platform)
{

}

PauseState* PauseState::create(gef::Platform& platform)
{
	return new PauseState(platform);
}

void PauseState::init()
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

void PauseState::onEnter()
{

}

void PauseState::onExit()
{

}