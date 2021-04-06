//@BridgetACasey

#pragma once

#include "game_object.h"

class Trap : public GameObject
{
protected:
	Trap();

public:
	~Trap();

	static Trap* create();

	void update(float deltaTime) override;

	void onCollisionBeginWith(CollisionTag tag) override;
	void onCollisionEndWith(CollisionTag tag) override;

	bool getTriggered();

private:
	bool triggered;
};