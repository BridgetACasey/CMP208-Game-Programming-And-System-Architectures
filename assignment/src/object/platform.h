//@BridgetACasey

#ifndef _PLATFORM_H
#define _PLATFORM_H

#pragma once

#include "object/game_object.h"

class Platform : public GameObject
{
protected:
	Platform();

public:
	~Platform();

	static Platform* create();
};

#endif