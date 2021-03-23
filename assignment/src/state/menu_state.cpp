//@BridgetACasey

#include "menu_state.h"

MenuState::MenuState(gef::Platform& platform) : State(platform)
{
	playButton = Button::create(gameInput);
	settingsButton = Button::create(gameInput);
	helpButton = Button::create(gameInput);
	exitButton = Button::create(gameInput);
}

MenuState* MenuState::create(gef::Platform& platform)
{
	return new MenuState(platform);
}

void MenuState::init()
{

}

void MenuState::handleInput()
{

}

void MenuState::update(float deltaTime)
{

}

void MenuState::render()
{

}

void MenuState::onEnter()
{
	gef::DebugOut("Entering the main menu\n");
}

void MenuState::onExit()
{

}