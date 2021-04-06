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

		//Bottom layers
		context_->getPNGLoader()->Load("slider_bar_bottom.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);

		masterBottomLayer.set_position(gef::Vector4((masterVolumeSlider->getMaxAnchorPoint() + masterVolumeSlider->getMinAnchorPoint()) / 2.0f,
			masterVolumeSlider->position().y(), masterVolumeSlider->position().z()));
		masterBottomLayer.set_height(masterVolumeSlider->height());
		masterBottomLayer.set_width(masterVolumeSlider->getMaxAnchorPoint() - masterVolumeSlider->getMinAnchorPoint());
		masterBottomLayer.set_texture(texture);

		musicBottomLayer.set_position(gef::Vector4((musicVolumeSlider->getMaxAnchorPoint() + musicVolumeSlider->getMinAnchorPoint()) / 2.0f,
			musicVolumeSlider->position().y(), musicVolumeSlider->position().z()));
		musicBottomLayer.set_height(musicVolumeSlider->height());
		musicBottomLayer.set_width(musicVolumeSlider->getMaxAnchorPoint() - musicVolumeSlider->getMinAnchorPoint());
		musicBottomLayer.set_texture(texture);

		sfxBottomLayer.set_position(gef::Vector4((sfxVolumeSlider->getMaxAnchorPoint() + sfxVolumeSlider->getMinAnchorPoint()) / 2.0f,
			sfxVolumeSlider->position().y(), sfxVolumeSlider->position().z()));
		sfxBottomLayer.set_height(sfxVolumeSlider->height());
		sfxBottomLayer.set_width(sfxVolumeSlider->getMaxAnchorPoint() - sfxVolumeSlider->getMinAnchorPoint());
		sfxBottomLayer.set_texture(texture);

		//Top layers
		context_->getPNGLoader()->Load("slider_bar_top.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);

		masterTopLayer.set_position(gef::Vector4((masterVolumeSlider->getMaxAnchorPoint() + masterVolumeSlider->getMinAnchorPoint()) / 2.0f,
			masterVolumeSlider->position().y(), masterVolumeSlider->position().z()));
		masterTopLayer.set_height(masterVolumeSlider->height());
		masterTopLayer.set_width(masterVolumeSlider->getMaxAnchorPoint() - masterVolumeSlider->getMinAnchorPoint());
		masterTopLayer.set_texture(texture);

		musicTopLayer.set_position(gef::Vector4((musicVolumeSlider->getMaxAnchorPoint() + musicVolumeSlider->getMinAnchorPoint()) / 2.0f,
			musicVolumeSlider->position().y(), musicVolumeSlider->position().z()));
		musicTopLayer.set_height(musicVolumeSlider->height());
		musicTopLayer.set_width(musicVolumeSlider->getMaxAnchorPoint() - musicVolumeSlider->getMinAnchorPoint());
		musicTopLayer.set_texture(texture);

		sfxTopLayer.set_position(gef::Vector4((sfxVolumeSlider->getMaxAnchorPoint() + sfxVolumeSlider->getMinAnchorPoint()) / 2.0f,
			sfxVolumeSlider->position().y(), sfxVolumeSlider->position().z()));
		sfxTopLayer.set_height(sfxVolumeSlider->height());
		sfxTopLayer.set_width(sfxVolumeSlider->getMaxAnchorPoint() - sfxVolumeSlider->getMinAnchorPoint());
		sfxTopLayer.set_texture(texture);

		//Back to main menu button
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
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::MAIN_MENU);
	}
}

bool SettingsState::update(float deltaTime)
{
	if (masterVolumeSlider->isHeld())
	{
		masterVolumeSlider->updatePosition();

		masterTopLayer.set_width((masterVolumeSlider->getMaxAnchorPoint() - masterVolumeSlider->getMinAnchorPoint()) * (masterVolumeSlider->getPercentageValue() / 100.0f));

		masterTopLayer.set_position(gef::Vector4((masterVolumeSlider->getMinAnchorPoint() + masterVolumeSlider->position().x()) / 2.0f + ((masterVolumeSlider->width() / 4.0f) * (masterVolumeSlider->getPercentageValue() / 100.0f)),
			masterTopLayer.position().y(), masterTopLayer.position().z()));

		context_->getGameAudio()->setMasterVolume(masterVolumeSlider->getPercentageValue());
	}

	if (musicVolumeSlider->isHeld())
	{
		musicVolumeSlider->updatePosition();

		musicTopLayer.set_width((musicVolumeSlider->getMaxAnchorPoint() - musicVolumeSlider->getMinAnchorPoint()) * (musicVolumeSlider->getPercentageValue() / 100.0f));

		musicTopLayer.set_position(gef::Vector4((musicVolumeSlider->getMinAnchorPoint() + musicVolumeSlider->position().x()) / 2.0f + ((musicVolumeSlider->width() / 4.0f) * (musicVolumeSlider->getPercentageValue() / 100.0f)),
			musicTopLayer.position().y(), musicTopLayer.position().z()));

		context_->getGameAudio()->setMusicVolume(musicVolumeSlider->getPercentageValue());
	}

	if (sfxVolumeSlider->isHeld())
	{
		sfxVolumeSlider->updatePosition();

		sfxTopLayer.set_width((sfxVolumeSlider->getMaxAnchorPoint() - sfxVolumeSlider->getMinAnchorPoint()) * (sfxVolumeSlider->getPercentageValue() / 100.0f));

		sfxTopLayer.set_position(gef::Vector4((sfxVolumeSlider->getMinAnchorPoint() + sfxVolumeSlider->position().x()) / 2.0f + ((sfxVolumeSlider->width() / 4.0f) * (sfxVolumeSlider->getPercentageValue() / 100.0f)),
			sfxTopLayer.position().y(), sfxTopLayer.position().z()));

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

	context_->getSpriteRenderer()->DrawSprite(masterBottomLayer);
	context_->getSpriteRenderer()->DrawSprite(musicBottomLayer);
	context_->getSpriteRenderer()->DrawSprite(sfxBottomLayer);

	context_->getSpriteRenderer()->DrawSprite(masterTopLayer);
	context_->getSpriteRenderer()->DrawSprite(musicTopLayer);
	context_->getSpriteRenderer()->DrawSprite(sfxTopLayer);

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