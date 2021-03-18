//@BridgetACasey

#pragma once

#include "game_object.h"

class CollisionManager
{
protected:
	CollisionManager();

public:
	~CollisionManager();

	static CollisionManager* create();

	void checkCollision();
};