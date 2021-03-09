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

gef::Texture* TextureManager::getTexture(const std::string& filePath, gef::Platform& platform)
{
	if (gameTextures.find(filePath) == gameTextures.end())
	{
		loadTexture(filePath, platform);
	}

	return gameTextures[filePath];
}

bool TextureManager::unloadTexture(const std::string& filePath)
{
	gef::Texture* texture = gameTextures[filePath];

	gameTextures.erase(filePath);

	if (!texture)
	{
		return false;
	}

	delete texture;

	texture = nullptr;

	return true;
}

void TextureManager::loadTexture(const std::string& filePath, gef::Platform& platform)
{
	gef::ImageData imageData;
	gef::PNGLoader pngLoader;

	pngLoader.Load(filePath.c_str(), platform, imageData);

	gameTextures[filePath] = gef::Texture::Create(platform, imageData);
}