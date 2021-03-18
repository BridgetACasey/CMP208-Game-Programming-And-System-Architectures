//BridgetACasey

#include "collision_manager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

CollisionManager* CollisionManager::create()
{
	return new CollisionManager();
}

void CollisionManager::checkCollision()
{
	// collision detection
	// get the head of the contact list

	/*
	b2Contact* contact = world->GetContactList();
	// get contact count
	int contact_count = world->GetContactCount();

	for (int contact_num = 0; contact_num < contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			// DO COLLISION RESPONSE HERE
		}

		// Get next contact point
		contact = contact->GetNext();
	}
	*/
}