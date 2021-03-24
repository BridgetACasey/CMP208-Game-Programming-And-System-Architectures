//@BridgetACasey

#pragma once

#include "state.h"

#include "object/player.h"
#include "object/obstacle.h"

#include <graphics/mesh_instance.h>
#include <graphics/scene.h>
#include <object/collision_listener.h>

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
	void update(float deltaTime) override;
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

	Player* player;
	Obstacle* ground;

	float fps_;
	float yPosition;
};