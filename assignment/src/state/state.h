//@BridgetACasey

#pragma once

#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>

#include "util/primitive_builder.h"
#include "input/game_input.h"

class Context;

enum class StateLabel
{
	SPLASH_SCREEN = 0,
	MAIN_MENU,
	PAUSE_MENU,
	LEVEL
};

class State
{
protected:
	State(gef::Platform& platform) : platform_(platform) {}

public:
	virtual ~State() = default;

	virtual void init() = 0;

	virtual void handleInput() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	void setContext(Context* context) { this->context_ = context; }

protected:
	Context* context_;

	gef::Platform& platform_;

	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	gef::InputManager* input_manager_;
	gef::Font* font_;

	PrimitiveBuilder* primitive_builder_;
	GameInput* gameInput;
};