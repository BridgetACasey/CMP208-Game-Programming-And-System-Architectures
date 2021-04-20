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

//Similar to a game state manager, stores all of the key objects that each state needs
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

	void setPlayerScore(int score);
	int getPlayerScore();

	void setPlayerSpeed(float speed);
	float getPlayerSpeed();

	void setPlayerJumpForce(float force);
	float getPlayerJumpForce();

	float getMaxPlayerSpeed();
	float getMaxPlayerJumpForce();

	void setGameWon(bool won);
	bool getGameWon();

	void setGamePlaying(bool playing);
	bool getGamePlaying();

private:
	State* activeState;

	std::map<StateLabel, State*> states;

	gef::SpriteRenderer* spriteRenderer;
	gef::Renderer3D* renderer3D;
	gef::InputManager* inputManager;
	gef::Font* font;

	PrimitiveBuilder* primitiveBuilder;

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