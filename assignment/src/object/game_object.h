//@BridgetACasey

#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <graphics/mesh_instance.h>
#include <graphics/renderer_3d.h>
#include <box2d/box2d.h>
#include <system/debug_log.h>

#include "util/primitive_builder.h"

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
	OBSTACLE,
	COIN
};

class GameObject : public gef::MeshInstance
{
protected:
	GameObject();

public:
	~GameObject();

	static GameObject* create();

	void updateTransforms();

	/*For collision events
	 Does not actually check if collisions have occurred (handled by CollisionListener),
	 only handles what happens to this GameObject after a valid collision with another GameObject
	 as determined by its CollisionTag*/
	virtual void onCollisionBeginWith(CollisionTag tag);
	virtual void onCollisionEndWith(CollisionTag tag);

	void setMesh(PrimitiveBuilder* primitive_builder, gef::Vector4& halfDimensions);
	void setBody(b2World* world, b2BodyType type);

	void setPosition(float x, float y, float z);
	gef::Vector4* getPosition();

	b2Body* getBody();

	void setCollisionTag(CollisionTag newTag);
	CollisionTag& getCollisionTag();

protected:
	gef::Vector4 position;
	gef::Vector4 halfDimensions_;

	b2Body* body;

	CollisionTag tag_;
};

#endif // _GAME_OBJECT_H