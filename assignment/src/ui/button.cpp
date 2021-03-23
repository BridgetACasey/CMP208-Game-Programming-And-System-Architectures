//@BridgetACasey

#include "button.h"

Button::Button(GameInput* input_)
{
	input = input_;
}

Button* Button::create(GameInput* input_)
{
	return new Button(input_);
}

bool Button::isHovering()
{
	if (input->getMousePosition().x > position_.x() - (width() / 2.0f) && input->getMousePosition().x < position_.x() + (width() / 2.0f))
	{
		if (input->getMousePosition().y > position_.y() - (height() / 2.0f) && input->getMousePosition().y < position_.y() + (height() / 2.0f))
		{
			return true;
		}
	}

	return false;
}

bool Button::isClicked()
{
	if (isHovering())
	{
		//Check if left mouse button has been clicked
		//return true
	}

	return false;
}