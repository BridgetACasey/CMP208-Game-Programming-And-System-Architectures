//@BridgetACasey

#ifndef _PLAYER_H
#define _PLAYER_H

#pragma once

#include "object/game_object.h"

//Represents the player
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
	int coins;	//The player's score, equivalent to how many coins have been collected in the level
};

#endif	//_PLAYER_H