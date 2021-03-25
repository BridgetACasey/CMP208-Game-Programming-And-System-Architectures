//@BridgetACasey

#include "button.h"

Button::Button(GameInput* input_)
{
	input = input_;

	setInactiveColour(0xfffffff);
	setHoveringColour(0xffffffff);
	setClickedColour(0xffffffff);
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
			set_colour(hoveringColour);
			return true;
		}
	}

	set_colour(inactiveColour);
	return false;
}

bool Button::isClicked()
{
	if (isHovering())
	{
		set_colour(clickedColour);

		if (input->getMouse()->left == MouseCode::PRESSED)
		{
			return true;
		}
	}

	return false;
}

void Button::setInactiveColour(UInt32 inactiveColour_)
{
	inactiveColour = inactiveColour_;
}

void Button::setHoveringColour(UInt32 hoveringColour_)
{
	hoveringColour = hoveringColour_;
}

void Button::setClickedColour(UInt32 clickedColour_)
{
	clickedColour = clickedColour_;
}