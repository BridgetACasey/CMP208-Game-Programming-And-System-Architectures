//@BridgetACasey

#include "settings_state.h"
#include "context.h"

SettingsState::SettingsState(gef::Platform& platform) : State(platform)
{
	backButton = nullptr;

	masterVolumeSlider = nullptr;
	musicVolumeSlider = nullptr;
	sfxVolumeSlider = nullptr;
}

SettingsState* SettingsState::create(gef::Platform& platform)
{
	return new SettingsState(platform);
}

void SettingsState::setup()
{
	if (firstSetup)
	{
		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position((float)platform_.width() / 2.0f, (float)platform_.height() / 2.0f, 0.0f);
		background.set_texture(context_->getTextureManager()->getTexture(TextureID::MENU_BACKGROUND_ALT));

		//Back to main menu button
		backButton = Button::create(context_->getGameInput());
		backButton->set_width(150.0f);
		backButton->set_height(75.0f);
		backButton->set_position(gef::Vector4(150.0f, 100.0f, 0.0f));
		backButton->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::BACK_BUTTON));
		backButton->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::BACK_BUTTON_COL));

		//Volume sliders
		masterVolumeSlider = Slider::create(context_->getGameInput());
		masterVolumeSlider->set_width(50.0f);
		masterVolumeSlider->set_height(50.0f);
		masterVolumeSlider->set_position(gef::Vector4(725.0f, 175.0f, 0.0f));
		masterVolumeSlider->setAnchorPoints(175.0f, 750.0f);
		masterVolumeSlider->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		masterVolumeSlider->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		masterVolumeSlider->getLowerBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		masterVolumeSlider->getUpperBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_TOP));

		musicVolumeSlider = Slider::create(context_->getGameInput());
		musicVolumeSlider->set_width(50.0f);
		musicVolumeSlider->set_height(50.0f);
		musicVolumeSlider->set_position(gef::Vector4(725.0f, 265.0f, 0.0f));
		musicVolumeSlider->setAnchorPoints(175.0f, 750.0f);
		musicVolumeSlider->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		musicVolumeSlider->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		musicVolumeSlider->getLowerBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		musicVolumeSlider->getUpperBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_TOP));

		sfxVolumeSlider = Slider::create(context_->getGameInput());
		sfxVolumeSlider->set_width(50.0f);
		sfxVolumeSlider->set_height(50.0f);
		sfxVolumeSlider->set_position(gef::Vector4(725.0f, 355.0f, 0.0f));
		sfxVolumeSlider->setAnchorPoints(175.0f, 750.0f);
		sfxVolumeSlider->setInactiveTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON));
		sfxVolumeSlider->setHoveringTexture(context_->getTextureManager()->getTexture(TextureID::MUSIC_BUTTON_COL));
		sfxVolumeSlider->getLowerBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_BOTTOM));
		sfxVolumeSlider->getUpperBackground()->set_texture(context_->getTextureManager()->getTexture(TextureID::SLIDER_TOP));
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

}

void SettingsState::handleInput()
{
	context_->getGameInput()->update();

	if (backButton->isClicked())
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::MAIN_MENU);
	}
}

bool SettingsState::update(float deltaTime)
{
	if (masterVolumeSlider->isHeld())
	{
		masterVolumeSlider->updatePosition();

		context_->getGameAudio()->setMasterVolume(masterVolumeSlider->getPercentageValue());
	}

	if (musicVolumeSlider->isHeld())
	{
		musicVolumeSlider->updatePosition();

		context_->getGameAudio()->setMusicVolume(musicVolumeSlider->getPercentageValue());
	}

	if (sfxVolumeSlider->isHeld())
	{
		sfxVolumeSlider->updatePosition();

		context_->getGameAudio()->setSFXVolume(sfxVolumeSlider->getPercentageValue());
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

	context_->getSpriteRenderer()->DrawSprite(*masterVolumeSlider->getUpperBackground());
	context_->getSpriteRenderer()->DrawSprite(*musicVolumeSlider->getUpperBackground());
	context_->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider->getUpperBackground());

	context_->getSpriteRenderer()->DrawSprite(*masterVolumeSlider);
	context_->getSpriteRenderer()->DrawSprite(*musicVolumeSlider);
	context_->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider);

	context_->getSpriteRenderer()->DrawSprite(*backButton);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(700.0f, 500.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "X: %.1f Y: %.1f",
			context_->getGameInput()->getMouse()->position.x, context_->getGameInput()->getMouse()->position.y);

		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 50.0f, -0.9f), 1.5f, 0xffffffff, gef::TJ_CENTRE, "SETTINGS");
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 125.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "MASTER:   %.1f", masterVolumeSlider->getPercentageValue());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 210.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "MUSIC:   %.1f", musicVolumeSlider->getPercentageValue());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 300.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SFX:   %.1f", sfxVolumeSlider->getPercentageValue());
	}

	context_->getSpriteRenderer()->End();
}