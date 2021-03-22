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

	void setActiveState(StateLabel stateName);

	State* getActiveState();

private:
	State* activeState;

	std::map<StateLabel, State*> states;
};