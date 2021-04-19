//@BridgetACasey

#ifndef _STATE_H
#define _STATE_H

#pragma once

#include <system/platform.h>
#include <system/debug_log.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>

#include "util/primitive_builder.h"
#include "util/texture_manager.h"
#include "util/mesh_manager.h"
#include "input/game_input.h"
#include "audio/game_audio.h"

class Context;

enum class StateLabel
{
	SPLASH_SCREEN = 0,
	MAIN_MENU,
	PAUSE_MENU,
	LEVEL,
	END_SCREEN,
	SETTINGS,
	HELP
};

class State
{
protected:
	State(gef::Platform& platform) : platform_(platform) { context_ = nullptr; }

public:
	virtual ~State() = default;

	virtual void setup() = 0;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void handleInput() = 0;
	virtual bool update(float deltaTime) = 0;
	virtual void render() = 0;

	void setContext(Context* context) { this->context_ = context; }

protected:
	float fps_;
	
	Context* context_;

	gef::Platform& platform_;

	bool firstSetup = true;
};

#endif	//_STATE_H