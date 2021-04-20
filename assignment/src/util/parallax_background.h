//@BridgetACasey

#ifndef _PARALLAX_BACKGROUND_H
#define _PARALLAX_BACKGROUND_H

#pragma once

#include <vector>

#include <system/platform.h>
#include <graphics/sprite.h>

class Context;

struct Layer
{
	float depth;
	float velocity;
	gef::Sprite sprite;
};

//Handles the calculations for parallax scrolling in the level state
class ParallaxBackground
{
protected:
	ParallaxBackground(gef::Platform& platform, Context* context);

public:
	static ParallaxBackground* create(gef::Platform& platform, Context* context);

	void updateBackgrounds(float deltaTime);

	void renderBackgrounds();

private:
	void setupBackgroundLayers();

	gef::Platform& platform;
	Context* context;

	//Stores two identical groups of layers, then resets their positions when they reach the edge of the screen
	std::vector<Layer> layers;
	std::vector<Layer> layersCopy;
};

#endif	//_PARALLAX_BACKGROUND_H