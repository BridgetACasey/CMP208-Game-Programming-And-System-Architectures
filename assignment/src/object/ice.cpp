//@BridgetACasey

#include "ice.h"

Ice::Ice()
{
	tag_ = CollisionTag::ICE;
	triggered = false;
	timer = 0.0f;
}

Ice::~Ice()
{

}

Ice* Ice::create()
{
	return new Ice();
}

void Ice::update(float deltaTime)
{
	updateTransforms();

	if (triggered)
	{
		if (timer > 1.0f)
		{
			body->SetEnabled(false);
			isAlive = false;
		}

		timer += 1.0f * deltaTime;
	}
}

void Ice::onCollisionBeginWith(CollisionTag tag)
{
	if (tag == CollisionTag::PLAYER)
	{
		triggered = true;
	}
}

void Ice::onCollisionEndWith(CollisionTag tag)
{
	if (tag == CollisionTag::PLAYER)
	{
		triggered = false;
		timer = 0.0f;
	}
}