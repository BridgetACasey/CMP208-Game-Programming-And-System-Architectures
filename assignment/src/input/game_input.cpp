//@BridgetACasey

#include "game_input.h"
#include <iostream>

GameInput::GameInput(gef::Platform& platform)
{
	inputManager = gef::InputManager::Create(platform);

	// make sure if there is a panel to detect touch input, then activate it
	if (inputManager && inputManager->touch_manager() && (inputManager->touch_manager()->max_num_panels() > 0))
	{
		inputManager->touch_manager()->EnablePanel(0);
	}

	active_touch_id_ = -1;

	mouse = new Mouse();
	
	key_space = new Key();
	key_a = new Key();
	key_d = new Key();
	key_l_shift = new Key();

	bindKeys();
}

GameInput::~GameInput()
{

}

GameInput* GameInput::create(gef::Platform& platform)
{
	return new GameInput(platform);
}

void GameInput::update()
{
	if (inputManager)
	{
		inputManager->Update();

		if (mouse)
		{
			mouse->position = inputManager->touch_manager()->mouse_position();
		}

		processTouchInput();
	}
}

void GameInput::processGameObjectCommands(GameObject* gameObject)
{
	Key* key = assignKeys();

	if (key)
	{
		key->command->executeObjectCommand(gameObject);
	}
}

void GameInput::bindKeys()
{
	key_space->command = &jump;
	key_a->command = &left;
	key_d->command = &right;
	key_l_shift->command = &sprint;
}

void GameInput::processMouseButton(Int32 touchID, gef::TouchType type)
{
	MouseCode button;

	switch (type)
	{
		case gef::TouchType::TT_NEW:
			button = MouseCode::PRESSED;
			break;

		case gef::TouchType::TT_ACTIVE:
			button = MouseCode::HELD;
			break;

		case gef::TouchType::TT_RELEASED:
			button = MouseCode::RELEASED;
			break;

		default:
			button = MouseCode::NONE;
	}

	if (touchID == 0)
	{
		mouse->left = button;
	}

	if (touchID == 1)
	{
		mouse->right = button;
	}
}

Key* GameInput::assignKeys()
{
	if (inputManager->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_SPACE))
	{
		return key_space;
	}

	if (inputManager->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_A))
	{
		return key_a;
	}

	if (inputManager->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_D))
	{
		return key_d;
	}

	if (inputManager->keyboard()->IsKeyDown(gef::Keyboard::KeyCode::KC_LSHIFT))
	{
		return key_l_shift;
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
					processMouseButton(touch->id, touch->type);
				}
			}
			else if (active_touch_id_ == touch->id)
			{
				// we are processing touch data with a matching id to the one we are looking for
				if (touch->type == gef::TT_ACTIVE)
				{
					// update an active touch here
					// we're just going to record the position of the touch
					processMouseButton(touch->id, touch->type);
				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// the touch we are tracking has been released
					// perform any actions that need to happen when a touch is released here
					// we're not doing anything here apart from resetting the active touch id
					processMouseButton(touch->id, touch->type);

					active_touch_id_ = -1;
				}
			}
		}
	}
}

Mouse* GameInput::getMouse()
{
	return mouse;
}

gef::Keyboard* GameInput::getKeyboard()
{
	return inputManager->keyboard();
}