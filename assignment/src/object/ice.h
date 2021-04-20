//@BridgetACasey

#ifndef _ICE_H
#define _ICE_H

#pragma once

#include "object/game_object.h"

//Ice, one of the obstacles encountered in the level
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

#endif	//_ICE_H