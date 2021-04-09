//@BridgetACasey

#pragma once

#include "object/game_object.h"

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