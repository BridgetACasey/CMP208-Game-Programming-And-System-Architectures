#include "context.h"

Context::Context(gef::Platform& platform)
{
	activeState = nullptr;

	setupStateComponents(platform);

	LevelState* level = LevelState::create(platform);
	MenuState* mainMenu = MenuState::create(platform);
	PauseState* pauseMenu = PauseState::create(platform);
	SplashState* splashScreen = SplashState::create(platform);

	states[StateLabel::LEVEL] = level;
	states[StateLabel::MAIN_MENU] = mainMenu;
	states[StateLabel::PAUSE_MENU] = pauseMenu;
	states[StateLabel::SPLASH_SCREEN] = splashScreen;

	setActiveState(StateLabel::SPLASH_SCREEN);
}

Context::~Context()
{
	delete states[StateLabel::LEVEL];
	delete states[StateLabel::MAIN_MENU];
	delete states[StateLabel::PAUSE_MENU];
	delete states[StateLabel::SPLASH_SCREEN];
}

void Context::setupStateComponents(gef::Platform& platform)
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform);
	renderer_3d_ = gef::Renderer3D::Create(platform);
	input_manager_ = gef::InputManager::Create(platform);

	// make sure if there is a panel to detect touch input, then activate it
	if (input_manager_ && input_manager_->touch_manager() && (input_manager_->touch_manager()->max_num_panels() > 0))
	{
		input_manager_->touch_manager()->EnablePanel(0);
	}

	primitive_builder_ = new PrimitiveBuilder(platform);
	gameInput = GameInput::create(platform, input_manager_);

	font_ = new gef::Font(platform);
	font_->Load("comic_sans");
}

void Context::setActiveState(StateLabel stateName)
{
	if (activeState)
	{
		activeState->onExit();
	}

	activeState = states[stateName];

	activeState->setContext(this);

	activeState->onEnter();
}

State* Context::getActiveState()
{
	return activeState;
}

gef::SpriteRenderer* Context::getSpriteRenderer()
{
	return sprite_renderer_;
}

gef::Renderer3D* Context::getRenderer3D()
{
	return renderer_3d_;
}

gef::Font* Context::getFont()
{
	return font_;
}

PrimitiveBuilder* Context::getPrimitiveBuilder()
{
	return primitive_builder_;
}

GameInput* Context::getGameInput()
{
	return gameInput;
}