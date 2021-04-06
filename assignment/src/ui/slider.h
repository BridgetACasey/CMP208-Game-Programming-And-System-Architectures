//@BridgetACasey

#pragma once

#include "button.h"

class Slider : public Button
{
protected:
	Slider(GameInput* input_);

public:
	static Slider* create(GameInput* input_);

	void updatePosition();

	void setAnchorPoints(float min, float max);

	float getPercentageValue();

	float getMinAnchorPoint();
	float getMaxAnchorPoint();

	gef::Sprite* getLowerBackground();
	gef::Sprite* getUpperBackground();

private:
	float minAnchorPoint;
	float maxAnchorPoint;

	float percentageValue;

	gef::Sprite lowerBackground;
	gef::Sprite upperBackground;
};