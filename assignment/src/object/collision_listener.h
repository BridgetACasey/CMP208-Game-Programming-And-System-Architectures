#pragma once

#include "box2d/b2_world_callbacks.h"

//Utilises Box2D's callback system to determine when two b2 world objects are in contact, rather than looping over every object in the scene

class CollisionListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override 
	{
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		GameObject* objectA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
		GameObject* objectB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

		if (objectA)
		{
			if (objectB)
			{
				objectA->onCollisionBeginWith(objectB->getCollisionTag());
			}
		}

		if (objectB)
		{
			if (objectA)
			{
				objectB->onCollisionBeginWith(objectA->getCollisionTag());
			}
		}
	}

	void EndContact(b2Contact* contact) override
	{
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		GameObject* objectA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
		GameObject* objectB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

		if (objectA)
		{
			if (objectB)
			{
				objectA->onCollisionBeginWith(objectB->getCollisionTag());
			}
		}

		if (objectB)
		{
			if (objectA)
			{
				objectB->onCollisionBeginWith(objectA->getCollisionTag());
			}
		}
	}
};