#include "game_object.h"

GameObject::GameObject()
{
	body = nullptr;
	tag_ = CollisionTag::NONE;

	velocity = b2Vec2(0.0f, 0.0f);
	maxVelocity = b2Vec2(0.0f, 0.0f);

	position = gef::Vector4(0.0f, 0.0f, 0.0f);
	rotation = gef::Vector4(0.0f, 0.0f, 0.0f);
	scale = gef::Vector4(1.0f, 1.0f, 1.0f);

	moveSpeed = 1.0f;
	jumpForce = 1.0f;

	canJump = false;

	activeDirection = 1;

	isAlive = true;
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
		gef::Matrix44 transform, translation, rotX, rotY, rotZ, scale_;

		velocity = body->GetLinearVelocity();
		
		scale_.Scale(scale);

		rotX.RotationX(rotation.x());
		rotY.RotationY(rotation.y());
		rotZ.RotationZ(rotation.z());

		position.set_x(body->GetPosition().x);
		position.set_y(body->GetPosition().y);

		translation.SetIdentity();
		translation.SetTranslation(position);

		transform = scale_ * rotX * rotY * rotZ * translation;

		set_transform(transform);
	}
}

void GameObject::checkDeathFromFalling()
{
	if (position.y() < 0.0f)
	{
		isAlive = false;
	}
}

void GameObject::update(float deltaTime)
{
	updateTransforms();
}

void GameObject::onCollisionBeginWith(CollisionTag tag)
{
	//To be populated in child classes
}

void GameObject::onCollisionEndWith(CollisionTag tag)
{
	//To be populated in child classes
}

void GameObject::setDefaultMesh(PrimitiveBuilder* primitive_builder, gef::Vector4& halfDimensions)
{
	gef::Mesh* mesh = primitive_builder->CreateBoxMesh(halfDimensions);
	set_mesh(mesh);
}

void GameObject::setBody(b2World* world, b2BodyType type, gef::Vector4& halfDimensions)
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

void GameObject::setRotation(float x, float y, float z)
{
	rotation.set_x(x);
	rotation.set_y(y);
	rotation.set_z(z);
}

gef::Vector4* GameObject::getRotation()
{
	return &rotation;
}

void GameObject::setScale(float x, float y, float z)
{
	scale.set_x(x);
	scale.set_y(y);
	scale.set_z(z);
}

gef::Vector4* GameObject::getScale()
{
	return &scale;
}

b2Body* GameObject::getBody()
{
	return body;
}

void GameObject::setMaxVelocity(b2Vec2& vel)
{
	maxVelocity = vel;
}

b2Vec2& GameObject::getMaxVelocity()
{
	return maxVelocity;
}

b2Vec2& GameObject::getVelocity()
{
	return velocity;
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

bool GameObject::getIsAlive()
{
	return isAlive;
}