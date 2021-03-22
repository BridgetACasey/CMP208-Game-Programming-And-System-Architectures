//@BridgetACasey

#pragma once

#include <maths/vector2.h>
#include <graphics/mesh_instance.h>
#include <graphics/scene.h>

#include "util/primitive_builder.h"
#include "input/game_input.h"
#include "object/player.h"
#include "object/obstacle.h"
#include <object/collision_listener.h>

#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>

class Context;

enum class StateLabel
{
	SPLASH_SCREEN = 0,
	MAIN_MENU,
	PAUSE_MENU,
	LEVEL,
	END_SCREEN
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
	b2World* world;
	CollisionListener collision;
	GameInput* gameInput;
};