//@BridgetACasey

#ifndef _PLATFORM_OBJECT_H
#define _PLATFORM_OBJECT_H

#pragma once

#include "object/game_object.h"

class PlatformObject : public GameObject
{
protected:
	PlatformObject();

public:
	~PlatformObject();

	static PlatformObject* create();
};

#endif