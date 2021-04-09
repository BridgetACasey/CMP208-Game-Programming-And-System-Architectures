//@BridgetACasey

#include "ice.h"

Ice::Ice()
{
	tag_ = CollisionTag::ICE;
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
}

void Ice::onCollisionBeginWith(CollisionTag tag)
{

}

void Ice::onCollisionEndWith(CollisionTag tag)
{

}