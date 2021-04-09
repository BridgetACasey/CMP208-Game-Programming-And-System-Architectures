//@BridgetACasey

#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <graphics/mesh_instance.h>
#include <graphics/renderer_3d.h>
#include <box2d/box2d.h>
#include <system/debug_log.h>

#include "util/primitive_builder.h"

class PrimitiveBuilder;

enum class CollisionTag
{
	NONE = 0,
	PLAYER,
	OBSTACLE,
	COLLECTIBLE,
	LAVA,
	ICE,
	CAMPFIRE
};

class GameObject : public gef::MeshInstance
{
protected:
	GameObject();

public:
	~GameObject();

	static GameObject* create();

	virtual void update(float deltaTime);

	/*For collision events
	 Does not actually check if collisions have occurred (handled by CollisionListener),
	 only handles what happens to this GameObject after a valid collision with another GameObject
	 as determined by its CollisionTag*/
	virtual void onCollisionBeginWith(CollisionTag tag);
	virtual void onCollisionEndWith(CollisionTag tag);

	void setDefaultMesh(PrimitiveBuilder* primitive_builder, gef::Vector4& halfDimensions);
	void setBody(b2World* world, b2BodyType type, gef::Vector4& halfDimensions);

	void setPosition(float x, float y, float z);
	gef::Vector4* getPosition();

	void setRotation(float x, float y, float z);
	gef::Vector4* getRotation();

	void setScale(float x, float y, float z);
	gef::Vector4* getScale();

	b2Body* getBody();

	void setCollisionTag(CollisionTag newTag);
	CollisionTag& getCollisionTag();

	void setMoveSpeed(float moveSpeed_);
	float getMoveSpeed();

	void setJumpForce(float jumpForce_);
	float getJumpForce();

	void setCanJump(bool canJump_);
	bool getCanJump();

	void setActiveDirection(int activeDirection_);
	int getActiveDirection();

	bool getIsAlive();

protected:
	void updateTransforms();
	void checkDeathFromFalling();

	gef::Vector4 position;
	gef::Vector4 rotation;
	gef::Vector4 scale;

	b2Body* body;

	CollisionTag tag_;

	float moveSpeed;
	float jumpForce;

	bool canJump;

	int activeDirection;

	bool isAlive;
};

#endif // _GAME_OBJECT_H