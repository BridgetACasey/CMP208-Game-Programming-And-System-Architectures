//@BridgetACasey

#ifndef _CONTEXT_H
#define _CONTEXT_H

#pragma once

#include <map>

#include "level_state.h"
#include "menu_state.h"
#include "pause_state.h"
#include "splash_state.h"
#include "end_state.h"
#include "settings_state.h"
#include "help_state.h"

class Context
{
public:
	Context(gef::Platform& platform);

	~Context();

	void setupStateComponents(gef::Platform& platform);

	void setActiveState(StateLabel stateName);

	State* getActiveState();

	gef::SpriteRenderer* getSpriteRenderer();
	gef::Renderer3D* getRenderer3D();
	gef::Font* getFont();

	PrimitiveBuilder* getPrimitiveBuilder();
	GameInput* getGameInput();
	GameAudio* getGameAudio();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();

	void setPlayerScore(int playerScore_);
	int getPlayerScore();

	void setPlayerSpeed(float playerSpeed_);
	float getPlayerSpeed();

	void setPlayerJumpForce(float playerJumpForce_);
	float getPlayerJumpForce();

	float getMaxPlayerSpeed();
	float getMaxPlayerJumpForce();

	void setGameWon(bool gameWon_);
	bool getGameWon();

	void setGamePlaying(bool gamePlaying_);
	bool getGamePlaying();

private:
	State* activeState;

	std::map<StateLabel, State*> states;

	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	gef::InputManager* input_manager_;
	gef::Font* font_;

	PrimitiveBuilder* primitive_builder_;
	TextureManager* textureManager;
	MeshManager* meshManager;
	GameInput* gameInput;
	GameAudio* gameAudio;

	int playerScore;

	float playerSpeed;
	float playerJumpForce;
	float maxPlayerSpeed;
	float maxPlayerJumpForce;

	bool gameWon;
	bool gamePlaying;
};

#endif	//_CONTEXT_H