//@BridgetACasey

#ifndef _COLLECTIBLE_H
#define _COLLECTIBLE_H

#pragma once

#include "game_object.h"

class Collectible : public GameObject
{
protected:
	Collectible();

public:
	~Collectible();

	static Collectible* create();

	void update(float deltaTime) override;

	void onCollisionBeginWith(CollisionTag tag) override;
	void onCollisionEndWith(CollisionTag tag) override;

	bool getCollected();

private:
	bool collected;
};

#endif	//_COLLECTIBLE_H