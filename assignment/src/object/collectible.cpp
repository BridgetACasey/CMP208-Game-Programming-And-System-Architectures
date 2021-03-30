//@BridgetACasey

#include "collectible.h"

Collectible::Collectible()
{
	collectible = true;
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

	if (!collectible)
	{
		body->SetEnabled(false);
	}
}

void Collectible::onCollisionBeginWith(CollisionTag tag)
{
	if (collectible)
	{
		if (tag == CollisionTag::PLAYER)
		{
			collectible = false;
		}
	}
}

void Collectible::onCollisionEndWith(CollisionTag tag)
{

}

bool Collectible::getCollectible()
{
	return collectible;
}
