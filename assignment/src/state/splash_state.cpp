//@BridgetACasey

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

		splashImage.set_height(platform.height());
		splashImage.set_width(platform.width());
		splashImage.set_position(platform.width() / 2.0f, platform.height() / 2.0f, 0.0f);

		splashImage.set_texture(context->getTextureManager()->getTexture(TextureID::SPLASH_BACKGROUND));

		firstSetup = false;
	}
}

void SplashState::onEnter()
{
	gef::DebugOut("Entering splash screen\n");

	setup();

	context->getGameAudio()->playSoundEffect(SoundEffectID::INTRO, false);
}

void SplashState::onExit()
{
	context->getGameAudio()->clearSoundEffect(SoundEffectID::INTRO);	//Clearing this sound effect as the program won't need it again
}

void SplashState::handleInput()
{

}

bool SplashState::update(float deltaTime)
{
	fps = 1.0f / deltaTime;

	//After 3 full seconds pass, progress to the main menu
	if (transitionTime > 3.0f)
	{
		transitionTime = 0.0f;
		context->setActiveState(StateLabel::MAIN_MENU);
	}

	transitionTime += 1.0f * deltaTime;

	return true;
}

void SplashState::render()
{
	context->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context->getRenderer3D()->End();

	context->getSpriteRenderer()->Begin(false);

	//Render UI elements
	context->getSpriteRenderer()->DrawSprite(splashImage);

	if (context->getFont())
	{
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "FPS: %.1f", fps);
	}

	context->getSpriteRenderer()->End();
}