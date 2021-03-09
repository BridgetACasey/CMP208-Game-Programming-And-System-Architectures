//@BridgetACasey

#include "game_input.h"
#include <iostream>

GameInput::GameInput(gef::Platform& platform, gef::InputManager* inputManager_)
{
	inputManager = inputManager_;
	
	key_space = new Key();
	key_a = new Key();
	key_d = new Key();

	bindKeys();
}

GameInput::~GameInput()
{

}

GameInput* GameInput::create(gef::Platform& platform, gef::InputManager* inputManager_)
{
	return new GameInput(platform, inputManager_);
}

void GameInput::update(GameObject* gameObject)
{
	inputManager->Update();

	processKeyCommands(gameObject);
}

void GameInput::bindKeys()
{
	key_space->keyText = "SPACE";
	key_space->command = &jump;

	key_a->keyText = "A";
	key_a->command = &left;

	key_d->keyText = "D";
	key_d->command = &right;
}

void GameInput::processKeyCommands(GameObject* gameObject)
{
	Key* key = assignKeys();

	if (key)
	{
		key->command->executeCommand(gameObject);
	}
}

const gef::Vector2& GameInput::getMousePosition()
{
	return inputManager->touch_manager()->mouse_position();
}

Key* GameInput::assignKeys()
{
	const gef::Keyboard* keyboard = inputManager->keyboard();

	if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_SPACE))
	{
		return key_space;
	}

	if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_A))
	{
		return key_a;
	}

	if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_D))
	{
		return key_d;
	}

	return nullptr;
}