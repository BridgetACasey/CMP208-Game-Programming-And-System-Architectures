//@BridgetACasey

#pragma once

class GameObject;

class InputCommand
{
public:
	virtual ~InputCommand(){}

	virtual void executeCommand(GameObject* gameObject) = 0;
};