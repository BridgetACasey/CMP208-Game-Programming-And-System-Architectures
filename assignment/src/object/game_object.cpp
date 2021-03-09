#include "game_object.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

GameObject* GameObject::create()
{
	return nullptr;
}

void GameObject::BuildTransform()
{
	gef::Matrix44 final_, trans, rotX, rotY, rotZ, scale_;

	scale_.Scale(scale);

	rotX.RotationX(rotation.x());
	rotY.RotationY(rotation.y());
	rotZ.RotationZ(rotation.z());

	trans.SetIdentity();
	trans.SetTranslation(position);

	final_ = scale_ * rotX * rotY * rotZ * trans;

	set_transform(final_);
}

void GameObject::SetMeshInstance(PrimitiveBuilder* primitive_builder)
{

}

void GameObject::SetPosition(float x, float y, float z)
{
	position.set_x(x);
	position.set_y(y);
	position.set_z(z);
}

void GameObject::SetRotation(float x, float y, float z)
{
	rotation.set_x(x);
	rotation.set_y(y);
	rotation.set_z(z);
}

void GameObject::SetScale(float x, float y, float z)
{
	scale.set_x(x);
	scale.set_y(y);
	scale.set_z(z);
}

gef::Vector4* GameObject::getPosition()
{
	return &position;
}

gef::Vector4* GameObject::getRotation()
{
	return &rotation;
}

gef::Vector4* GameObject::getScale()
{
	return &scale;
}