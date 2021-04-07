#include "splash_state.h"
#include "context.h"

SplashState::SplashState(gef::Platform& platform) : State(platform)
{
	transitionTime = 0.0f;
}

SplashState* SplashState::create(gef::Platform& platform)
{
	return new SplashState(platform);
}

void SplashState::setup()
{
	if (firstSetup)
	{
		gef::DebugOut("Splash Screen: Performing first time setup!\n");

		splashImage.set_height(platform_.height());
		splashImage.set_width(platform_.width());
		splashImage.set_position(platform_.width() / 2.0f, platform_.height() / 2.0f, 0.0f);

		splashImage.set_texture(context_->getTextureManager()->generateTexture("sprites/potato_lizard.png"));
	}

	firstSetup = false;
}

void SplashState::onEnter()
{
	gef::DebugOut("Entering splash screen\n");

	setup();

	context_->getGameAudio()->playSoundEffect(SoundEffectID::INTRO, false);
}

void SplashState::onExit()
{

}

void SplashState::handleInput()
{

}

bool SplashState::update(float deltaTime)
{
	if (transitionTime > 3.0f)
	{
		transitionTime = 0.0f;
		context_->setActiveState(StateLabel::MAIN_MENU);
	}

	transitionTime += 1.0f * deltaTime;

	return true;
}

void SplashState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	//Render UI elements
	context_->getSpriteRenderer()->DrawSprite(splashImage);
	
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "SPLASH SCREEN");
	}

	context_->getSpriteRenderer()->End();
}