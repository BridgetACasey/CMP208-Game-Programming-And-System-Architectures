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

	buttons[0] = nullptr;
	buttons[1] = nullptr;
	buttons[2] = nullptr;
	buttons[3] = nullptr;
	buttons[4] = nullptr;
	buttons[5] = nullptr;
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
		background.set_height(platform.height());
		background.set_width(platform.width());
		background.set_position(platform.width() / 2.0f, platform.height() / 2.0f, 100.0f);
		background.set_texture(context->getTextureManager()->getTexture(TextureID::MENU_BACKGROUND_ALT));

		//Back button to return to main menu
		backButton = Button::create(context->getGameInput());
		backButton->set_width(150.0f);
		backButton->set_height(75.0f);
		backButton->set_position(gef::Vector4(150.0f, 100.0f, 50.0f));
		backButton->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::BACK_BUTTON));
		backButton->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::BACK_BUTTON_COL));

		//Volume sliders
		masterVolumeSlider = Slider::create(context->getGameInput());
		masterVolumeSlider->setButtonDimensions(50.0f, 50.0f);
		masterVolumeSlider->setAnchorPoints(175.0f, 750.0f, 175.0f, 0.0f);
		masterVolumeSlider->setInitialPercentageValue(context->getGameAudio()->getMasterVolume());
		masterVolumeSlider->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		masterVolumeSlider->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		masterVolumeSlider->getLowerBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		masterVolumeSlider->getUpperBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		masterVolumeSlider->updatePosition(0.0f, false);

		musicVolumeSlider = Slider::create(context->getGameInput());
		musicVolumeSlider->setButtonDimensions(50.0f, 50.0f);
		musicVolumeSlider->setAnchorPoints(175.0f, 750.0f, 265.0f, 0.0f);
		musicVolumeSlider->setInitialPercentageValue(context->getGameAudio()->getMusicVolume());
		musicVolumeSlider->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		musicVolumeSlider->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		musicVolumeSlider->getLowerBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		musicVolumeSlider->getUpperBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		musicVolumeSlider->updatePosition(0.0f, false);

		sfxVolumeSlider = Slider::create(context->getGameInput());
		sfxVolumeSlider->setButtonDimensions(50.0f, 50.0f);
		sfxVolumeSlider->setAnchorPoints(175.0f, 750.0f, 355.0f, 0.0f);
		sfxVolumeSlider->setInitialPercentageValue(context->getGameAudio()->getSFXVolume());
		sfxVolumeSlider->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		sfxVolumeSlider->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		sfxVolumeSlider->getLowerBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		sfxVolumeSlider->getUpperBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		sfxVolumeSlider->updatePosition(0.0f, false);

		//Player movement speed slider
		speedSlider = Slider::create(context->getGameInput());
		speedSlider->setButtonDimensions(50.0f, 50.0f);
		speedSlider->setAnchorPoints(175.0f, 425.0f, 450.0f, 0.0f);
		speedSlider->setInitialPercentageValue(100.0f);
		speedSlider->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::GEAR_BUTTON));
		speedSlider->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::GEAR_BUTTON_COL));
		speedSlider->getLowerBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		speedSlider->getUpperBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		speedSlider->updatePosition(0.0f, false);

		//Player jump force slider
		jumpSlider = Slider::create(context->getGameInput());
		jumpSlider->setButtonDimensions(50.0f, 50.0f);
		jumpSlider->setAnchorPoints(500.0f, 750.0f, 450.0f, 0.0f);
		jumpSlider->setInitialPercentageValue(100.0f);
		jumpSlider->setInactiveTexture(context->getTextureManager()->getTexture(TextureID::GEAR_BUTTON));
		jumpSlider->setHoveringTexture(context->getTextureManager()->getTexture(TextureID::GEAR_BUTTON_COL));
		jumpSlider->getLowerBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		jumpSlider->getUpperBackground()->set_texture(context->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
		jumpSlider->updatePosition(0.0f, false);

		//Loading each button/slider into a button array to be cycled through if using a controller
		buttons[0] = backButton;
		buttons[1] = masterVolumeSlider;
		buttons[2] = musicVolumeSlider;
		buttons[3] = sfxVolumeSlider;
		buttons[4] = speedSlider;
		buttons[5] = jumpSlider;
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
	fps = 1.0f / deltaTime;
	
	context->getGameInput()->update();

	if (context->getGameInput()->getController()->active)
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
	context->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context->getRenderer3D()->End();

	context->getSpriteRenderer()->Begin(false);

	context->getSpriteRenderer()->DrawSprite(background);
	context->getSpriteRenderer()->DrawSprite(*backButton);

	context->getSpriteRenderer()->DrawSprite(*masterVolumeSlider->getLowerBackground());
	context->getSpriteRenderer()->DrawSprite(*musicVolumeSlider->getLowerBackground());
	context->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider->getLowerBackground());
	context->getSpriteRenderer()->DrawSprite(*speedSlider->getLowerBackground());
	context->getSpriteRenderer()->DrawSprite(*jumpSlider->getLowerBackground());

	context->getSpriteRenderer()->DrawSprite(*masterVolumeSlider->getUpperBackground());
	context->getSpriteRenderer()->DrawSprite(*musicVolumeSlider->getUpperBackground());
	context->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider->getUpperBackground());
	context->getSpriteRenderer()->DrawSprite(*speedSlider->getUpperBackground());
	context->getSpriteRenderer()->DrawSprite(*jumpSlider->getUpperBackground());

	context->getSpriteRenderer()->DrawSprite(*masterVolumeSlider);
	context->getSpriteRenderer()->DrawSprite(*musicVolumeSlider);
	context->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider);
	context->getSpriteRenderer()->DrawSprite(*speedSlider);
	context->getSpriteRenderer()->DrawSprite(*jumpSlider);

	//Render UI elements
	if (context->getFont())
	{
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "FPS: %.1f", fps);
		
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, 50.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, "SETTINGS");
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, 125.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "MASTER:   %.1f", masterVolumeSlider->getPercentageValue());
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, 210.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "MUSIC:   %.1f", musicVolumeSlider->getPercentageValue());
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(platform.width() / 2.0f, 300.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SFX:   %.1f", sfxVolumeSlider->getPercentageValue());

		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(300.0f, 400.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SPEED:   %.1f", context->getPlayerSpeed());
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(625.0f, 400.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "JUMP:   %.1f", context->getPlayerJumpForce());
	}

	context->getSpriteRenderer()->End();
}

