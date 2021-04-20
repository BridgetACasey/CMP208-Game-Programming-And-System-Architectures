//@BridgetACasey

#ifndef _LAVA_H
#define _LAVA_H

#pragma once

#include "object/game_object.h"

//The lava object, which instantly kills the player upon contact
//Does not do anything specific on its own, as the player class is responsible for determining if it is still alive
class Lava : public GameObject
{
protected:
	Lava();

public:
	~Lava();

	static Lava* create();

	void update(float deltaTime) override;

	void onCollisionBeginWith(CollisionTag tag) override;
	void onCollisionEndWith(CollisionTag tag) override;
};

#endif	//_LAVA_H