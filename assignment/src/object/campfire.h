//@BridgetACasey

#pragma once

#include "object/game_object.h"

class Campfire : public GameObject
{
protected:
	Campfire();

public:
	~Campfire();

	static Campfire* create();

	void update(float deltaTime) override;

	void onCollisionBeginWith(CollisionTag tag) override;
	void onCollisionEndWith(CollisionTag tag) override;

	bool getContacted();

private:
	bool contacted;
};