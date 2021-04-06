#include "context.h"

Context::Context(gef::Platform& platform)
{
	playerScore = 0;
	gameComplete = false;

	activeState = nullptr;

	setupStateComponents(platform);

	LevelState* level = LevelState::create(platform);
	MenuState* mainMenu = MenuState::create(platform);
	PauseState* pauseMenu = PauseState::create(platform);
	SplashState* splashScreen = SplashState::create(platform);
	EndState* endScreen = EndState::create(platform);
	SettingsState* settings = SettingsState::create(platform);
	HelpState* help = HelpState::create(platform);

	states[StateLabel::LEVEL] = level;
	states[StateLabel::MAIN_MENU] = mainMenu;
	states[StateLabel::PAUSE_MENU] = pauseMenu;
	states[StateLabel::SPLASH_SCREEN] = splashScreen;
	states[StateLabel::END_SCREEN] = endScreen;
	states[StateLabel::SETTINGS] = settings;
	states[StateLabel::HELP] = help;
}

Context::~Context()
{
	delete states[StateLabel::LEVEL];
	delete states[StateLabel::MAIN_MENU];
	delete states[StateLabel::PAUSE_MENU];
	delete states[StateLabel::SPLASH_SCREEN];
	delete states[StateLabel::END_SCREEN];
	delete states[StateLabel::SETTINGS];
	delete states[StateLabel::HELP];
}

void Context::setupStateComponents(gef::Platform& platform)
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform);
	renderer_3d_ = gef::Renderer3D::Create(platform);

	primitive_builder_ = new PrimitiveBuilder(platform);
	gameInput = GameInput::create(platform);
	gameAudio = GameAudio::create(platform);
	textureManager = TextureManager::create(platform);

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

GameAudio* Context::getGameAudio()
{
	return gameAudio;
}

TextureManager* Context::getTextureManager()
{
	return textureManager;
}

void Context::setPlayerScore(int playerScore_)
{
	playerScore = playerScore_;
}

int Context::getPlayerScore()
{
	return playerScore;
}

void Context::setGameComplete(bool gameComplete_)
{
	gameComplete = gameComplete_;
}

bool Context::getGameComplete()
{
	return gameComplete;
}