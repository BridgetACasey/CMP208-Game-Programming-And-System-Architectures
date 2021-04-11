//@BridgetACasey

#include "end_state.h"
#include "context.h"

EndState::EndState(gef::Platform& platform) : State(platform)
{
	lastScore = 0;
	highestScore = 0;

	buttonIndex = 0;
	
	play = true;
}

EndState* EndState::create(gef::Platform& platform)
{
	return new EndState(platform);
}

void EndState::setup()
{
	if (firstSetup)
	{
		buttons[0] = Button::create(context_->getGameInput());
		buttons[0]->set_width(150.0f);
		buttons[0]->set_height(75.0f);
		buttons[0]->set_position(gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f));
		buttons[0]->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::NEW_GAME_BUTTON));
		buttons[0]->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::NEW_GAME_BUTTON_COL));

		buttons[1] = Button::create(context_->getGameInput());
		buttons[1]->set_width(150.0f);
		buttons[1]->set_height(75.0f);
		buttons[1]->set_position(gef::Vector4(platform_.width() / 2.0f, buttons[0]->position().y() + 75.0f, 0.0f));
		buttons[1]->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::QUIT_BUTTON));
		buttons[1]->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::QUIT_BUTTON_COL));

		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f);
	}

	firstSetup = false;
}

void EndState::onEnter()
{
	gef::DebugOut("Entering the end screen\n");

	setup();

	lastScore = context_->getPlayerScore();

	if (lastScore > highestScore)
	{
		highestScore = lastScore;
	}

	if (context_->getGameWon())
	{
		background.set_texture(context_->getTextureManager()->getTexture(TextureID::END_WIN_BACKGROUND));
		text = "YOU REACHED THE CAMPFIRE";
		context_->getGameAudio()->playSoundEffect(SoundEffectID::WIN, false);
	}

	else
	{
		background.set_texture(context_->getTextureManager()->getTexture(TextureID::END_LOSE_BACKGROUND));
		text = "YOU DIED";
		context_->getGameAudio()->playSoundEffect(SoundEffectID::LOSE, false);
	}

	context_->getGameAudio()->playMusic(MusicID::NONE);
}

void EndState::onExit()
{
	buttons[0]->setSelectedByController(false);
	buttons[1]->setSelectedByController(false);
}

void EndState::handleInput()
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

bool EndState::update(float deltaTime)
{
	return play;
}

void EndState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	context_->getSpriteRenderer()->DrawSprite(background);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 75.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, text);
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 140.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "Last Score: %.1i", lastScore);
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 170.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "Highest Score: %.1i", highestScore);
	}

	context_->getSpriteRenderer()->DrawSprite(*buttons[0]);
	context_->getSpriteRenderer()->DrawSprite(*buttons[1]);

	context_->getSpriteRenderer()->End();
}

void EndState::checkForController()
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

void EndState::checkButtonStatus(bool usingMouse)
{
	if (buttons[0]->isClicked(usingMouse))
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::MAIN_MENU);
	}

	if (buttons[1]->isClicked(usingMouse))
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		play = false;
	}
}

void EndState::setLastScore(int lastScore_)
{
	lastScore = lastScore_;
}