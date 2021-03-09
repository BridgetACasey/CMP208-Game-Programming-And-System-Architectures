//@BridgetACasey

#include "texture_manager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

TextureManager* TextureManager::create()
{
	return nullptr;
}

void TextureManager::cleanUpTextures()
{
	for (auto& texture : gameTextures)
	{
		delete texture.second;
	}
}

gef::Texture* TextureManager::getTexture(const std::string& filename, gef::Platform& platform)
{
	if (gameTextures.find(filename) == gameTextures.end())
	{
		loadTexture(filename, platform);
	}

	return gameTextures[filename];
}

bool TextureManager::unloadTexture(const std::string& filename)
{
	gef::Texture* texture = gameTextures[filename];

	gameTextures.erase(filename);

	if (!texture)
	{
		return false;
	}

	delete texture;

	texture = nullptr;

	return true;
}

void TextureManager::loadTexture(const std::string& filename, gef::Platform& platform)
{
	gef::ImageData imageData;
	gef::PNGLoader pngLoader;

	pngLoader.Load(filename.c_str(), platform, imageData);

	gameTextures[filename] = gef::Texture::Create(platform, imageData);
}