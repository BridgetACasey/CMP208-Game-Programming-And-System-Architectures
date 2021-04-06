//@BridgetACasey

#include "pause_state.h"
#include "context.h"

PauseState::PauseState(gef::Platform& platform) : State(platform)
{
	resumeButton = nullptr;
	backButton = nullptr;
}

PauseState* PauseState::create(gef::Platform& platform)
{
	return new PauseState(platform);
}

void PauseState::setup()
{
	if (firstSetup)
	{
		resumeButton = Button::create(context_->getGameInput());
		backButton = Button::create(context_->getGameInput());

		resumeButton->set_width(150.0f);
		resumeButton->set_height(75.0f);
		resumeButton->set_position(gef::Vector4((float)platform_.width() / 2.0f, (float)platform_.height() / 2.0f, 0.0f));
		resumeButton->setInactiveTexture(context_->getTextureManager()->generateTexture("Large Buttons/Large Buttons/Resume Button.png"));
		resumeButton->setHoveringTexture(context_->getTextureManager()->generateTexture("Large Buttons/Colored Large Buttons/Resumecol_Button.png"));

		backButton->set_width(150.0f);
		backButton->set_height(75.0f);
		backButton->set_position((float)platform_.width() / 2.0f, (float)platform_.height() / 2.0f + 100.0f, 0.0f);
		backButton->setInactiveTexture(context_->getTextureManager()->generateTexture("Large Buttons/Large Buttons/Menu Button.png"));
		backButton->setHoveringTexture(context_->getTextureManager()->generateTexture("Large Buttons/Colored Large Buttons/Menucol_Button.png"));

		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position((float)platform_.width() / 2.0f, (float)platform_.height() / 2.0f, 0.0f);
		background.set_texture(context_->getTextureManager()->generateTexture("potato_lizard.png"));
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

	if (backButton->isClicked())
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
	context_->getSpriteRenderer()->DrawSprite(*backButton);

	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f - 125.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "PAUSED");
	}

	context_->getSpriteRenderer()->End();
}