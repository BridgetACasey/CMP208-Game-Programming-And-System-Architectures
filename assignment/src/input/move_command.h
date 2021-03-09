//@BridgetACasey

#pragma once

#include "input_command.h"
#include <system/debug_log.h>

class MoveCommand : public InputCommand
{
	void executeCommand(GameObject* gameObject) override
	{
		gef::DebugOut("Moving!\n");
	}
};