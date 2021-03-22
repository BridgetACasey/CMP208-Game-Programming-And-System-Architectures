//@BridgetACasey

#include "obstacle.h"

Obstacle::Obstacle()
{
	tag_ = CollisionTag::OBSTACLE;
}

Obstacle::~Obstacle()
{

}

Obstacle* Obstacle::create()
{
	return new Obstacle();
}

void Obstacle::onCollisionBeginWith(CollisionTag tag)
{
	if (tag == CollisionTag::PLAYER)
	{
		gef::DebugOut("Obstacle has contacted with player!");
	}
}

void Obstacle::onCollisionEndWith(CollisionTag tag)
{

}