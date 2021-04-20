//@BridgetACasey

#ifndef _STATE_H
#define _STATE_H

#pragma once

/*
* Header files are included in the base state class instead of being copied into context
* or child state classes to avoid duplication.
*/
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

enum class StateLabel	//For switching between states in a more readable way
{
	SPLASH_SCREEN = 0,
	MAIN_MENU,
	PAUSE_MENU,
	LEVEL,
	END_SCREEN,
	SETTINGS,
	HELP
};

//A purely virtual class that all states inherit from
class State
{
protected:
	State(gef::Platform& pltfrm) : platform(pltfrm) { context = nullptr; }

public:
	virtual ~State() = default;

	virtual void setup() = 0;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void handleInput() = 0;
	virtual bool update(float deltaTime) = 0;
	virtual void render() = 0;

	void setContext(Context* cntxt) { this->context = cntxt; }

protected:
	gef::Platform& platform;

	Context* context;

	float fps = 0.0f;

	/*
	* Used to determine if objects need to be created.
	* They cannot be created in the state's constructor, as many objects rely on a reference to context,
	* which is only passed to the class upon it becoming the active state.
	*/
	bool firstSetup = true;
};

#endif	//_STATE_H