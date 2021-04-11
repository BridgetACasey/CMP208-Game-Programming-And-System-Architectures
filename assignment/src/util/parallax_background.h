//@BridgetACasey

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

	gef::Platform& platform_;
	Context* context_;

	std::vector<Layer> layers;
	std::vector<Layer> layersCopy;
};