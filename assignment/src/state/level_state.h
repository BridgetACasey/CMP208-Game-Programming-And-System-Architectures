//@BridgetACasey

#ifndef _LEVEL_STATE_H
#define _LEVEL_STATE_H

#pragma once

#include "state.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "object/player.h"
#include "object/collectible.h"
#include "object/ice.h"
#include "object/lava.h"
#include "object/campfire.h"
#include "object/obstacle.h"
#include "util/parallax_background.h"

#include <object/collision_listener.h>

enum MapObjectID	//Readable way of distinguishing object types when loading in map data
{
	NONE = 0,
	SNOW,
	STONE_GROUND,
	STONE_WALL,
	ICE,
	LAVA,
	COIN
};

//A struct to bundle up all the relevant values related to the camera, so they can be more easily accessed elsewhere
struct Camera
{
	float fov;
	float aspectRatio;

	gef::Matrix44 projection;
	gef::Matrix44 view;

	gef::Vector4 eye;
	gef::Vector4 lookAt;
	gef::Vector4 up;

	//Centres on a game object and follows it around the level as it moves
	//Intended for the player, but could theoretically be used to focus on any game object
	void updateFollow(GameObject* object)
	{
		eye = gef::Vector4(object->getPosition()->x(), object->getPosition()->y(), eye.z());
		lookAt = gef::Vector4(object->getPosition()->x(), object->getPosition()->y(), lookAt.z());
		view.LookAt(eye, lookAt, up);
	}
};

//The main level state
class LevelState : public State
{
protected:
	LevelState(gef::Platform& platform);

public:
	static LevelState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	bool update(float deltaTime) override;
	void render() override;

private:
	void setupLighting();
	void setupCamera();

	void setupPlayer();
	void setupCampfire();

	void readMapData(const char* filePath);
	void generateMap(std::vector<int>& mapData, const int width, const int height);

	b2World* world;
	CollisionListener collisionListener;

	ParallaxBackground* parallax;
	gef::Sprite sky;

	Camera* camera;

	Player* player;
	Campfire* campfire;
	AudioEmitter fireEmitter;	//For the campfire sound effect

	std::vector<GameObject*> map;
};

#endif	//_LEVEL_STATE_H