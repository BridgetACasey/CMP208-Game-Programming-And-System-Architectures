//@BridgetACasey

#include "texture_manager.h"

TextureManager::TextureManager(gef::Platform& platform) : platform_(platform)
{

}

TextureManager* TextureManager::create(gef::Platform& platform)
{
	return new TextureManager(platform);
}

gef::Texture* TextureManager::generateTexture(const char* filePath)
{
	gef::ImageData image;
	gef::Texture* texture;

	pngLoader.Load(filePath, platform_, image);
	texture = gef::Texture::Create(platform_, image);

	return texture;
}