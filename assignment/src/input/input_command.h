//@BridgetACasey

#pragma once

#include <system/debug_log.h>

class GameObject;

class InputCommand
{
public:
	virtual ~InputCommand() = default;

	virtual void executeObjectCommand(GameObject* gameObject) = 0;
};