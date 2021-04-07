//@BridgetACasey

#pragma once

#include <map>

#include <graphics/scene.h>
#include <system/debug_log.h>

enum class MeshID
{
	NONE = -1,
	PLAYER,
	COIN,
	TRAP
};

class MeshManager
{
protected:
	MeshManager(gef::Platform& platform);

public:
	static MeshManager* create(gef::Platform& platform);

	gef::Mesh* getMesh(MeshID id);

private:
	void initMeshes();
	gef::Mesh* generateMesh(const char* filePath);

	gef::Scene* loadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* getMeshFromSceneAssets(gef::Scene* scene);

	gef::Platform& platform_;

	std::map<MeshID, gef::Mesh*> meshes;
};