//@BridgetACasey

#pragma once

#include "input_command.h"

class MoveCommand : public InputCommand
{
	void executeObjectCommand(GameObject* gameObject) override
	{
		gef::DebugOut("Moving!\n");
	}
};