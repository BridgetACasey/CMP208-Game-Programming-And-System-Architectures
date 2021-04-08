//@BridgetACasey

#include "button.h"

Button::Button(GameInput* input_)
{
	input = input_;

	inactive = nullptr;
	hovering = nullptr;

	selectedByController = false;
}

Button* Button::create(GameInput* input_)
{
	return new Button(input_);
}

bool Button::isHovering(bool isMouse)
{
	if (isMouse)
	{
		if (input->getMouse()->position.x > position_.x() - (width() / 2.0f) && input->getMouse()->position.x < position_.x() + (width() / 2.0f))
		{
			if (input->getMouse()->position.y > position_.y() - (height() / 2.0f) && input->getMouse()->position.y < position_.y() + (height() / 2.0f))
			{
				set_texture(hovering);
				return true;
			}
		}
	}

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
	if (isHovering(isMouse))
	{
		if (isMouse)
		{
			if (input->getMouse()->left == MouseCode::PRESSED)
			{
				return true;
			}
		}

		else
		{
			if (input->getSonyController()->buttons_pressed() == gef_SONY_CTRL_CROSS)
			{
				return true;
			}
		}
	}

	return false;
}

bool Button::isHeld(bool isMouse)
{
	if (isHovering(isMouse))
	{
		if (isMouse)
		{
			if (input->getMouse()->left == MouseCode::HELD)
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