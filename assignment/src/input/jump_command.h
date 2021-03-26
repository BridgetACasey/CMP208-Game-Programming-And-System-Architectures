//@BridgetACasey

#pragma once

#include "input_command.h"

class JumpCommand : public InputCommand
{
	void executeObjectCommand(GameObject* gameObject) override
	{
		gef::DebugOut("THE BIGGEST JAMP\n");
	}
};