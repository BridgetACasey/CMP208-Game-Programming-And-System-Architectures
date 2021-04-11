//@BridgetACasey

#include "parallax_background.h"
#include "state/context.h"

ParallaxBackground::ParallaxBackground(gef::Platform& platform, Context* context) : platform_(platform)
{
	context_ = context;

	setupBackgroundLayers();
}

ParallaxBackground* ParallaxBackground::create(gef::Platform& platform, Context* context)
{
	return new ParallaxBackground(platform, context);
}

void ParallaxBackground::updateBackgrounds(float deltaTime)
{
	for (int i = 0; i < 6; ++i)
	{
		layers.at(i).sprite.set_position(layers.at(i).sprite.position().x() - (layers.at(i).velocity * deltaTime), layers.at(i).sprite.position().y(), layers.at(i).sprite.position().z());
		layersCopy.at(i).sprite.set_position(layersCopy.at(i).sprite.position().x() - (layersCopy.at(i).velocity * deltaTime), layersCopy.at(i).sprite.position().y(),
			layersCopy.at(i).sprite.position().z());

		if (layers.at(i).sprite.position().x() < -(layers.at(i).sprite.width() / 2.0f))
		{
			layers.at(i).sprite.set_position(platform_.width() / 2.0f, platform_.height() / 2.0f, layers.at(i).depth);
		}

		if (layersCopy.at(i).sprite.position().x() < layersCopy.at(i).sprite.width() / 2.0f)
		{
			layersCopy.at(i).sprite.set_position(layersCopy.at(i).sprite.width() / 2.0f + platform_.width(), platform_.height() / 2.0f, layersCopy.at(i).depth);
		}
	}
}

void ParallaxBackground::renderBackgrounds()
{
	for (int i = 0; i < 6; ++i)
	{
		context_->getSpriteRenderer()->DrawSprite(layers.at(i).sprite);
		context_->getSpriteRenderer()->DrawSprite(layersCopy.at(i).sprite);
	}
}

void ParallaxBackground::setupBackgroundLayers()
{
	Layer layer;

	for (int i = 0; i < 6; ++i)
	{
		layer.sprite.set_height(platform_.height());
		layer.sprite.set_width(platform_.width());
		layer.depth = i + 2.0f;
		layer.sprite.set_position(platform_.width() / 2.0f, platform_.height() / 2.0f, layer.depth);

		layers.push_back(layer);

		layer.sprite.set_position((platform_.width() / 2.0f) + layer.sprite.width(), platform_.height() / 2.0f, layer.depth);

		layersCopy.push_back(layer);
	}

	layers.at(0).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_BACK));
	layers.at(1).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_MOUNTAINS));
	layers.at(2).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_3));
	layers.at(3).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_2));
	layers.at(4).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_1));
	layers.at(5).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUD));

	layersCopy.at(0).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_BACK));
	layersCopy.at(1).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_MOUNTAINS));
	layersCopy.at(2).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_3));
	layersCopy.at(3).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_2));
	layersCopy.at(4).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUDS_MID_1));
	layersCopy.at(5).sprite.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_CLOUD));

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