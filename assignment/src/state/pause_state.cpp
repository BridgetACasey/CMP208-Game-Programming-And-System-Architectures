//@BridgetACasey

#include "pause_state.h"
#include "context.h"

PauseState::PauseState(gef::Platform& platform) : State(platform)
{

}

PauseState* PauseState::create(gef::Platform& platform)
{
	return new PauseState(platform);
}

void PauseState::setup()
{

}

void PauseState::onEnter()
{
	gef::DebugOut("Entering the pause menu\n");
}

void PauseState::onExit()
{

}

void PauseState::handleInput()
{
	context_->getGameInput()->update();

	if (context_->getGameInput()->getKeyboard()->IsKeyPressed(context_->getGameInput()->getKeyboard()->KC_ESCAPE))
	{
		context_->setActiveState(StateLabel::LEVEL);
	}
}

void PauseState::update(float deltaTime)
{

}

void PauseState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "PAUSED");
	}

	context_->getSpriteRenderer()->End();
}