//@BridgetACasey

#include "obstacle.h"

Obstacle::Obstacle()
{
	tag_ = CollisionTag::OBSTACLE_GROUND;
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