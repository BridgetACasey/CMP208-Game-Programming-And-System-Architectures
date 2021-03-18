//@BridgetACasey

#include "player.h"

Player::Player()
{
	tag = CollisionTag::PLAYER;
}

Player::~Player()
{

}

Player* Player::create()
{
	return new Player();
}