//@BridgetACasey

#include "settings_state.h"
#include "context.h"

SettingsState::SettingsState(gef::Platform& platform) : State(platform)
{
	buttonIndex = 0;

	backButton = nullptr;

	masterVolumeSlider = nullptr;
	musicVolumeSlider = nullptr;
	sfxVolumeSlider = nullptr;
	speedSlider = nullptr;
	jumpSlider = nullptr;
}

SettingsState* SettingsState::create(gef::Platform& platform)
{
	return new SettingsState(platform);
}

void SettingsState::setup()
{
	if (firstSetup)
	{
		//Background image
		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f);
		background.set_texture(context_->getTextureManager()->getTexture(TextureID::MENU_BACKGROUND_ALT));

		//Back button to return to main menu
		backButton = Button::create(context_->getGameInput());
		backButton->set_width(150.0f);
		backButton->set_height(75.0f);
		backButton->set_position(gef::Vector4(150.0f, 100.0f, 0.0f));
		backButton->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::BACK_BUTTON));
		backButton->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::BACK_BUTTON_COL));

		//Volume sliders
		masterVolumeSlider = Slider::create(context_->getGameInput());
		masterVolumeSlider->setButtonDimensions(50.0f, 50.0f);
		masterVolumeSlider->setAnchorPoints(175.0f, 750.0f, 175.0f);
		masterVolumeSlider->setInitialPercentageValue(context_->getGameAudio()->getMasterVolume());
		masterVolumeSlider->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		masterVolumeSlider->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		masterVolumeSlider->getLowerBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		masterVolumeSlider->getUpperBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		masterVolumeSlider->updatePosition(0.0f, false);

		musicVolumeSlider = Slider::create(context_->getGameInput());
		musicVolumeSlider->setButtonDimensions(50.0f, 50.0f);
		musicVolumeSlider->setAnchorPoints(175.0f, 750.0f, 265.0f);
		musicVolumeSlider->setInitialPercentageValue(context_->getGameAudio()->getMusicVolume());
		musicVolumeSlider->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		musicVolumeSlider->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		musicVolumeSlider->getLowerBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		musicVolumeSlider->getUpperBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		musicVolumeSlider->updatePosition(0.0f, false);

		sfxVolumeSlider = Slider::create(context_->getGameInput());
		sfxVolumeSlider->setButtonDimensions(50.0f, 50.0f);
		sfxVolumeSlider->setAnchorPoints(175.0f, 750.0f, 355.0f);
		sfxVolumeSlider->setInitialPercentageValue(context_->getGameAudio()->getSFXVolume());
		sfxVolumeSlider->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		sfxVolumeSlider->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		sfxVolumeSlider->getLowerBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		sfxVolumeSlider->getUpperBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		sfxVolumeSlider->updatePosition(0.0f, false);

		speedSlider = Slider::create(context_->getGameInput());
		speedSlider->setButtonDimensions(50.0f, 50.0f);
		speedSlider->setAnchorPoints(175.0f, 425.0f, 450.0f);
		speedSlider->setInitialPercentageValue(100.0f);
		speedSlider->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::GEAR_BUTTON));
		speedSlider->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::GEAR_BUTTON_COL));
		speedSlider->getLowerBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		speedSlider->getUpperBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		speedSlider->updatePosition(0.0f, false);

		jumpSlider = Slider::create(context_->getGameInput());
		jumpSlider->setButtonDimensions(50.0f, 50.0f);
		jumpSlider->setAnchorPoints(500.0f, 750.0f, 450.0f);
		jumpSlider->setInitialPercentageValue(100.0f);
		jumpSlider->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::GEAR_BUTTON));
		jumpSlider->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::GEAR_BUTTON_COL));
		jumpSlider->getLowerBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		jumpSlider->getUpperBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		jumpSlider->updatePosition(0.0f, false);

		buttons[0] = backButton;
		buttons[1] = masterVolumeSlider;
		buttons[2] = musicVolumeSlider;
		buttons[3] = sfxVolumeSlider;
		buttons[4] = speedSlider;
		buttons[5] = jumpSlider;

		context_->setPlayerSpeed(context_->getMaxPlayerSpeed() * (speedSlider->getPercentageValue() / 100.0f));
		context_->setPlayerJumpForce(context_->getMaxPlayerJumpForce() * (jumpSlider->getPercentageValue() / 100.0f));
	}

	firstSetup = false;
}

void SettingsState::onEnter()
{
	gef::DebugOut("Entering the settings screen\n");

	setup();
}

