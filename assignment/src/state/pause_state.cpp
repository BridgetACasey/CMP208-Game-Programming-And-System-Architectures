//@BridgetACasey

#include "pause_state.h"
#include "context.h"

PauseState::PauseState(gef::Platform& platform) : State(platform)
{
	buttonIndex = 0;
}

PauseState* PauseState::create(gef::Platform& platform)
{
	return new PauseState(platform);
}

void PauseState::setup()
{
	if (firstSetup)
	{
		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f);
		background.set_texture(context_->getTextureManager()->getTexture(TextureID::MENU_BACKGROUND_ALT));

		buttons[0] = Button::create(context_->getGameInput());
		buttons[1] = Button::create(context_->getGameInput());

		buttons[0]->set_width(150.0f);
		buttons[0]->set_height(75.0f);
		buttons[0]->set_position(gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f));
		buttons[0]->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::RESUME_BUTTON));
		buttons[0]->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::RESUME_BUTTON_COL));

		buttons[1]->set_width(150.0f);
		buttons[1]->set_height(75.0f);
		buttons[1]->set_position(platform_.width() / 2.0f, buttons[0]->position().y() + 75.0f, 0.0f);
		buttons[1]->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::MENU_BUTTON));
		buttons[1]->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::MENU_BUTTON_COL));
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
	context_->getGameInput()->update();

	if (context_->getGameInput()->getController()->active)
	{
		checkForController();
		checkButtonStatus(false);
	}

	else
	{
		checkButtonStatus(true);
	}

	if (context_->getGameInput()->getKeyboard()->IsKeyPressed(context_->getGameInput()->getKeyboard()->KC_ESCAPE) ||
		context_->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_SELECT)
	{
		context_->setActiveState(StateLabel::LEVEL);
	}
}

bool PauseState::update(float deltaTime)
{
	fps_ = 1.0f / deltaTime;

	return true;
}

void PauseState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	//Render UI elements
	context_->getSpriteRenderer()->DrawSprite(background);

	context_->getSpriteRenderer()->DrawSprite(*buttons[0]);
	context_->getSpriteRenderer()->DrawSprite(*buttons[1]);

	if (context_->getFont())
	{		
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f - 200.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, "PAUSED");

		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "FPS: %.1f", fps_);
	}

	context_->getSpriteRenderer()->End();
}

void PauseState::checkForController()
{
	if (context_->getGameInput()->getController()->leftStick == ControllerCode::UP ||
		context_->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_UP)
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

	else if (context_->getGameInput()->getController()->leftStick == ControllerCode::DOWN ||
		context_->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_DOWN)
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
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::LEVEL);
	}

	if (buttons[1]->isClicked(usingMouse))
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::MAIN_MENU);
	}
}