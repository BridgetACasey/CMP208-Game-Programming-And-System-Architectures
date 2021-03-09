//@BridgetACasey

#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#pragma once

#include <string>
#include <unordered_map>

#include <graphics/texture.h>
#include <graphics/image_data.h>
#include <assets/png_loader.h>

class TextureManager
{
protected:
	TextureManager();

public:
	~TextureManager();

	static TextureManager* create();

	void cleanUpTextures();

	void loadTexture(const std::string& filename, gef::Platform& platform);
	bool unloadTexture(const std::string& filename);

	gef::Texture* getTexture(const std::string& filename, gef::Platform& platform);

private:
	std::unordered_map<std::string, gef::Texture*> gameTextures;
};

#endif