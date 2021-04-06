//@BridgetACasey

#include "trap.h"

Trap::Trap()
{
	triggered = false;
	tag_ = CollisionTag::TRAP;
}

Trap::~Trap()
{
}

Trap* Trap::create()
{
	return new Trap();
}

void Trap::update(float deltaTime)
{
	updateTransforms();
}

void Trap::onCollisionBeginWith(CollisionTag tag)
{
	if (tag == CollisionTag::PLAYER)
	{
		triggered = true;
	}
}

void Trap::onCollisionEndWith(CollisionTag tag)
{

}

bool Trap::getTriggered()
{
	return triggered;
}