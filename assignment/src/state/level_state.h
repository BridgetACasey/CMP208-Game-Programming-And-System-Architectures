//@BridgetACasey

#pragma once

#include "state.h"

#include "object/player.h"
#include "object/collectible.h"
#include "object/obstacle.h"
#include "object/trap.h"

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
	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

	b2World* world;
	CollisionListener collision;

	gef::MeshInstance world_mesh_instance_;
	gef::Scene* scene_assets_;

	Camera* camera;

	Player* player;
	Collectible* coin;
	Obstacle* ground;
	Trap* trap;

	AudioEmitter coinCollection;

	float fps_;
	float yPosition;
};