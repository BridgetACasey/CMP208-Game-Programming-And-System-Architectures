//@BridgetACasey

#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#pragma once

#include <map>

#include <graphics/texture.h>
#include <graphics/image_data.h>
#include <assets/png_loader.h>

enum class TextureID
{
	NONE = -1,
	GAME_TITLE,
	SPLASH_BACKGROUND,
	MENU_BACKGROUND,
	MENU_BACKGROUND_ALT,
	HELP_SCREEN_BACKGROUND,
	PARALLAX_CLOUD,
	PARALLAX_CLOUDS_BACK,
	PARALLAX_CLOUDS_MID_1,
	PARALLAX_CLOUDS_MID_2,
	PARALLAX_CLOUDS_MID_3,
	PARALLAX_MOUNTAINS,
	PARALLAX_SKY,
	END_WIN_BACKGROUND,
	END_LOSE_BACKGROUND,
	PLAY_BUTTON,
	SETTINGS_BUTTON,
	HELP_BUTTON,
	QUIT_BUTTON,
	BACK_BUTTON,
	CONTINUE_BUTTON,
	RESUME_BUTTON,
	MENU_BUTTON,
	NEW_GAME_BUTTON,
	MUSIC_BUTTON,
	GEAR_BUTTON,
	PLAY_BUTTON_COL,
	SETTINGS_BUTTON_COL,
	HELP_BUTTON_COL,
	QUIT_BUTTON_COL,
	BACK_BUTTON_COL,
	CONTINUE_BUTTON_COL,
	RESUME_BUTTON_COL,
	MENU_BUTTON_COL,
	NEW_GAME_BUTTON_COL,
	MUSIC_BUTTON_COL,
	GEAR_BUTTON_COL,
	SLIDER_BOTTOM,
	SLIDER_TOP
};

//Loads in and manages all the required textures from .png files, similiar in function to the MeshManager class
class TextureManager
{
protected:
	TextureManager(gef::Platform& platform);

public:
	static TextureManager* create(gef::Platform& platform);

	gef::Texture* getTexture(TextureID id);

private:
	void initTextures();
	gef::Texture* generateTexture(const char* filePath);

	gef::Platform& platform;

	gef::PNGLoader pngLoader;

	std::map<TextureID, gef::Texture*> textures;
};

#endif	//_TEXTURE_MANAGER_H