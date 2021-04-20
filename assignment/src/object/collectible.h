//@BridgetACasey

#ifndef _COLLECTIBLE_H
#define _COLLECTIBLE_H

#pragma once

#include "game_object.h"

//The base class for coin objects found in the level
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

	void setBody(b2World* world, b2BodyType type, gef::Vector4& halfDimensions) override;

private:
	bool collected;
};

#endif	//_COLLECTIBLE_H