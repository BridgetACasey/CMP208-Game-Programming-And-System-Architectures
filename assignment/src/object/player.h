//@BridgetACasey

#ifndef _PLAYER_H
#define _PLAYER_H

#pragma once

#include "object/game_object.h"

class Player : public GameObject
{
protected:
	Player();

public:
	~Player();

	static Player* create();

	void update(float deltaTime) override;

	void setBody(b2World* world, b2BodyType type, gef::Vector4& halfDimensions) override;

	void onCollisionBeginWith(CollisionTag tag) override;
	void onCollisionEndWith(CollisionTag tag) override;

	int getCoins();

private:
	int coins;
};

#endif