void SettingsState::onExit()
{
	buttons[0]->setSelectedByController(false);
	buttons[1]->setSelectedByController(false);
	buttons[2]->setSelectedByController(false);
	buttons[3]->setSelectedByController(false);
	buttons[4]->setSelectedByController(false);
	buttons[5]->setSelectedByController(false);
}

void SettingsState::handleInput()
{

}

bool SettingsState::update(float deltaTime)
{
	context_->getGameInput()->update();

	if (context_->getGameInput()->getController()->active)
	{
		checkForController();
		checkButtonStatus(deltaTime, false);
	}

	else
	{
		checkButtonStatus(deltaTime, true);
	}

	return true;
}

void SettingsState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	context_->getSpriteRenderer()->DrawSprite(background);

	context_->getSpriteRenderer()->DrawSprite(*masterVolumeSlider->getLowerBackground());
	context_->getSpriteRenderer()->DrawSprite(*musicVolumeSlider->getLowerBackground());
	context_->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider->getLowerBackground());
	context_->getSpriteRenderer()->DrawSprite(*speedSlider->getLowerBackground());
	context_->getSpriteRenderer()->DrawSprite(*jumpSlider->getLowerBackground());

	context_->getSpriteRenderer()->DrawSprite(*masterVolumeSlider->getUpperBackground());
	context_->getSpriteRenderer()->DrawSprite(*musicVolumeSlider->getUpperBackground());
	context_->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider->getUpperBackground());
	context_->getSpriteRenderer()->DrawSprite(*speedSlider->getUpperBackground());
	context_->getSpriteRenderer()->DrawSprite(*jumpSlider->getUpperBackground());

	context_->getSpriteRenderer()->DrawSprite(*masterVolumeSlider);
	context_->getSpriteRenderer()->DrawSprite(*musicVolumeSlider);
	context_->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider);
	context_->getSpriteRenderer()->DrawSprite(*speedSlider);
	context_->getSpriteRenderer()->DrawSprite(*jumpSlider);

	context_->getSpriteRenderer()->DrawSprite(*backButton);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 50.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, "SETTINGS");
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 125.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "MASTER:   %.1f", masterVolumeSlider->getPercentageValue());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 210.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "MUSIC:   %.1f", musicVolumeSlider->getPercentageValue());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 300.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SFX:   %.1f", sfxVolumeSlider->getPercentageValue());

		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(300.0f, 400.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SPEED:   %.1f", context_->getPlayerSpeed());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(625.0f, 400.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "JUMP:   %.1f", context_->getPlayerJumpForce());
	}

	context_->getSpriteRenderer()->End();
}

void SettingsState::checkForController()
{
	if (context_->getGameInput()->getController()->leftStick == ControllerCode::UP ||
		context_->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_UP)
	{
		buttons[buttonIndex]->setSelectedByController(false);

		if (buttonIndex <= 0)
		{
			buttonIndex = 5;
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

		if (buttonIndex >= 5)
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

void SettingsState::checkButtonStatus(float deltaTime, bool usingMouse)
{
	if (backButton->isClicked(usingMouse))
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::MAIN_MENU);
	}

	if (masterVolumeSlider->isHeld(usingMouse))
	{
		masterVolumeSlider->updatePosition(deltaTime, usingMouse);

		context_->getGameAudio()->setMasterVolume(masterVolumeSlider->getPercentageValue());
	}

	if (musicVolumeSlider->isHeld(usingMouse))
	{
		musicVolumeSlider->updatePosition(deltaTime, usingMouse);

		context_->getGameAudio()->setMusicVolume(musicVolumeSlider->getPercentageValue());
	}

	if (sfxVolumeSlider->isHeld(usingMouse))
	{
		sfxVolumeSlider->updatePosition(deltaTime, usingMouse);

		context_->getGameAudio()->setSFXVolume(sfxVolumeSlider->getPercentageValue());
	}

	if (speedSlider->isHeld(usingMouse))
	{
		speedSlider->updatePosition(deltaTime, usingMouse);

		context_->setPlayerSpeed(context_->getMaxPlayerSpeed() * (speedSlider->getPercentageValue() / 100.0f));
	}

	if (jumpSlider->isHeld(usingMouse))
	{
		jumpSlider->updatePosition(deltaTime, usingMouse);

		context_->setPlayerJumpForce(context_->getMaxPlayerJumpForce() * (jumpSlider->getPercentageValue() / 100.0f));
	}
}