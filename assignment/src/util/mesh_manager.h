//@BridgetACasey

#pragma once

#include <graphics/scene.h>
#include <system/debug_log.h>

class MeshManager
{
protected:
	MeshManager(gef::Platform& platform);

public:
	static MeshManager* create(gef::Platform& platform);

	gef::Mesh* generateMesh(const char* filePath);

private:
	gef::Platform& platform_;

	gef::Scene* loadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* getMeshFromSceneAssets(gef::Scene* scene);
};