//@BridgetACasey

#include "game_input.h"

GameInput::GameInput()
{

}

GameInput* GameInput::Create(gef::InputManager* inputManager_)
{
	return nullptr;
}

void GameInput::update()
{
	inputManager->Update();
}

const gef::Vector2& GameInput::getMousePosition()
{
	return inputManager->touch_manager()->mouse_position();
}