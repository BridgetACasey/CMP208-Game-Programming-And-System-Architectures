//@BridgetACasey

#include "campfire.h"

Campfire::Campfire()
{
	collisionTag = CollisionTag::CAMPFIRE;
	contacted = false;
}

Campfire::~Campfire()
{

}

Campfire* Campfire::create()
{
	return new Campfire();
}

void Campfire::update(float deltaTime)
{
	updateTransforms();
}

void Campfire::onCollisionBeginWith(CollisionTag tag)
{
	if (tag == CollisionTag::PLAYER)
	{
		contacted = true;
	}
}

void Campfire::onCollisionEndWith(CollisionTag tag)
{

}

bool Campfire::getContacted()
{
	return contacted;
}