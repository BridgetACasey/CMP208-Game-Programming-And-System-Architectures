//@BridgetACasey

#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#pragma once

class StateMachine
{
protected:
	StateMachine();

public:
	~StateMachine();

	static StateMachine* create();
};

#endif