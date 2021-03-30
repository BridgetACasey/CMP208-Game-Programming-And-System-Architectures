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
	checkDeath();
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
}

void Player::onCollisionEndWith(CollisionTag tag)
{

}

int Player::getCoins()
{
	return coins;
}