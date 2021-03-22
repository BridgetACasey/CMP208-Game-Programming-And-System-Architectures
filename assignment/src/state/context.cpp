#include "context.h"

Context::Context(gef::Platform& platform)
{
	LevelState* level = LevelState::create(platform);
	MenuState* mainMenu = MenuState::create(platform);
	PauseState* pauseMenu = PauseState::create(platform);
	SplashState* splashScreen = SplashState::create(platform);

	states[StateLabel::LEVEL] = level;
	states[StateLabel::MAIN_MENU] = mainMenu;
	states[StateLabel::PAUSE_MENU] = pauseMenu;
	states[StateLabel::SPLASH_SCREEN] = splashScreen;

	activeState = states.at(StateLabel::LEVEL);
}

Context::~Context()
{
	delete states[StateLabel::LEVEL];
	delete states[StateLabel::MAIN_MENU];
	delete states[StateLabel::PAUSE_MENU];
	delete states[StateLabel::SPLASH_SCREEN];
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