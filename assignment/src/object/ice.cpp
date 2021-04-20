//@BridgetACasey

#include "ice.h"

Ice::Ice()
{
	collisionTag = CollisionTag::ICE;
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
		//After one full second, the ice should disappear and the player should fall
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
	//If the player moves away from the ice, the timer resets
	if (tag == CollisionTag::PLAYER)
	{
		triggered = false;
		timer = 0.0f;
	}
}