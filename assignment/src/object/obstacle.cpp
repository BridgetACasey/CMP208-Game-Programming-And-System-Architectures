//@BridgetACasey

#include "obstacle.h"

Obstacle::Obstacle()
{
	collisionTag = CollisionTag::OBSTACLE_GROUND;	//By default, the player can jump off this object type
}

Obstacle::~Obstacle()
{

}

Obstacle* Obstacle::create()
{
	return new Obstacle();
}

void Obstacle::update(float deltaTime)
{
	updateTransforms();
}

void Obstacle::onCollisionBeginWith(CollisionTag tag)
{

}

void Obstacle::onCollisionEndWith(CollisionTag tag)
{

}