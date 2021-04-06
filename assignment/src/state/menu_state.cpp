//@BridgetACasey

#include "menu_state.h"
#include "context.h"

MenuState::MenuState(gef::Platform& platform) : State(platform)
{
	playButton = nullptr;
	settingsButton = nullptr;
	helpButton = nullptr;
	exitButton = nullptr;

	play = true;
}

MenuState* MenuState::create(gef::Platform& platform)
{
	return new MenuState(platform);
}

void MenuState::setup()
{
	if (firstSetup)
	{
		gef::DebugOut("Main Menu: Performing first time setup!\n");

		background.set_height(platform_.height());
		background.set_width(platform_.width());
		background.set_position((float)platform_.width() / 2.0f, (float)platform_.height() / 2.0f, 0.0f);
		background.set_texture(context_->getTextureManager()->generateTexture("potato_lizard.png"));

		backgroundCopy = background;
		backgroundCopy.set_position(backgroundCopy.width() / 2.0f + (float)platform_.width(), platform_.height() / 2.0f, 0.0f);

		playButton = Button::create(context_->getGameInput());
		settingsButton = Button::create(context_->getGameInput());
		helpButton = Button::create(context_->getGameInput());
		exitButton = Button::create(context_->getGameInput());

		playButton->set_width(150.0f);
		playButton->set_height(75.0f);
		playButton->set_position(gef::Vector4(platform_.width() / 2.0f, (platform_.height() / 2.0f) - 50.0f, 0.0f));
		playButton->setInactiveTexture(context_->getTextureManager()->generateTexture("Large Buttons/Large Buttons/Play Button.png"));
		playButton->setHoveringTexture(context_->getTextureManager()->generateTexture("Large Buttons/Colored Large Buttons/Playcol_Button.png"));

		settingsButton->set_width(150.0f);
		settingsButton->set_height(75.0f);
		settingsButton->set_position(gef::Vector4(playButton->position().x(), playButton->position().y() + 75.0f, 0.0f));
		settingsButton->setInactiveTexture(context_->getTextureManager()->generateTexture("Large Buttons/Large Buttons/Settings Button.png"));
		settingsButton->setHoveringTexture(context_->getTextureManager()->generateTexture("Large Buttons/Colored Large Buttons/Settingscol_Button.png"));

		helpButton->set_width(150.0f);
		helpButton->set_height(75.0f);
		helpButton->set_position(gef::Vector4(settingsButton->position().x(), settingsButton->position().y() + 75.0f, 0.0f));
		helpButton->setInactiveTexture(context_->getTextureManager()->generateTexture("Large Buttons/Large Buttons/Controls Button.png"));
		helpButton->setHoveringTexture(context_->getTextureManager()->generateTexture("Large Buttons/Colored Large Buttons/Controlscol_Button.png"));

		exitButton->set_width(150.0f);
		exitButton->set_height(75.0f);
		exitButton->set_position(gef::Vector4(helpButton->position().x(), helpButton->position().y() + 75.0f, 0.0f));
		exitButton->setInactiveTexture(context_->getTextureManager()->generateTexture("Large Buttons/Large Buttons/Exit Button.png"));
		exitButton->setHoveringTexture(context_->getTextureManager()->generateTexture("Large Buttons/Colored Large Buttons/Exitcol_Button.png"));

		context_->getGameAudio()->playMusic(MusicID::MENU);
		context_->getGameAudio()->loadSoundEffect(SoundEffectID::CLICK);
	}

	firstSetup = false;
}

void MenuState::onEnter()
{
	gef::DebugOut("Entering the main menu\n");

	setup();
}

void MenuState::onExit()
{

}

void MenuState::handleInput()
{
	context_->getGameInput()->update();

	if (playButton->isClicked())
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::LEVEL);
	}

	if (settingsButton->isClicked())
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::SETTINGS);
	}

	if (helpButton->isClicked())
	{
		context_->getGameAudio()->playSoundEffect(SoundEffectID::CLICK, false);
		context_->setActiveState(StateLabel::HELP);
	}

	if (exitButton->isClicked())
	{
		play = false;
	}
}

bool MenuState::update(float deltaTime)
{
	updateBackground(deltaTime);

	return play;
}

void MenuState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	//Render UI elements
	context_->getSpriteRenderer()->DrawSprite(background);
	context_->getSpriteRenderer()->DrawSprite(backgroundCopy);

	context_->getSpriteRenderer()->DrawSprite(*playButton);
	context_->getSpriteRenderer()->DrawSprite(*settingsButton);
	context_->getSpriteRenderer()->DrawSprite(*helpButton);
	context_->getSpriteRenderer()->DrawSprite(*exitButton);

	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(700.0f, 500.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "X: %.1f Y: %.1f",
			context_->getGameInput()->getMouse()->position.x, context_->getGameInput()->getMouse()->position.y);
	}

	context_->getSpriteRenderer()->End();
}

void MenuState::updateBackground(float deltaTime)
{
	background.set_position(background.position().x() - 75.0f * deltaTime, background.position().y(), background.position().z());
	backgroundCopy.set_position(backgroundCopy.position().x() - 75.0f * deltaTime, backgroundCopy.position().y(), backgroundCopy.position().z());

	if (background.position().x() < -(background.width() / 2.0f))
	{
		background.set_position((float)platform_.width() / 2.0f, (float)platform_.height() / 2.0f, 0.0f);
	}

	if (backgroundCopy.position().x() < backgroundCopy.width() / 2.0f)
	{
		backgroundCopy.set_position(backgroundCopy.width() / 2.0f + (float)platform_.width(), platform_.height() / 2.0f, 0.0f);
	}
}