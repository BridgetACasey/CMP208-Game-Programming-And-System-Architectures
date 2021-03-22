#pragma once

#include <map>
#include <string>

#include "state.h"
#include "level_state.h"

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