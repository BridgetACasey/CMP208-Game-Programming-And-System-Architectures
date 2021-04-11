//@BridgetACasey

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

#include <graphics/mesh_instance.h>
#include <graphics/scene.h>
#include <object/collision_listener.h>

enum MapObjectID
{
	NONE = 0,
	SNOW,
	STONE_GROUND,
	STONE_WALL,
	ICE,
	LAVA,
	COIN
};

struct Camera
{
	float fov;
	float aspect_ratio;

	gef::Matrix44 projection_matrix;
	gef::Matrix44 view_matrix;

	gef::Vector4 eye;
	gef::Vector4 lookAt;
	gef::Vector4 up;

	void updateFollow(GameObject* object)
	{
		eye = gef::Vector4(object->getPosition()->x(), object->getPosition()->y(), eye.z());
		lookAt = gef::Vector4(object->getPosition()->x(), object->getPosition()->y(), lookAt.z());
		view_matrix.LookAt(eye, lookAt, up);
	}
};

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
	CollisionListener collision;
	gef::PointLight pointLight;

	ParallaxBackground* parallax;
	gef::Sprite sky;

	Camera* camera;

	Player* player;
	Campfire* campfire;

	std::vector<GameObject*> map;

	float fps_;
};