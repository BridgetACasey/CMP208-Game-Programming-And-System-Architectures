//@BridgetACasey

#include "parallax_background.h"
#include "state/context.h"

ParallaxBackground::ParallaxBackground(gef::Platform& pltfrm, Context* cntxt) : platform(pltfrm), context(cntxt)
{
	setupBackgroundLayers();
}

ParallaxBackground* ParallaxBackground::create(gef::Platform& platform, Context* context)
{
	return new ParallaxBackground(platform, context);
}

void ParallaxBackground::updateBackgrounds(float deltaTime)
{
	//Scrolls each of the background images along at their respective speeds
	for (int i = 0; i < 6; ++i)
	{
		layers.at(i).sprite.set_position(layers.at(i).sprite.position().x() - (layers.at(i).velocity * deltaTime), layers.at(i).sprite.position().y(), layers.at(i).sprite.position().z());
		layersCopy.at(i).sprite.set_position(layersCopy.at(i).sprite.position().x() - (layersCopy.at(i).velocity * deltaTime), layersCopy.at(i).sprite.position().y(),
			layersCopy.at(i).sprite.position().z());

		//If a sprite moves too far off the edge of the screen, reset its position
		if (layers.at(i).sprite.position().x() < -(layers.at(i).sprite.width() / 2.0f))
		{
			layers.at(i).sprite.set_position(platform.width() / 2.0f, platform.height() / 2.0f, layers.at(i).depth);
		}

		if (layersCopy.at(i).sprite.position().x() < layersCopy.at(i).sprite.width() / 2.0f)
		{
			layersCopy.at(i).sprite.set_position(layersCopy.at(i).sprite.width() / 2.0f + platform.width(), platform.height() / 2.0f, layersCopy.at(i).depth);
		}
	}
}

void ParallaxBackground::renderBackgrounds()
{
	for (int i = 0; i < 6; ++i)
	{
		context->getSpriteRenderer()->DrawSprite(layers.at(i).sprite);
		context->getSpriteRenderer()->DrawSprite(layersCopy.at(i).sprite);
	}
}

void ParallaxBackground::setupBackgroundLayers()
{
	Layer layer;

	//Initialises the starting values for each layer
	for (int i = 0; i < 6; ++i)
	{
		layer.sprite.set_height(platform.height());
		layer.sprite.set_width(platform.width());
		layer.depth = i + 2.0f;
		layer.sprite.set_position(platform.width() / 2.0f, platform.height() / 2.0f, layer.depth);

		layers.push_back(layer);

		layer.sprite.set_position((platform.width() / 2.0f) + layer.sprite.width(), platform.height() / 2.0f, layer.depth);

		layersCopy.push_back(layer);
	}

	layers.at(0).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_BACK));
	layers.at(1).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_MOUNTAINS));
	layers.at(2).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_3));
	layers.at(3).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_2));
	layers.at(4).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_1));
	layers.at(5).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUD));

	layersCopy.at(0).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_BACK));
	layersCopy.at(1).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_MOUNTAINS));
	layersCopy.at(2).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_3));
	layersCopy.at(3).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_2));
	layersCopy.at(4).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_1));
	layersCopy.at(5).sprite.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUD));

	layers.at(0).velocity = 5.0f;
	layers.at(1).velocity = 10.0f;
	layers.at(2).velocity = 15.0f;
	layers.at(3).velocity = 20.0f;
	layers.at(4).velocity = 25.0f;
	layers.at(5).velocity = 30.0f;

	layersCopy.at(0).velocity = 5.0f;
	layersCopy.at(1).velocity = 10.0f;
	layersCopy.at(2).velocity = 15.0f;
	layersCopy.at(3).velocity = 20.0f;
	layersCopy.at(4).velocity = 25.0f;
	layersCopy.at(5).velocity = 30.0f;
}