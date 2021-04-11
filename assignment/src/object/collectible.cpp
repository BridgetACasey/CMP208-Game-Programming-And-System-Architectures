//@BridgetACasey

#include "collectible.h"

Collectible::Collectible()
{
	collected = false;
	tag_ = CollisionTag::COLLECTIBLE;
}

Collectible::~Collectible()
{

}

Collectible* Collectible::create()
{
	return new Collectible();
}

void Collectible::update(float deltaTime)
{
	updateTransforms();

	if (collected)
	{
		body->SetEnabled(false);
		isAlive = false;
	}
}

void Collectible::onCollisionBeginWith(CollisionTag tag)
{
	if (!collected)
	{
		if (tag == CollisionTag::PLAYER)
		{
			collected = true;
		}
	}
}

void Collectible::onCollisionEndWith(CollisionTag tag)
{

}

bool Collectible::getCollected()
{
	return collected;
}