void SettingsState::checkForController()
{
	if (context->getGameInput()->getController()->leftStick == ControllerCode::UP ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_UP)
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

	else if (context->getGameInput()->getController()->leftStick == ControllerCode::DOWN ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_DOWN)
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
		context->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context->setActiveState(StateLabel::MAIN_MENU);
	}

	//Adjust the volume or player settings based on how far along the slider button is
	if (masterVolumeSlider->isHeld(usingMouse))
	{
		masterVolumeSlider->updatePosition(deltaTime, usingMouse);

		context->getGameAudio()->setMasterVolume(masterVolumeSlider->getPercentageValue());
	}

	if (musicVolumeSlider->isHeld(usingMouse))
	{
		musicVolumeSlider->updatePosition(deltaTime, usingMouse);

		context->getGameAudio()->setMusicVolume(musicVolumeSlider->getPercentageValue());
	}

	if (sfxVolumeSlider->isHeld(usingMouse))
	{
		sfxVolumeSlider->updatePosition(deltaTime, usingMouse);

		context->getGameAudio()->setSFXVolume(sfxVolumeSlider->getPercentageValue());
	}

	if (speedSlider->isHeld(usingMouse))
	{
		speedSlider->updatePosition(deltaTime, usingMouse);

		context->setPlayerSpeed(context->getMaxPlayerSpeed() * (speedSlider->getPercentageValue() / 100.0f));
	}

	if (jumpSlider->isHeld(usingMouse))
	{
		jumpSlider->updatePosition(deltaTime, usingMouse);

		context->setPlayerJumpForce(context->getMaxPlayerJumpForce() * (jumpSlider->getPercentageValue() / 100.0f));
	}
}