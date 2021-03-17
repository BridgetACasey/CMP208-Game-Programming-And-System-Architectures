#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <graphics/mesh_instance.h>
#include <graphics/renderer_3d.h>
#include <box2d/box2d.h>

#include "primitive_builder.h"

namespace gef
{
	class Vector4;
	class Renderer3D;
}

class PrimitiveBuilder;

enum class CollisionTag
{
	NONE = 0,
	PLAYER,
	FLOOR,
	WALL,
	COLLECTIBLE
};

class GameObject : public gef::MeshInstance
{
protected:
	GameObject();

public:
	~GameObject();

	static GameObject* create();

	void UpdateFromSimulation(const b2Body* body);
	void updateTransforms();

	void setMesh(PrimitiveBuilder* primitive_builder);
	void setBody(b2World* world);

	void buildTransform();

	gef::Vector4* getPosition();

	b2Body* getBody();

	void setGameObjectTag(CollisionTag& newTag);
	CollisionTag& getGameObjectTag();

protected:
	gef::Vector4 position;

	b2Body* body;

	CollisionTag tag;
};

#endif // _GAME_OBJECT_H