//@BridgetACasey

#include "slider.h"

Slider::Slider(GameInput* input_) : Button(input_)
{
	minAnchorPoint = 0.0f;
	maxAnchorPoint = 0.0f;

	percentageValue = 100.0f;

	horizontal = true;
}

Slider* Slider::create(GameInput* input_)
{
	return new Slider(input_);
}

void Slider::updatePosition()
{
	if (isHeld())
	{
		if (horizontal)
		{
			if (position_.x() > maxAnchorPoint - (width_ / 2.0f))
			{
				set_position(maxAnchorPoint - (width_ / 2.0f), position_.y(), position_.z());
			}

			else if (position_.x() < minAnchorPoint + (width_ / 2.0f))
			{
				set_position(minAnchorPoint + (width_ / 2.0f), position_.y(), position_.z());
			}

			else
			{
				set_position(gef::Vector4(input->getMouse()->position.x, position_.y(), position_.z()));
			}

			float left = minAnchorPoint + (width_ / 2.0f);
			float right = maxAnchorPoint - (width_ / 2.0f);

			percentageValue = (position_.x() - left) / (right - left) * 100.0f;
		}

		else
		{
			if (position_.y() > maxAnchorPoint - (height_ / 2.0f))
			{
				set_position(position_.x(), maxAnchorPoint - 1.0f, position_.z());
			}

			else if (position_.y() < minAnchorPoint + (height_ / 2.0f))
			{
				set_position(position_.x(), minAnchorPoint + 1.0f, position_.z());
			}

			else
			{
				set_position(gef::Vector4(position_.x(), input->getMouse()->position.x, position_.z()));
			}

			float left = minAnchorPoint + (height_ / 2.0f);
			float right = maxAnchorPoint - (height_ / 2.0f);

			percentageValue = (position_.y() - left) / (right - left) * 100.0f;
		}
	}
}

void Slider::setAnchorPoints(float min, float max)
{
	minAnchorPoint = min;
	maxAnchorPoint = max;
}

void Slider::setHorizontal(bool horizontal_)
{
	horizontal = horizontal_;
}

float Slider::getPercentageValue()
{
	return percentageValue;
}