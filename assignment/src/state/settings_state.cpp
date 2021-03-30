//@BridgetACasey

#include "settings_state.h"
#include "context.h"

SettingsState::SettingsState(gef::Platform& platform) : State(platform)
{
	backButton = nullptr;
}

SettingsState* SettingsState::create(gef::Platform& platform)
{
	return new SettingsState(platform);
}

void SettingsState::setup()
{
	if (firstSetup)
	{
		gef::ImageData image_;
		gef::Texture* texture;

		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position((float)platform_.width() / 2.0f, (float)platform_.height() / 2.0f, 0.0f);
		context_->getPNGLoader()->Load("potato_lizard.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		background.set_texture(texture);

		masterVolumeSlider = Slider::create(context_->getGameInput());
		masterVolumeSlider->set_width(50.0f);
		masterVolumeSlider->set_height(50.0f);
		masterVolumeSlider->setAnchorPoints(175.0f, 750.0f);
		masterVolumeSlider->set_position(gef::Vector4(725.0f, 175.0f, 0.0f));
		context_->getPNGLoader()->Load("Square Buttons/Square Buttons/Music Square Button.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		masterVolumeSlider->setInactiveTexture(texture);
		context_->getPNGLoader()->Load("Square Buttons/Colored Square Buttons/Music col_Square Button.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		masterVolumeSlider->setHoveringTexture(texture);

		musicVolumeSlider = Slider::create(context_->getGameInput());
		musicVolumeSlider->set_width(50.0f);
		musicVolumeSlider->set_height(50.0f);
		musicVolumeSlider->setAnchorPoints(175.0f, 750.0f);
		musicVolumeSlider->set_position(gef::Vector4(725.0f, 265.0f, 0.0f));
		context_->getPNGLoader()->Load("Square Buttons/Square Buttons/Music Square Button.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		musicVolumeSlider->setInactiveTexture(texture);
		context_->getPNGLoader()->Load("Square Buttons/Colored Square Buttons/Music col_Square Button.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		musicVolumeSlider->setHoveringTexture(texture);

		sfxVolumeSlider = Slider::create(context_->getGameInput());
		sfxVolumeSlider->set_width(50.0f);
		sfxVolumeSlider->set_height(50.0f);
		sfxVolumeSlider->setAnchorPoints(175.0f, 750.0f);
		sfxVolumeSlider->set_position(gef::Vector4(725.0f, 355.0f, 0.0f));
		context_->getPNGLoader()->Load("Square Buttons/Square Buttons/Music Square Button.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		sfxVolumeSlider->setInactiveTexture(texture);
		context_->getPNGLoader()->Load("Square Buttons/Colored Square Buttons/Music col_Square Button.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		sfxVolumeSlider->setHoveringTexture(texture);

		backButton = Button::create(context_->getGameInput());
		backButton->set_width(150.0f);
		backButton->set_height(75.0f);
		backButton->set_position(gef::Vector4(150.0f, 100.0f, 0.0f));

		context_->getPNGLoader()->Load("Large Buttons/Large Buttons/Back Button.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		backButton->setInactiveTexture(texture);

		context_->getPNGLoader()->Load("Large Buttons/Colored Large Buttons/Backcol_Button.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		backButton->setHoveringTexture(texture);
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
		context_->setActiveState(StateLabel::MAIN_MENU);
	}
}

bool SettingsState::update(float deltaTime)
{
	masterVolumeSlider->updatePosition();
	musicVolumeSlider->updatePosition();
	sfxVolumeSlider->updatePosition();

	context_->getAudio()->setMasterVolume(masterVolumeSlider->getPercentageValue());
	context_->getAudio()->setMusicVolume(musicVolumeSlider->getPercentageValue());
	context_->getAudio()->setSFXVolume(sfxVolumeSlider->getPercentageValue());

	return true;
}

void SettingsState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	context_->getSpriteRenderer()->DrawSprite(background);

	context_->getSpriteRenderer()->DrawSprite(*backButton);
	context_->getSpriteRenderer()->DrawSprite(*masterVolumeSlider);
	context_->getSpriteRenderer()->DrawSprite(*musicVolumeSlider);
	context_->getSpriteRenderer()->DrawSprite(*sfxVolumeSlider);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(700.0f, 500.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "X: %.1f Y: %.1f",
			context_->getGameInput()->getMouse()->position.x, context_->getGameInput()->getMouse()->position.y);

		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(400.0f, 500.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "MSC: %.1f SFX: %.1f",
			context_->getAudio()->getMusicVolume(), context_->getAudio()->getSFXVolume());

		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SETTINGS");
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 125.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "MASTER: %.1f", masterVolumeSlider->getPercentageValue());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 210.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "MUSIC %.1f", musicVolumeSlider->getPercentageValue());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, 300.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SFX %.1f", sfxVolumeSlider->getPercentageValue());
	}

	context_->getSpriteRenderer()->End();
}