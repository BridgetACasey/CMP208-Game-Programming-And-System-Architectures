//@BridgetACasey

#ifndef _SLIDER_H
#define _SLIDER_H

#pragma once

#include "button.h"

//A slider ui object, used in the settings menu mainly for changing the volume at run time
class Slider : public Button
{
protected:
	Slider(GameInput* input);

public:
	static Slider* create(GameInput* input);

	//Checks if the button component is still within its given range along the x-axis and adjusts its position accordingly
	void updatePosition(float deltaTime, bool usingMouse);

	//The width and height of the slider's button component
	void setButtonDimensions(float width, float height);

	//The minimum and maximum x coordinates the button component can oscillate between, as well as the y and z positions of the entire slider object
	void setAnchorPoints(float min, float max, float y, float z);

	//The starting value the slider sits at to determine its position before being interacted with, to prevent visual bugs
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

#endif	//_SLIDER_H