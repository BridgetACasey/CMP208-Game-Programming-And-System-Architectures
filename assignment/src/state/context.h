#pragma once

#include <map>

#include "level_state.h"
#include "menu_state.h"
#include "pause_state.h"
#include "splash_state.h"
#include "end_state.h"
#include "settings_state.h"
#include "help_state.h"

namespace gef
{
	class Platform;
}

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
	gef::PNGLoader* getPNGLoader();

	PrimitiveBuilder* getPrimitiveBuilder();
	GameInput* getGameInput();

	void setPlayerScore(int playerScore_);
	int getPlayerScore();

	void setGameComplete(bool gameComplete_);
	bool getGameComplete();

private:
	State* activeState;

	std::map<StateLabel, State*> states;

	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	gef::InputManager* input_manager_;
	gef::Font* font_;

	gef::PNGLoader pngLoader;

	PrimitiveBuilder* primitive_builder_;
	GameInput* gameInput;

	int playerScore;
	bool gameComplete;
};