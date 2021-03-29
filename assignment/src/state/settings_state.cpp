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
		backButton = Button::create(context_->getGameInput());
		backButton->set_width(150.0f);
		backButton->set_height(75.0f);
		backButton->set_position(gef::Vector4(150.0f, 100.0f, 0.0f));

		gef::ImageData image_;
		gef::Texture* texture;

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
	return true;
}

void SettingsState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SETTINGS");
	}

	context_->getSpriteRenderer()->DrawSprite(*backButton);

	context_->getSpriteRenderer()->End();
}