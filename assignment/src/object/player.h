//@BridgetACasey

#ifndef _PLAYER_H
#define _PLAYER_H

#pragma once

#include "object/game_object.h"

class Player : public GameObject
{
protected:
	Player();

public:
	~Player();

	static Player* Create();
};

#endif