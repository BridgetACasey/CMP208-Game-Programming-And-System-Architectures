//@BridgetACasey

#include "texture_manager.h"

TextureManager::TextureManager(gef::Platform& platform) : platform_(platform)
{
	initTextures();
}

TextureManager* TextureManager::create(gef::Platform& platform)
{
	return new TextureManager(platform);
}

void TextureManager::initTextures()
{
	textures[TextureID::GAME_TITLE] = generateTexture("sprites/game_title.png");

	textures[TextureID::SPLASH_BACKGROUND] = generateTexture("sprites/splash_screen.png");
	textures[TextureID::MENU_BACKGROUND] = generateTexture("sprites/background_glacial_mountains.png");
	textures[TextureID::MENU_BACKGROUND_ALT] = generateTexture("sprites/background_glacial_mountains_lightened.png");
	textures[TextureID::END_WIN_BACKGROUND] = generateTexture("sprites/background_glacial_mountains_warm.png");
	textures[TextureID::END_LOSE_BACKGROUND] = generateTexture("sprites/cave_blue.png");
	textures[TextureID::HELP_SCREEN_BACKGROUND] = generateTexture("sprites/help_screen.png");

	textures[TextureID::PARALLAX_CLOUD] = generateTexture("sprites/cloud_lonely.png");
	textures[TextureID::PARALLAX_CLOUDS_BACK] = generateTexture("sprites/clouds_bg.png");
	textures[TextureID::PARALLAX_CLOUDS_MID_1] = generateTexture("sprites/clouds_mg_1.png");
	textures[TextureID::PARALLAX_CLOUDS_MID_2] = generateTexture("sprites/clouds_mg_2.png");
	textures[TextureID::PARALLAX_CLOUDS_MID_3] = generateTexture("sprites/clouds_mg_3.png");
	textures[TextureID::PARALLAX_MOUNTAINS] = generateTexture("sprites/glacial_mountains.png");
	textures[TextureID::PARALLAX_SKY] = generateTexture("sprites/sky.png");

	textures[TextureID::PLAY_BUTTON] = generateTexture("sprites/play_button.png");
	textures[TextureID::SETTINGS_BUTTON] = generateTexture("sprites/settings_button.png");
	textures[TextureID::HELP_BUTTON] = generateTexture("sprites/controls_button.png");
	textures[TextureID::QUIT_BUTTON] = generateTexture("sprites/quit_button.png");
	textures[TextureID::BACK_BUTTON] = generateTexture("sprites/back_button.png");
	textures[TextureID::CONTINUE_BUTTON] = generateTexture("sprites/continue_button.png");
	textures[TextureID::RESUME_BUTTON] = generateTexture("sprites/resume_button.png");
	textures[TextureID::MENU_BUTTON] = generateTexture("sprites/menu_button.png");
	textures[TextureID::NEW_GAME_BUTTON] = generateTexture("sprites/new_game_button.png");
	textures[TextureID::MUSIC_BUTTON] = generateTexture("sprites/music_button.png");
	textures[TextureID::GEAR_BUTTON] = generateTexture("sprites/gear_button.png");

	textures[TextureID::PLAY_BUTTON_COL] = generateTexture("sprites/play_button_col.png");
	textures[TextureID::SETTINGS_BUTTON_COL] = generateTexture("sprites/settings_button_col.png");
	textures[TextureID::HELP_BUTTON_COL] = generateTexture("sprites/controls_button_col.png");
	textures[TextureID::QUIT_BUTTON_COL] = generateTexture("sprites/quit_button_col.png");
	textures[TextureID::BACK_BUTTON_COL] = generateTexture("sprites/back_button_col.png");
	textures[TextureID::CONTINUE_BUTTON_COL] = generateTexture("sprites/continue_button_col.png");
	textures[TextureID::RESUME_BUTTON_COL] = generateTexture("sprites/resume_button_col.png");
	textures[TextureID::MENU_BUTTON_COL] = generateTexture("sprites/menu_button_col.png");
	textures[TextureID::NEW_GAME_BUTTON_COL] = generateTexture("sprites/new_game_button_col.png");
	textures[TextureID::MUSIC_BUTTON_COL] = generateTexture("sprites/music_button_col.png");
	textures[TextureID::GEAR_BUTTON_COL] = generateTexture("sprites/gear_button_col.png");

	textures[TextureID::SLIDER_BOTTOM] = generateTexture("sprites/slider_bar_bottom.png");
	textures[TextureID::SLIDER_TOP] = generateTexture("sprites/slider_bar_top.png");
}

gef::Texture* TextureManager::getTexture(TextureID id)
{
	return textures[id];
}

gef::Texture* TextureManager::generateTexture(const char* filePath)
{
	gef::ImageData image;
	gef::Texture* texture;

	pngLoader.Load(filePath, platform_, image);
	texture = gef::Texture::Create(platform_, image);

	return texture;
}