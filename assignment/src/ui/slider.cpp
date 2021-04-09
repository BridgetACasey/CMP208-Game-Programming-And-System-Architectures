//@BridgetACasey

#include "slider.h"

Slider::Slider(GameInput* input_) : Button(input_)
{
	minAnchorPoint = 0.0f;
	maxAnchorPoint = 0.0f;

	percentageValue = 100.0f;

	scrollSpeed = 100.0f;
}

Slider* Slider::create(GameInput* input_)
{
	return new Slider(input_);
}

void Slider::updatePosition(float deltaTime, bool usingMouse)
{
	if (position_.x() > maxAnchorPoint - (width_ / 2.0f))	//Setting the button back to its maximum x value
	{
		set_position(maxAnchorPoint - (width_ / 2.0f), position_.y(), position_.z());
	}

	else if (position_.x() < minAnchorPoint + (width_ / 2.0f))	//Setting the button back to its minimum x value
	{
		set_position(minAnchorPoint + (width_ / 2.0f), position_.y(), position_.z());
	}

	else
	{
		if (usingMouse)
		{
			//Adding an extra offset value of 0.2 to either side, otherwise the slider may get stuck
			if (input->getMouse()->position.x > minAnchorPoint + (width_ / 2.0f) - 0.2f && input->getMouse()->position.x < maxAnchorPoint - (width_ / 2.0f) + 0.2f)
			{
				set_position(gef::Vector4(input->getMouse()->position.x, position_.y(), position_.z()));
			}
		}

		else
		{
			if (input->getController()->leftStick == ControllerCode::LEFT || input->getSonyController()->buttons_down() == gef_SONY_CTRL_LEFT)
			{
				set_position(gef::Vector4(position_.x() - (scrollSpeed * deltaTime), position_.y(), position_.z()));
			}

			else if (input->getController()->leftStick == ControllerCode::RIGHT || input->getSonyController()->buttons_down() == gef_SONY_CTRL_RIGHT)
			{
				set_position(gef::Vector4(position_.x() + (scrollSpeed * deltaTime), position_.y(), position_.z()));
			}
		}
	}

	float min = minAnchorPoint + (width_ / 2.0f);
	float max = maxAnchorPoint - (width_ / 2.0f);

	percentageValue = (position_.x() - min) / (max - min) * 100.0f;

	//Scaling the top portion of the slider sprites relative to the position of the button component
	upperBackground.set_width((maxAnchorPoint - minAnchorPoint) * (percentageValue / 100.0f));
	upperBackground.set_position(gef::Vector4(minAnchorPoint + (upperBackground.width() / 2.0f), position_.y(), position_.z()));
}

void Slider::setButtonDimensions(float width, float height)
{
	set_width(width);
	set_height(height);
}

void Slider::setAnchorPoints(float min, float max, float y)
{
	minAnchorPoint = min;
	maxAnchorPoint = max;

	position_.set_y(y);

	lowerBackground.set_position(gef::Vector4((maxAnchorPoint + minAnchorPoint) / 2.0f, position_.y(), position_.z()));
	lowerBackground.set_height(height_);
	lowerBackground.set_width(maxAnchorPoint - minAnchorPoint);

	upperBackground.set_position(gef::Vector4((maxAnchorPoint + minAnchorPoint) / 2.0f, position_.y(), position_.z()));
	upperBackground.set_height(height_);
	upperBackground.set_width(maxAnchorPoint - minAnchorPoint);
}

void Slider::setInitialPercentageValue(float initialPercentage)
{
	percentageValue = initialPercentage;

	float min = minAnchorPoint + (width_ / 2.0f);
	float max = maxAnchorPoint - (width_ / 2.0f);

	position_.set_x(min + ((max - min) * (percentageValue / 100.0f)));

	upperBackground.set_width((maxAnchorPoint - minAnchorPoint) * (percentageValue / 100.0f));
	upperBackground.set_position(gef::Vector4((minAnchorPoint + position_.x()) / 2.0f + ((width_ / 4.0f) * (percentageValue / 100.0f)), position_.y(), position_.z()));
}

float Slider::getPercentageValue()
{
	return percentageValue;
}

float Slider::getMinAnchorPoint()
{
	return minAnchorPoint;
}

float Slider::getMaxAnchorPoint()
{
	return maxAnchorPoint;
}

gef::Sprite* Slider::getLowerBackground()
{
	return &lowerBackground;
}

gef::Sprite* Slider::getUpperBackground()
{
	return &upperBackground;
}