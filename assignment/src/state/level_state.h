//@BridgetACasey

#pragma once

#include "state.h"

class LevelState : public State
{
protected:
	LevelState(gef::Platform& platform);

public:
	static LevelState* create(gef::Platform& platform);

	void CleanUp();

	void init() override;

	void handleInput() override;
	void update(float deltaTime) override;
	void render() override;

	void onEnter() override;
	void onExit() override;

private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();
	void SetupCamera();
	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

	gef::MeshInstance world_mesh_instance_;
	gef::Scene* scene_assets_;

	Player* player;
	Obstacle* ground;

	float fps_;
	float yPosition;
};