#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <graphics/mesh_instance.h>
#include <graphics/renderer_3d.h>
#include <box2d/Box2D.h>

#include "primitive_builder.h"

namespace gef
{
	class Vector4;
	class Renderer3D;
}

class PrimitiveBuilder;

class GameObject : public gef::MeshInstance
{
protected:
	GameObject();

public:
	~GameObject();

	static GameObject* create();

	void SetMeshInstance(PrimitiveBuilder* primitive_builder);
	void render(gef::Renderer3D* renderer);

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	void BuildTransform();

	gef::Vector4* getPosition();
	gef::Vector4* getRotation();
	gef::Vector4* getScale();

protected:
	gef::Vector4 position;
	gef::Vector4 rotation;
	gef::Vector4 scale;
};

#endif // _GAME_OBJECT_H