//@BridgetACasey

#include "help_state.h"
#include "context.h"

HelpState::HelpState(gef::Platform& platform) : State(platform)
{
	backButton = nullptr;
}

HelpState* HelpState::create(gef::Platform& platform)
{
	return new HelpState(platform);
}

void HelpState::setup()
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

		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position((float)platform_.width() / 2.0f, (float)platform_.height() / 2.0f, 0.0f);
		context_->getPNGLoader()->Load("potato_lizard.png", platform_, image_);
		texture = gef::Texture::Create(platform_, image_);
		background.set_texture(texture);
	}

	firstSetup = false;
}

void HelpState::onEnter()
{
	gef::DebugOut("Entering the help screen\n");
	setup();
}

void HelpState::onExit()
{

}

void HelpState::handleInput()
{
	context_->getGameInput()->update();

	if (backButton->isClicked())
	{
		context_->getAudio()->manager()->PlaySample(1, false);
		context_->setActiveState(StateLabel::MAIN_MENU);
	}
}

bool HelpState::update(float deltaTime)
{
	return true;
}

void HelpState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	context_->getSpriteRenderer()->DrawSprite(background);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "HELP");
	}

	context_->getSpriteRenderer()->DrawSprite(*backButton);

	context_->getSpriteRenderer()->End();
}