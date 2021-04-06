//@BridgetACasey

#include "slider.h"

Slider::Slider(GameInput* input_) : Button(input_)
{
	minAnchorPoint = 0.0f;
	maxAnchorPoint = 0.0f;

	percentageValue = 100.0f;
}

Slider* Slider::create(GameInput* input_)
{
	return new Slider(input_);
}

void Slider::updatePosition()
{
	if (position_.x() > maxAnchorPoint - (width_ / 2.0f))
	{
		set_position(maxAnchorPoint - (width_ / 2.0f), position_.y(), position_.z());
	}

	else if (position_.x() < minAnchorPoint + (width_ / 2.0f))
	{
		set_position(minAnchorPoint + (width_ / 2.0f), position_.y(), position_.z());
	}

	//Adding an extra offset value of 0.2 to either side, otherwise the slider may get stuck
	else if(input->getMouse()->position.x > minAnchorPoint + (width_ / 2.0f) - 0.2f && input->getMouse()->position.x < maxAnchorPoint - (width_ / 2.0f) + 0.2f)
	{
		set_position(gef::Vector4(input->getMouse()->position.x, position_.y(), position_.z()));
	}

	float left = minAnchorPoint + (width_ / 2.0f);
	float right = maxAnchorPoint - (width_ / 2.0f);

	percentageValue = (position_.x() - left) / (right - left) * 100.0f;

	upperBackground.set_width((maxAnchorPoint - minAnchorPoint) * (percentageValue / 100.0f));
	upperBackground.set_position(gef::Vector4((minAnchorPoint + position_.x()) / 2.0f + ((width_ / 4.0f) * (percentageValue / 100.0f)), position_.y(), position_.z()));
}

void Slider::setAnchorPoints(float min, float max)
{
	minAnchorPoint = min;
	maxAnchorPoint = max;

	lowerBackground.set_position(gef::Vector4((maxAnchorPoint + minAnchorPoint) / 2.0f, position_.y(), position_.z()));
	lowerBackground.set_height(height_);
	lowerBackground.set_width(maxAnchorPoint - minAnchorPoint);

	upperBackground.set_position(gef::Vector4((maxAnchorPoint + minAnchorPoint) / 2.0f, position_.y(), position_.z()));
	upperBackground.set_height(height_);
	upperBackground.set_width(maxAnchorPoint - minAnchorPoint);
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