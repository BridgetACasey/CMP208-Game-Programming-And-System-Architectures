//@BridgetACasey

#pragma once

#include "game_object.h"

class Collectible : public GameObject
{
protected:
	Collectible();

public:
	~Collectible();

	static Collectible* create();

	void onCollisionBeginWith(CollisionTag tag) override;
	void onCollisionEndWith(CollisionTag tag) override;

	bool getCollectible();

private:
	bool collectible;
};