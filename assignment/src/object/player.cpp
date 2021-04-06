//@BridgetACasey

#include "player.h"

Player::Player()
{
	tag_ = CollisionTag::PLAYER;
	coins = 0;
}

Player::~Player()
{

}

Player* Player::create()
{
	return new Player();
}

void Player::update(float deltaTime)
{
	updateTransforms();
	checkDeathFromFalling();
}

void Player::onCollisionBeginWith(CollisionTag tag)
{
	if (tag == CollisionTag::COLLECTIBLE)
	{
		coins += 1;
	}

	if (tag == CollisionTag::OBSTACLE)
	{
		canJump = true;
	}

	if(tag == CollisionTag::TRAP)
	{
		isAlive = false;
	}
}

void Player::onCollisionEndWith(CollisionTag tag)
{

}

int Player::getCoins()
{
	return coins;
}