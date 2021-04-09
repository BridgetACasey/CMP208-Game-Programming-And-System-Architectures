//@BridgetACasey

#pragma once

#include "state.h"

#include <vector>

#include "object/player.h"
#include "object/collectible.h"
#include "object/ice.h"
#include "object/lava.h"
#include "object/campfire.h"
#include "object/obstacle.h"

#include <graphics/mesh_instance.h>
#include <graphics/scene.h>
#include <object/collision_listener.h>

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
		eye = gef::Vector4(object->getPosition()->x(), eye.y(), eye.z());
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
	void DrawHUD();
	void SetupLights();
	void SetupCamera();
	
	void setupPlayer();
	void setupLava();
	void setupIce();
	void setupObstacles();
	void setupCollectibles();

	b2World* world;
	CollisionListener collision;

	Camera* camera;

	std::vector<Lava*> lava;
	std::vector<Ice*> ice;
	std::vector<Obstacle*> obstacles;
	std::vector<Collectible*> collectibles;

	Campfire* campfire;

	Player* player;

	float fps_;
};