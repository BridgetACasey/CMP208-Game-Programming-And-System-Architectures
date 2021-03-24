//@BridgetACasey

#include "menu_state.h"
#include "context.h"

MenuState::MenuState(gef::Platform& platform) : State(platform)
{

}

MenuState* MenuState::create(gef::Platform& platform)
{
	return new MenuState(platform);
}

void MenuState::setup()
{
	if (firstSetup)
	{
		gef::DebugOut("Main Menu: Performing first time setup!\n");

		playButton = Button::create(context_->getGameInput());
		settingsButton = Button::create(context_->getGameInput());
		helpButton = Button::create(context_->getGameInput());
		exitButton = Button::create(context_->getGameInput());

		playButton->set_width(150.0f);
		playButton->set_height(75.0f);
		playButton->setInactiveColour(0xfffffff);
		playButton->setHoveringColour(0xffffffff);
		playButton->setClickedColour(0xffffffff);
		playButton->set_position(gef::Vector4(platform_.width() / 2.0f, (platform_.height() / 2.0f) - 50.0f, 0.0f));

		settingsButton->set_width(150.0f);
		settingsButton->set_height(75.0f);
		settingsButton->setInactiveColour(0xfffffff);
		settingsButton->setHoveringColour(0xffffffff);
		settingsButton->setClickedColour(0xffffffff);
		settingsButton->set_position(gef::Vector4(playButton->position().x(), playButton->position().y() + 75.0f, 0.0f));

		helpButton->set_width(150.0f);
		helpButton->set_height(75.0f);
		helpButton->setInactiveColour(0xfffffff);
		helpButton->setHoveringColour(0xffffffff);
		helpButton->setClickedColour(0xffffffff);
		helpButton->set_position(gef::Vector4(settingsButton->position().x(), settingsButton->position().y() + 75.0f, 0.0f));

		exitButton->set_width(150.0f);
		exitButton->set_height(75.0f);
		exitButton->setInactiveColour(0xfffffff);
		exitButton->setHoveringColour(0xffffffff);
		exitButton->setClickedColour(0xffffffff);
		exitButton->set_position(gef::Vector4(helpButton->position().x(), helpButton->position().y() + 75.0f, 0.0f));
	}

	firstSetup = false;
}

void MenuState::onEnter()
{
	gef::DebugOut("Entering the main menu\n");

	setup();
}

void MenuState::onExit()
{

}

void MenuState::handleInput()
{

}

void MenuState::update(float deltaTime)
{
	context_->getGameInput()->update(NULL);

	if (playButton->isHovering())
	{
		gef::DebugOut("Hovering over PLAY\n");
	}

	if (settingsButton->isHovering())
	{
		gef::DebugOut("Hovering over SETTINGS\n");
	}

	if (helpButton->isHovering())
	{
		gef::DebugOut("Hovering over HELP\n");
	}

	if (exitButton->isHovering())
	{
		gef::DebugOut("Hovering over EXIT\n");
	}
}

void MenuState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	//Render UI elements
	context_->getSpriteRenderer()->DrawSprite(*playButton);
	context_->getSpriteRenderer()->DrawSprite(*settingsButton);
	context_->getSpriteRenderer()->DrawSprite(*helpButton);
	context_->getSpriteRenderer()->DrawSprite(*exitButton);

	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(500.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "X: %.1f Y: %.1f",
			context_->getGameInput()->getMousePosition().x, context_->getGameInput()->getMousePosition().y);
	}

	context_->getSpriteRenderer()->End();
}