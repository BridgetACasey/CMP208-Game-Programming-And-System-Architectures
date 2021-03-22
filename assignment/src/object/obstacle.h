//@BridgetACasey

#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#pragma once

#include "object/game_object.h"

class Obstacle : public GameObject
{
protected:
	Obstacle();

public:
	~Obstacle();

	static Obstacle* create();

	void onCollisionBeginWith(CollisionTag tag) override;
	void onCollisionEndWith(CollisionTag tag) override;
};

#endif