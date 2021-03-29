//@BridgetACasey

#include "end_state.h"
#include "context.h"

EndState::EndState(gef::Platform& platform) : State(platform)
{
	lastScore = 0;
	highestScore = 0;
}

EndState* EndState::create(gef::Platform& platform)
{
	return new EndState(platform);
}

void EndState::setup()
{
	if (firstSetup)
	{
		restartButton = Button::create(context_->getGameInput());
		restartButton->set_width(150.0f);
		restartButton->set_height(75.0f);
		restartButton->setInactiveColour(0xfffffff);
		restartButton->setHoveringColour(0xffffffff);
		restartButton->setClickedColour(0xffffffff);
		restartButton->set_position(gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f + 100.0f, 0.0f));
	}

	firstSetup = false;
}

void EndState::onEnter()
{
	gef::DebugOut("Entering the end screen\n");

	setup();

	lastScore = context_->getPlayerScore();

	if (lastScore > highestScore)
	{
		highestScore = lastScore;
	}
}

void EndState::onExit()
{

}

void EndState::handleInput()
{
	context_->getGameInput()->update();

	if (restartButton->isClicked())
	{
		context_->setActiveState(StateLabel::LEVEL);
	}
}

bool EndState::update(float deltaTime)
{
	return true;
}

void EndState::render()
{
	context_->getRenderer3D()->Begin(true);

	//Render 3D geometry

	context_->getRenderer3D()->End();

	context_->getSpriteRenderer()->Begin(false);

	//Render UI elements
	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f - 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE, "YOU DIED");
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(platform_.width() / 2.0f, platform_.height() / 2.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_CENTRE,
			"Last Score: %.1i   Highest Score: %.1i", lastScore, highestScore);
	}

	context_->getSpriteRenderer()->DrawSprite(*restartButton);

	context_->getSpriteRenderer()->End();
}

void EndState::setLastScore(int lastScore_)
{
	lastScore = lastScore_;
}