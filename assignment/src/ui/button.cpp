//@BridgetACasey

#include "button.h"

Button::Button(GameInput* input_)
{
	input = input_;

	inactive = nullptr;
	hovering = nullptr;
}

Button* Button::create(GameInput* input_)
{
	return new Button(input_);
}

bool Button::isHovering()
{
	if (input->getMouse()->position.x > position_.x() - (width() / 2.0f) && input->getMouse()->position.x < position_.x() + (width() / 2.0f))
	{
		if (input->getMouse()->position.y > position_.y() - (height() / 2.0f) && input->getMouse()->position.y < position_.y() + (height() / 2.0f))
		{
			set_texture(hovering);
			return true;
		}
	}

	set_texture(inactive);

	return false;
}

bool Button::isClicked()
{
	if (isHovering())
	{
		if (input->getMouse()->left == MouseCode::PRESSED)
		{
			return true;
		}
	}

	return false;
}

bool Button::isHeld()
{
	if (isHovering())
	{
		if (input->getMouse()->left == MouseCode::HELD)
		{
			return true;
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