//@BridgetACasey

#include "lava.h"

Lava::Lava()
{
	collisionTag = CollisionTag::LAVA;
}

Lava::~Lava()
{

}

Lava* Lava::create()
{
	return new Lava();
}

void Lava::update(float deltaTime)
{
	updateTransforms();
}

void Lava::onCollisionBeginWith(CollisionTag tag)
{

}

void Lava::onCollisionEndWith(CollisionTag tag)
{

}