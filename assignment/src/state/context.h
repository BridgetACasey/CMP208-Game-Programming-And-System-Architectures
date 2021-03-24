#pragma once

#include <map>

#include "level_state.h"
#include "menu_state.h"
#include "pause_state.h"
#include "splash_state.h"

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

	PrimitiveBuilder* getPrimitiveBuilder();
	GameInput* getGameInput();

private:
	State* activeState;

	std::map<StateLabel, State*> states;

	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	gef::InputManager* input_manager_;
	gef::Font* font_;

	PrimitiveBuilder* primitive_builder_;
	GameInput* gameInput;
};