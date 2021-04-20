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
		backButton = Button::create(context->getGameInput());
		backButton->set_width(150.0f);
		backButton->set_height(75.0f);
		backButton->set_position(gef::Vector4(100.0f, 50.0f, 0.0f));
		backButton->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::BACK_BUTTON));
		backButton->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::BACK_BUTTON_COL));

		background.set_height(platform.height());
		background.set_width(platform.width());
		background.set_position(platform.width() / 2.0f, platform.height() / 2.0f, 0.0f);
		background.set_texture(context->getTextureManager()->getTexture(TextureID::MENU_BACKGROUND_ALT));

		help.set_height(platform.height() - 100.0f);
		help.set_width(platform.width() - 100.0f);
		help.set_position(platform.width() / 2.0f, 310.0f, 0.0f);
		help.set_texture(context->getTextureManager()->getTexture(TextureID::HELP_SCREEN_BACKGROUND));
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

bool HelpState::update(float deltaTime)
{
	fps = 1.0f / deltaTime;

	return true;
}

void HelpState::render()
{
	context->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context->getRenderer3D()->End();

	context->getSpriteRenderer()->Begin(false);

	context->getSpriteRenderer()->DrawSprite(background);

	context->getSpriteRenderer()->DrawSprite(help);	//Display the help screen image

	//Render UI elements
	if (context->getFont())
	{
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "FPS: %.1f", fps);
		
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, 25.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, "HOW TO PLAY");
	}

	context->getSpriteRenderer()->DrawSprite(*backButton);

	context->getSpriteRenderer()->End();
}

void HelpState::checkForController()
{
	if (context->getGameInput()->getController()->leftStick == ControllerCode::UP ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_UP ||
		context->getGameInput()->getController()->leftStick == ControllerCode::DOWN ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_DOWN)
	{
		backButton->setSelectedByController(!backButton->getSelectedByController());
	}
}

void HelpState::checkButtonStatus(bool usingMouse)
{
	if (backButton->isClicked(usingMouse))
	{
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context->setActiveState(StateLabel::MAIN_MENU);
	}
}