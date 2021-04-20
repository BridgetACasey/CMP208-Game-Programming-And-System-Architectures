//@BridgetACasey

#ifndef _INPUT_COMMAND_H
#define _INPUT_COMMAND_H

#pragma once

#include <system/debug_log.h>

class GameObject;

//The base command class for GameObject-related input commands
class InputCommand
{
public:
	virtual ~InputCommand() = default;

	virtual void executeObjectCommand(GameObject* gameObject) = 0;
};

#endif	//_INPUT_COMMAND_H