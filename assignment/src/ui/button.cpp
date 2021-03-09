//@BridgetACasey

#include "button.h"

Button::Button()
{

}

Button::~Button()
{

}

Button* Button::create()
{
	return nullptr;
}

bool Button::isHovering()
{
	if (input->getMousePosition().x >= position.x && input->getMousePosition().x <= position.x + scale.x)
	{
		if (input->getMousePosition().y >= position.y && input->getMousePosition().y <= position.y + scale.y)
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
		/* IF Interaction button is held down RETURN TRUE */

		return true;
	}

	return false;
}

void Button::SetPosition(float x, float y)
{
	position.x = x;
	position.x = y;
}

void Button::SetScale(float x, float y)
{
	scale.x = x;
	scale.x = y;
}

gef::Vector2* Button::getPosition()
{
	return &position;
}

gef::Vector2* Button::getScale()
{
	return &scale;
}