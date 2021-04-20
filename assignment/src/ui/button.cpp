//@BridgetACasey

#include "button.h"

Button::Button(GameInput* input)
{
	gameInput = input;

	inactive = nullptr;
	hovering = nullptr;

	selectedByController = false;
}

Button* Button::create(GameInput* input)
{
	return new Button(input);
}

bool Button::isHovering(bool isMouse)
{
	//Checks if the mouse is overlapping the bounds of the button object
	if (isMouse)
	{
		if (gameInput->getMouse()->position.x > position_.x() - (width() / 2.0f) && gameInput->getMouse()->position.x < position_.x() + (width() / 2.0f))
		{
			if (gameInput->getMouse()->position.y > position_.y() - (height() / 2.0f) && gameInput->getMouse()->position.y < position_.y() + (height() / 2.0f))
			{
				set_texture(hovering);
				return true;
			}
		}
	}

	//Otherwise, if it is marked as active by the controller, assume it is being hovered over in the same way
	else
	{
		if (selectedByController)
		{
			set_texture(hovering);
			return true;
		}
	}

	set_texture(inactive);

	return false;
}

bool Button::isClicked(bool isMouse)
{
	//Checks if the appropriate button has been pressed whilst hovering
	//This is the function that would normally be used when assigning an action to a button
	if (isHovering(isMouse))
	{
		if (isMouse)
		{
			if (gameInput->getMouse()->left == MouseCode::PRESSED)
			{
				return true;
			}
		}

		else
		{
			if (gameInput->getSonyController()->buttons_pressed() == gef_SONY_CTRL_CROSS)
			{
				return true;
			}
		}
	}

	return false;
}

bool Button::isHeld(bool isMouse)
{
	//Similar to isClicked, but checks if the corresponding button has been held down instead
	//Assumes that if the controller is being used, the button is held down anyway
	if (isHovering(isMouse))
	{
		if (isMouse)
		{
			if (gameInput->getMouse()->left == MouseCode::HELD)
			{
				return true;
			}
		}

		else
		{
			if (selectedByController)
			{
				return true;
			}
		}
	}

	return false;
}

void Button::setInactiveTexture(gef::Texture* texture)
{
	inactive = texture;
}

void Button::setHoveringTexture(gef::Texture* texture)
{
	hovering = texture;
}

void Button::setSelectedByController(bool selected)
{
	selectedByController = selected;
}

bool Button::getSelectedByController()
{
	return selectedByController;
}