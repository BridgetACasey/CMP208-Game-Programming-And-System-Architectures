//@BridgetACasey

#include "context.h"

Context::Context(gef::Platform& platform)
{
	//Player score, to be passed between the level and end state
	playerScore = 0;

	//Default player movement values, to be used in the settings state
	maxPlayerSpeed = 8.0f;
	maxPlayerJumpForce = 500.0f;
	playerSpeed = maxPlayerSpeed;
	playerJumpForce = maxPlayerJumpForce;

	//To check if the level is being actively played, or has been successfully completed
	gameWon = false;
	gamePlaying = false;

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
	spriteRenderer = gef::SpriteRenderer::Create(platform);
	renderer3D = gef::Renderer3D::Create(platform);

	primitiveBuilder = new PrimitiveBuilder(platform);
	gameInput = GameInput::create(platform);
	gameAudio = GameAudio::create(platform);
	textureManager = TextureManager::create(platform);
	meshManager = MeshManager::create(platform);

	font = new gef::Font(platform);
	font->Load("comic_sans");
}

void Context::setActiveState(StateLabel stateName)
{
	//Changes the active state and passes a reference to the same instance of the context class
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
	return spriteRenderer;
}

gef::Renderer3D* Context::getRenderer3D()
{
	return renderer3D;
}

gef::Font* Context::getFont()
{
	return font;
}

PrimitiveBuilder* Context::getPrimitiveBuilder()
{
	return primitiveBuilder;
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

MeshManager* Context::getMeshManager()
{
	return meshManager;
}

void Context::setPlayerScore(int score)
{
	playerScore = score;
}

int Context::getPlayerScore()
{
	return playerScore;
}

void Context::setPlayerSpeed(float speed)
{
	playerSpeed = speed;
}

float Context::getPlayerSpeed()
{
	return playerSpeed;
}

void Context::setPlayerJumpForce(float force)
{
	playerJumpForce = force;
}

float Context::getPlayerJumpForce()
{
	return playerJumpForce;
}

float Context::getMaxPlayerSpeed()
{
	return maxPlayerSpeed;
}

float Context::getMaxPlayerJumpForce()
{
	return maxPlayerJumpForce;
}

void Context::setGameWon(bool won)
{
	gameWon = won;
}

bool Context::getGameWon()
{
	return gameWon;
}

void Context::setGamePlaying(bool playing)
{
	gamePlaying = playing;
}

bool Context::getGamePlaying()
{
	return gamePlaying;
}