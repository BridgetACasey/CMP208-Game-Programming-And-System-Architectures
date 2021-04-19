//@BridgetACasey

#pragma once

#include "button.h"

class Slider : public Button
{
protected:
	Slider(GameInput* input_);

public:
	static Slider* create(GameInput* input_);

	//Checks if the button component is still within its given range along the x-axis and adjusts its position accordingly
	void updatePosition(float deltaTime, bool usingMouse);

	//The width and height of the slider's button component
	void setButtonDimensions(float width, float height);

	//The minimum and maximum x coordinates the button component can oscillate between, as well as the y position of the entire slider object
	void setAnchorPoints(float min, float max, float y, float z);

	void setInitialPercentageValue(float initialPercentage);
	float getPercentageValue();

	float getMinAnchorPoint();
	float getMaxAnchorPoint();

	gef::Sprite* getLowerBackground();
	gef::Sprite* getUpperBackground();

private:
	float minAnchorPoint;
	float maxAnchorPoint;

	float percentageValue;

	float scrollSpeed;

	gef::Sprite lowerBackground;
	gef::Sprite upperBackground;
};