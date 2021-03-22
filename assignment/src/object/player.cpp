//@BridgetACasey

#include "player.h"

Player::Player()
{
	tag_ = CollisionTag::PLAYER;
}

Player::~Player()
{

}

Player* Player::create()
{
	return new Player();
}

void Player::onCollisionBeginWith(CollisionTag tag)
{
	if (tag == CollisionTag::OBSTACLE)
	{
		gef::DebugOut("Player has contacted with obstacle!\n");
	}

	if (tag == CollisionTag::COIN)
	{
		//Add to total coins
	}
}

void Player::onCollisionEndWith(CollisionTag tag)
{

}