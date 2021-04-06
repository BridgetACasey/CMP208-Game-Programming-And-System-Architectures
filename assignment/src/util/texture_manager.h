//@BridgetACasey

#pragma once

#include <graphics/texture.h>
#include <graphics/image_data.h>
#include <assets/png_loader.h>

class TextureManager
{
protected:
	TextureManager(gef::Platform& platform);

public:
	static TextureManager* create(gef::Platform& platform);

	gef::Texture* generateTexture(const char* filePath);

private:
	gef::Platform& platform_;

	gef::PNGLoader pngLoader;
};