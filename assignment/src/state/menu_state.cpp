//@BridgetACasey

#include "menu_state.h"
#include "context.h"

MenuState::MenuState(gef::Platform& platform) : State(platform)
{
	buttonIndex = 0;

	scrollSpeed = 25.0f;

	buttons[0] = nullptr;	//Play/Continue button
	buttons[1] = nullptr;	//Settings button
	buttons[2] = nullptr;	//Help/Controls button
	buttons[3] = nullptr;	//Quit button
	
	play = true;
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

		title.set_width(256.0f);
		title.set_height(128.0f);
		title.set_position(gef::Vector4(platform.width() / 2.0f, (platform.height() / 2.0f) - 175.0f, 0.0f));
		title.set_texture(context->getTextureManager()->getTexture(TextureID::GAME_TITLE));

		background.set_height(platform.height());
		background.set_width(platform.width());
		background.set_position(platform.width() / 2.0f, platform.height() / 2.0f, 0.0f);
		background.set_texture(context->getTextureManager()->getTexture(TextureID::MENU_BACKGROUND));

		backgroundCopy = background;
		backgroundCopy.set_position(backgroundCopy.width() / 2.0f + platform.width(), platform.height() / 2.0f, 0.0f);

		buttons[0] = Button::create(context->getGameInput());
		buttons[1] = Button::create(context->getGameInput());
		buttons[2] = Button::create(context->getGameInput());
		buttons[3] = Button::create(context->getGameInput());

		buttons[0]->set_width(150.0f);
		buttons[0]->set_height(75.0f);
		buttons[0]->set_position(gef::Vector4(platform.width() / 2.0f, (platform.height() / 2.0f) - 50.0f, 0.0f));

		buttons[1]->set_width(150.0f);
		buttons[1]->set_height(75.0f);
		buttons[1]->set_position(gef::Vector4(buttons[0]->position().x(), buttons[0]->position().y() + 75.0f, 0.0f));
		buttons[1]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::SETTINGS_BUTTON));
		buttons[1]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::SETTINGS_BUTTON_COL));

		buttons[2]->set_width(150.0f);
		buttons[2]->set_height(75.0f);
		buttons[2]->set_position(gef::Vector4(buttons[1]->position().x(), buttons[1]->position().y() + 75.0f, 0.0f));
		buttons[2]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::HELP_BUTTON));
		buttons[2]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::HELP_BUTTON_COL));

		buttons[3]->set_width(150.0f);
		buttons[3]->set_height(75.0f);
		buttons[3]->set_position(gef::Vector4(buttons[2]->position().x(), buttons[2]->position().y() + 75.0f, 0.0f));
		buttons[3]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::QUIT_BUTTON));
		buttons[3]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::QUIT_BUTTON_COL));
	}

	firstSetup = false;
}

void MenuState::onEnter()
{
	gef::DebugOut("Entering the main menu\n");

	setup();

	//Checks if the player has entered the level but not yet completed it, and changes the 'play' texture to 'continue' instead
	if (context->getGamePlaying())
	{
		buttons[0]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::CONTINUE_BUTTON));
		buttons[0]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::CONTINUE_BUTTON_COL));
	}

	else
	{
		buttons[0]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::PLAY_BUTTON));
		buttons[0]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::PLAY_BUTTON_COL));
	}

	//This is called after the level has been completed, in order to restart the main menu music
	if (!context->getGamePlaying() && !context->getGameAudio()->isMusicPlaying(MusicID::MENU))
	{
		context->getGameAudio()->playMusic(MusicID::MENU);
	}
}

void MenuState::onExit()
{
	buttons[0]->setSelectedByController(false);
	buttons[1]->setSelectedByController(false);
	buttons[2]->setSelectedByController(false);
	buttons[3]->setSelectedByController(false);
}

void MenuState::handleInput()
{
	context->getGameInput()->update();

	if (context->getGameInput()->getController()->active)
	{
		checkForController();
		checkButtonStatus(false);
	}

	else
	{
		checkButtonStatus(true);
	}
}

bool MenuState::update(float deltaTime)
{
	fps = 1.0f / deltaTime;

	updateBackground(deltaTime);

	return play;
}

void MenuState::render()
{
	context->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context->getRenderer3D()->End();

	context->getSpriteRenderer()->Begin(false);

	//Render UI elements
	context->getSpriteRenderer()->DrawSprite(background);
	context->getSpriteRenderer()->DrawSprite(backgroundCopy);

	context->getSpriteRenderer()->DrawSprite(title);

	context->getSpriteRenderer()->DrawSprite(*buttons[0]);
	context->getSpriteRenderer()->DrawSprite(*buttons[1]);
	context->getSpriteRenderer()->DrawSprite(*buttons[2]);
	context->getSpriteRenderer()->DrawSprite(*buttons[3]);

	if (context->getFont())
	{
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "FPS: %.1f", fps);
	}

	context->getSpriteRenderer()->End();
}

void MenuState::checkForController()
{
	if (context->getGameInput()->getController()->leftStick == ControllerCode::UP ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_UP)
	{
		buttons[buttonIndex]->setSelectedByController(false);

		if (buttonIndex <= 0)
		{
			buttonIndex = 3;
		}

		else
		{
			--buttonIndex;
		}
	}

	else if (context->getGameInput()->getController()->leftStick == ControllerCode::DOWN ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_DOWN)
	{
		buttons[buttonIndex]->setSelectedByController(false);

		if (buttonIndex >= 3)
		{
			buttonIndex = 0;
		}

		else
		{
			++buttonIndex;
		}
	}

	buttons[buttonIndex]->setSelectedByController(true);
}

void MenuState::checkButtonStatus(bool usingMouse)
{
	if (buttons[0]->isClicked(usingMouse))
	{
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context->setActiveState(StateLabel::LEVEL);
	}

	if (buttons[1]->isClicked(usingMouse))
	{
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context->setActiveState(StateLabel::SETTINGS);
	}

	if (buttons[2]->isClicked(usingMouse))
	{
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context->setActiveState(StateLabel::HELP);
	}

	if (buttons[3]->isClicked(usingMouse))
	{
		play = false;
	}
}

void MenuState::updateBackground(float deltaTime)
{
	background.set_position(background.position().x() - scrollSpeed * deltaTime, background.position().y(), background.position().z());
	backgroundCopy.set_position(backgroundCopy.position().x() - scrollSpeed * deltaTime, backgroundCopy.position().y(), backgroundCopy.position().z());

	if (background.position().x() < -(background.width() / 2.0f))
	{
		background.set_position(platform.width() / 2.0f, platform.height() / 2.0f, 0.0f);
	}

	if (backgroundCopy.position().x() < backgroundCopy.width() / 2.0f)
	{
		backgroundCopy.set_position(backgroundCopy.width() / 2.0f + platform.width(), platform.height() / 2.0f, 0.0f);
	}
}