//@BridgetACasey

#include "help_state.h"
#include "context.h"

HelpState::HelpState(gef::Platform& platform) : State(platform)
{
	backButton = nullptr;
}

HelpState* HelpState::create(gef::Platform& platform)
{
	return new HelpState(platform);
}

void HelpState::setup()
{
	if (firstSetup)
	{
		backButton = Button::create(context_->getGameInput());
		backButton->set_width(150.0f);
		backButton->set_height(75.0f);
		backButton->set_position(gef::Vector4(100.0f, 50.0f, 0.0f));
		backButton->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::BACK_BUTTON));
		backButton->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::BACK_BUTTON_COL));

		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f);
		background.set_texture(context_->getTextureManager()->getTexture(TextureID::MENU_BACKGROUND_ALT));

		help.set_height(platform_.height() - 100.0f);
		help.set_width(platform_.width() - 100.0f);
		help.set_position(platform_.width() / 2.0f, 310.0f, 0.0f);
		help.set_texture(context_->getTextureManager()->getTexture(TextureID::HELP_SCREEN_BACKGROUND));
	}

	firstSetup = false;
}

void HelpState::onEnter()
{
	gef::DebugOut("Entering the help screen\n");

	setup();
}

void HelpState::onExit()
{
	backButton->setSelectedByController(false);
}

void HelpState::handleInput()
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
}

bool HelpState::update(float deltaTime)
{
	return true;
}

void HelpState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	context_->getSpriteRenderer()->DrawSprite(background);

	context_->getSpriteRenderer()->DrawSprite(help);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 25.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, "HOW TO PLAY");
	}

	context_->getSpriteRenderer()->DrawSprite(*backButton);

	context_->getSpriteRenderer()->End();
}

void HelpState::checkForController()
{
	if (context_->getGameInput()->getController()->leftStick == ControllerCode::UP ||
		context_->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_UP ||
		context_->getGameInput()->getController()->leftStick == ControllerCode::DOWN ||
		context_->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_DOWN)
	{
		backButton->setSelectedByController(!backButton->getSelectedByController());
	}
}

void HelpState::checkButtonStatus(bool usingMouse)
{
	if (backButton->isClicked(usingMouse))
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::MAIN_MENU);
	}
}