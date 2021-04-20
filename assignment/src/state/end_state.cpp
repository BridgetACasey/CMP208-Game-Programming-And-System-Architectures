//@BridgetACasey

#include "end_state.h"
#include "context.h"

EndState::EndState(gef::Platform& platform) : State(platform)
{
	lastScore = 0;
	highestScore = 0;

	buttonIndex = 0;

	text = nullptr;

	buttons[0] = nullptr;	//Restart/New Game button
	buttons[1] = nullptr;	//Quit button
	
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
		buttons[0] = Button::create(context->getGameInput());
		buttons[0]->set_width(150.0f);
		buttons[0]->set_height(75.0f);
		buttons[0]->set_position(gef::Vector4(platform.width() / 2.0f, platform.height() / 2.0f, 0.0f));
		buttons[0]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::NEW_GAME_BUTTON));
		buttons[0]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::NEW_GAME_BUTTON_COL));

		buttons[1] = Button::create(context->getGameInput());
		buttons[1]->set_width(150.0f);
		buttons[1]->set_height(75.0f);
		buttons[1]->set_position(gef::Vector4(platform.width() / 2.0f, buttons[0]->position().y() + 75.0f, 0.0f));
		buttons[1]->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::QUIT_BUTTON));
		buttons[1]->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::QUIT_BUTTON_COL));

		background.set_height(platform.height());
		background.set_width(platform.width());
		background.set_position(platform.width() / 2.0f, platform.height() / 2.0f, 0.0f);
	}

	firstSetup = false;
}

void EndState::onEnter()
{
	gef::DebugOut("Entering the end screen\n");

	setup();

	lastScore = context->getPlayerScore();

	if (lastScore > highestScore)
	{
		highestScore = lastScore;
	}

	//Checks if the player has won or lost
	if (context->getGameWon())
	{
		background.set_texture(context->getTextureManager()->getTexture(TextureID::END_WIN_BACKGROUND));
		text = "YOU REACHED THE CAMPFIRE";
		context->getGameAudio()->playSoundEffect(SoundEffectID::WIN, false);
	}

	else
	{
		background.set_texture(context->getTextureManager()->getTexture(TextureID::END_LOSE_BACKGROUND));
		text = "YOU DIED";
		context->getGameAudio()->playSoundEffect(SoundEffectID::LOSE, false);
	}

	context->getGameAudio()->playMusic(MusicID::NONE);
}

void EndState::onExit()
{
	//Setting the buttons to be deselected upon exit, to prevent glitches when reentering the state
	buttons[0]->setSelectedByController(false);
	buttons[1]->setSelectedByController(false);
}

void EndState::handleInput()
{
	context->getGameInput()->update();

	//If the controller is the active input device, cycle through the buttons, otherwise check the mouse position
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

bool EndState::update(float deltaTime)
{
	fps = 1.0f / deltaTime;
	
	return play;
}

void EndState::render()
{
	context->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context->getRenderer3D()->End();

	context->getSpriteRenderer()->Begin(false);

	context->getSpriteRenderer()->DrawSprite(background);

	//Render UI elements
	if (context->getFont())
	{
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "FPS: %.1f", fps);
		
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, 75.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, text);
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, 140.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "Last Score: %.1i", lastScore);
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, 170.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "Highest Score: %.1i", highestScore);
	}

	context->getSpriteRenderer()->DrawSprite(*buttons[0]);
	context->getSpriteRenderer()->DrawSprite(*buttons[1]);

	context->getSpriteRenderer()->End();
}

void EndState::checkForController()	//Cycling through the buttons in the scene to check which is actively selected based on controller input
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

void EndState::checkButtonStatus(bool usingMouse)	//Executing button commands based on which one is clicked
{
	if (buttons[0]->isClicked(usingMouse))
	{
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context->setActiveState(StateLabel::MAIN_MENU);
	}

	if (buttons[1]->isClicked(usingMouse))
	{
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		play = false;
	}
}

void EndState::setLastScore(int score)
{
	lastScore = score;
}