//@BridgetACasey

#pragma once

#include "input_command.h"
#include <system/debug_log.h>

class JumpCommand : public InputCommand
{
	void executeCommand(GameObject* gameObject) override
	{
		gef::DebugOut("THE BIGGEST JAMP\n");
	}
};