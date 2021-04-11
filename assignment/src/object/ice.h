//@BridgetACasey

#pragma once

#include "object/game_object.h"

class Ice : public GameObject
{
protected:
	Ice();

public:
	~Ice();

	static Ice* create();

	void update(float deltaTime) override;

	void onCollisionBeginWith(CollisionTag tag) override;
	void onCollisionEndWith(CollisionTag tag) override;

private:
	bool triggered;
	float timer;
};