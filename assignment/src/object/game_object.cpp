#include "game_object.h"

GameObject::GameObject()
{
	body = nullptr;
	tag_ = CollisionTag::NONE;

	moveSpeed = 1.0f;
	jumpForce = 1.0f;

	canJump = true;

	activeDirection = 1;
}

GameObject::~GameObject()
{

}

GameObject* GameObject::create()
{
	return new GameObject();
}

void GameObject::updateTransforms()
{
	if (body)
	{
		position.set_x(body->GetPosition().x);	//set object position
		position.set_y(body->GetPosition().y);
		position.set_z(0.0f);

		gef::Matrix44 transform;
		transform.RotationZ(body->GetAngle());	//set object rotation

		transform.SetTranslation(position);	//build transform matrix
		set_transform(transform);
	}
}

void GameObject::onCollisionBeginWith(CollisionTag tag)
{
	//To be populated in child classes
}

void GameObject::onCollisionEndWith(CollisionTag tag)
{
	//To be populated in child classes
}

void GameObject::setMesh(PrimitiveBuilder* primitive_builder, gef::Vector4& halfDimensions)
{
	halfDimensions_ = halfDimensions;

	gef::Mesh* mesh = primitive_builder->CreateBoxMesh(halfDimensions);
	set_mesh(mesh);
}

void GameObject::setBody(b2World* world, b2BodyType type)
{
	// create a physics body
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position = b2Vec2(position.x(), position.y());
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->CreateBody(&bodyDef);

	// create the shape
	b2PolygonShape shape;
	shape.SetAsBox(halfDimensions_.x(), halfDimensions_.y());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	b2Fixture* fixture = body->CreateFixture(&fixtureDef);
}

void GameObject::setPosition(float x, float y, float z)
{
	position.set_x(x);
	position.set_y(y);
	position.set_z(z);
}

gef::Vector4* GameObject::getPosition()
{
	return &position;
}

b2Body* GameObject::getBody()
{
	return body;
}

void GameObject::setCollisionTag(CollisionTag tag)
{
	tag_ = tag;
}

CollisionTag& GameObject::getCollisionTag()
{
	return tag_;
}

void GameObject::setMoveSpeed(float moveSpeed_)
{
	moveSpeed = moveSpeed_;
}

void GameObject::setJumpForce(float jumpForce_)
{
	jumpForce = jumpForce_;
}

float GameObject::getMoveSpeed()
{
	return moveSpeed;
}

float GameObject::getJumpForce()
{
	return jumpForce;
}

void GameObject::setCanJump(bool canJump_)
{
	canJump = canJump_;
}

bool GameObject::getCanJump()
{
	return canJump;
}

void GameObject::setActiveDirection(int activeDirection_)
{
	activeDirection = activeDirection_;
}

int GameObject::getActiveDirection()
{
	return activeDirection;
}