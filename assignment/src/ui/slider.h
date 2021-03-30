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
	void setHorizontal(bool horizontal_);

	float getPercentageValue();

private:
	float minAnchorPoint;
	float maxAnchorPoint;

	float percentageValue;

	bool horizontal;
};