#include "game_object.h"

GameObject::GameObject()
{

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

void GameObject::setGameObjectTag(CollisionTag& newTag)
{
	tag = newTag;
}

CollisionTag& GameObject::getGameObjectTag()
{
	return tag;
}