//@BridgetACasey

#ifndef _STATE_H
#define _STATE_H

#pragma once

class State
{
protected:
	State();

public:
	~State();

	static State* create();
};

#endif