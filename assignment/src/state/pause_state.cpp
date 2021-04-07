//@BridgetACasey

#include "pause_state.h"
#include "context.h"

PauseState::PauseState(gef::Platform& platform) : State(platform)
{
	resumeButton = nullptr;
	menuButton = nullptr;
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

		resumeButton = Button::create(context_->getGameInput());
		menuButton = Button::create(context_->getGameInput());

		resumeButton->set_width(150.0f);
		resumeButton->set_height(75.0f);
		resumeButton->set_position(gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f));
		resumeButton->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::RESUME_BUTTON));
		resumeButton->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::RESUME_BUTTON_COL));

		menuButton->set_width(150.0f);
		menuButton->set_height(75.0f);
		menuButton->set_position(platform_.width() / 2.0f, resumeButton->position().y() + 75.0f, 0.0f);
		menuButton->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::MENU_BUTTON));
		menuButton->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::MENU_BUTTON_COL));
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

}

void PauseState::handleInput()
{
	context_->getGameInput()->update();

	if (menuButton->isClicked())
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::MAIN_MENU);
	}

	if (resumeButton->isClicked())
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::LEVEL);
	}

	if (context_->getGameInput()->getKeyboard()->IsKeyPressed(context_->getGameInput()->getKeyboard()->KC_ESCAPE))
	{
		context_->setActiveState(StateLabel::LEVEL);
	}
}

bool PauseState::update(float deltaTime)
{
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

	context_->getSpriteRenderer()->DrawSprite(*resumeButton);
	context_->getSpriteRenderer()->DrawSprite(*menuButton);

	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f - 200.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, "PAUSED");
	}

	context_->getSpriteRenderer()->End();
}