//@BridgetACasey

#include "pause_state.h"
#include "context.h"

PauseState::PauseState(gef::Platform& platform) : State(platform)
{
	buttonIndex = 0;

	buttons[0] = nullptr;	//Resume button
	buttons[1] = nullptr;	//Menu button, to return to the main menu
}

PauseState* PauseState::create(gef::Platform& platform)
{
	return new PauseState(platform);
}

void PauseState::setup()
{
	if (firstSetup)
	{
		background.set_height(platform.height());
		background.set_width(platform.width());
		background.set_position(platform.width() / 2.0f, platform.height() / 2.0f, 0.0f);
		background.set_texture(context->getTextureManager()->getTexture(TextureID::MENU_BACKGROUND_ALT));

		buttons[0] = Button::create(context->getGameInput());
		buttons[1] = Button::create(context->getGameInput());

		buttons[0]->set_width(150.0f);
		buttons[0]->set_height(75.0f);
		buttons[0]->set_position(gef::Vector4(platform.width() / 2.0f, platform.height() / 2.0f, 0.0f));
		buttons[0]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::RESUME_BUTTON));
		buttons[0]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::RESUME_BUTTON_COL));

		buttons[1]->set_width(150.0f);
		buttons[1]->set_height(75.0f);
		buttons[1]->set_position(platform.width() / 2.0f, buttons[0]->position().y() + 75.0f, 0.0f);
		buttons[1]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::MENU_BUTTON));
		buttons[1]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::MENU_BUTTON_COL));
	}

	firstSetup = false;
}

void PauseState::onEnter()
{
	gef::DebugOut("Entering the pause menu\n");

	setup();
}

void PauseState::onExit()
{
	buttons[0]->setSelectedByController(false);
	buttons[1]->setSelectedByController(false);
}

void PauseState::handleInput()
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

	if (context->getGameInput()->getKeyboard()->IsKeyPressed(context->getGameInput()->getKeyboard()->KC_ESCAPE) ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_SELECT)
	{
		context->setActiveState(StateLabel::LEVEL);
	}
}

bool PauseState::update(float deltaTime)
{
	fps = 1.0f / deltaTime;

	return true;
}

void PauseState::render()
{
	context->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context->getRenderer3D()->End();

	context->getSpriteRenderer()->Begin(false);

	//Render UI elements
	context->getSpriteRenderer()->DrawSprite(background);

	context->getSpriteRenderer()->DrawSprite(*buttons[0]);
	context->getSpriteRenderer()->DrawSprite(*buttons[1]);

	if (context->getFont())
	{		
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, platform.height() / 2.0f - 200.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, "PAUSED");

		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "FPS: %.1f", fps);
	}

	context->getSpriteRenderer()->End();
}

void PauseState::checkForController()
{
	if (context->getGameInput()->getController()->leftStick == ControllerCode::UP ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_UP)
	{
		buttons[buttonIndex]->setSelectedByController(false);

		if (buttonIndex <= 0)
		{
			buttonIndex = 1;
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

		if (buttonIndex >= 1)
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

void PauseState::checkButtonStatus(bool usingMouse)
{
	if (buttons[0]->isClicked(usingMouse))
	{
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context->setActiveState(StateLabel::LEVEL);
	}

	if (buttons[1]->isClicked(usingMouse))
	{
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context->setActiveState(StateLabel::MAIN_MENU);
	}
}