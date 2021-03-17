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

void GameObject::UpdateFromSimulation(const b2Body* body)
{
	if (body)
	{
		// setup object rotation
		gef::Matrix44 object_rotation;
		object_rotation.RotationZ(body->GetAngle());

		// setup the object translation
		gef::Vector4 object_translation(body->GetPosition().x, body->GetPosition().y, 0.0f);

		// build object transformation matrix
		gef::Matrix44 object_transform = object_rotation;
		object_transform.SetTranslation(object_translation);
		set_transform(object_transform);
	}
}

void GameObject::buildTransform()
{
	//gef::Matrix44 final_, trans, rotX, rotY, rotZ, scale_;

	//scale_.Scale(scale);

	//rotX.RotationX(rotation.x());
	//rotY.RotationY(rotation.y());
	//rotZ.RotationZ(rotation.z());

	//trans.SetIdentity();
	//trans.SetTranslation(position);

	//final_ = scale_ * rotX * rotY * rotZ * trans;

	//set_transform(final_);
}

void GameObject::setMesh(PrimitiveBuilder* primitive_builder)
{
	set_mesh(primitive_builder->GetDefaultCubeMesh());
}

void GameObject::setBody(b2World* world)
{
	// create a physics body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(170.0f, 25.0f);
	//bodyDef.linearDamping = 10.0f;

	body = world->CreateBody(&bodyDef);

	// create the shape
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	b2Fixture* fixture = body->CreateFixture(&fixtureDef);
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