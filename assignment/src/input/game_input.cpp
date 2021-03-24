//@BridgetACasey

#include "game_input.h"
#include <iostream>

GameInput::GameInput(gef::Platform& platform, gef::InputManager* inputManager_)
{
	inputManager = inputManager_;

	active_touch_id_ = -1;
	
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
	if (inputManager)
	{
		inputManager->Update();

		processTouchInput();

		mousePosition = inputManager->touch_manager()->mouse_position();
	}

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

void GameInput::processTouchInput()
{
	const gef::TouchInputManager* touch_input = inputManager->touch_manager();

	if (touch_input && (touch_input->max_num_panels() > 0))
	{
		// get the active touches for this panel
		const gef::TouchContainer& panel_touches = touch_input->touches(0);

		// go through the touches
		for (gef::ConstTouchIterator touch = panel_touches.begin(); touch != panel_touches.end(); ++touch)
		{
			// if active touch id is -1, then we are not currently processing a touch
			if (active_touch_id_ == -1)
			{
				// check for the start of a new touch
				if (touch->type == gef::TT_NEW)
				{
					active_touch_id_ = touch->id;

					// do any processing for a new touch here
					// we're just going to record the position of the touch
					touch_position_ = touch->position;
				}
			}
			else if (active_touch_id_ == touch->id)
			{
				// we are processing touch data with a matching id to the one we are looking for
				if (touch->type == gef::TT_ACTIVE)
				{
					// update an active touch here
					// we're just going to record the position of the touch
					touch_position_ = touch->position;
				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// the touch we are tracking has been released
					// perform any actions that need to happen when a touch is released here
					// we're not doing anything here apart from resetting the active touch id
					active_touch_id_ = -1;
				}
			}
		}
	}
}

gef::Vector2& GameInput::getMousePosition()
{
	return mousePosition;
}