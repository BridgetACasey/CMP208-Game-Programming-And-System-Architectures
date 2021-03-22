#include "context.h"

Context::Context(gef::Platform& platform)
{
	LevelState* level = LevelState::create(platform);

	states[StateLabel::LEVEL] = level;

	activeState = states.at(StateLabel::LEVEL);
}

Context::~Context()
{
	delete states[StateLabel::LEVEL];
}

void Context::setActiveState(StateLabel stateName)
{
	activeState->onExit();

	activeState = states[stateName];

	activeState->onEnter();

	activeState->setContext(this);
}

State* Context::getActiveState()
{
	return activeState;
}