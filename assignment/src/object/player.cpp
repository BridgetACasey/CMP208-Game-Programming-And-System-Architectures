//@BridgetACasey

#include "player.h"

Player::Player()
{
	collisionTag = CollisionTag::PLAYER;
	coins = 0;
}

Player::~Player()
{

}

Player* Player::create()
{
	return new Player();
}

void Player::update(float deltaTime)
{
	updateTransforms();
	checkDeathFromFalling();
}

void Player::setBody(b2World* world, b2BodyType type, gef::Vector4& halfDimensions)
{
	// create a physics body
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position = b2Vec2(position.x(), position.y());
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_p = b2Vec2(0.0f, 0.0f);
	shape.m_radius = halfDimensions.x();

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	b2Fixture* fixture = body->CreateFixture(&fixtureDef);
}

void Player::onCollisionBeginWith(CollisionTag tag)
{
	if (tag == CollisionTag::COLLECTIBLE)
	{
		coins += 1;
	}

	if (tag == CollisionTag::OBSTACLE_GROUND || tag == CollisionTag::ICE)
	{
		canJump = true;
	}

	if(tag == CollisionTag::LAVA)
	{
		isAlive = false;
	}
}

void Player::onCollisionEndWith(CollisionTag tag)
{

}

int Player::getCoins()
{
	return coins;
}