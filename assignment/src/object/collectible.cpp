//@BridgetACasey

#include "collectible.h"

Collectible::Collectible()
{
	collected = false;
	collisionTag = CollisionTag::COLLECTIBLE;
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

void Collectible::setBody(b2World* world, b2BodyType type, gef::Vector4& halfDimensions)
{
	// create a physics body
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position = b2Vec2(position.x(), position.y());
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->CreateBody(&bodyDef);

	// create the shape
	b2PolygonShape shape;
	shape.SetAsBox(halfDimensions.x(), halfDimensions.y());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = true;	//Overriding this function to make the body a sensor, so the player doesn't bounce off it
	b2Fixture* fixture = body->CreateFixture(&fixtureDef);
}