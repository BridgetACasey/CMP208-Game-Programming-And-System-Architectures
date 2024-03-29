//@BridgetACasey

#include "mesh_manager.h"

MeshManager::MeshManager(gef::Platform& pltfrm) : platform(pltfrm)
{
	initMeshes();
}

MeshManager* MeshManager::create(gef::Platform& platform)
{
	return new MeshManager(platform);
}

gef::Mesh* MeshManager::getMesh(MeshID id)
{
	return meshes[id];
}

void MeshManager::initMeshes()
{
	//Initialises all the meshes so they can be easily retrieved in other parts of the program
	meshes[MeshID::PLAYER] = generateMesh("player.scn");
	meshes[MeshID::COIN] = generateMesh("coin.scn");
	meshes[MeshID::LAVA] = generateMesh("lava.scn");
	meshes[MeshID::SNOW] = generateMesh("snow.scn");
	meshes[MeshID::ICE] = generateMesh("ice.scn");
	meshes[MeshID::STONE] = generateMesh("stone.scn");
	meshes[MeshID::CAMPFIRE] = generateMesh("campfire.scn");
}

gef::Mesh* MeshManager::generateMesh(const char* filePath)
{
	gef::Mesh* mesh = nullptr;

	// load the scene asset in from the .scn
	gef::Scene* asset;

	asset = loadSceneAssets(platform, filePath);

	if (asset)
	{
		mesh = getMeshFromSceneAssets(asset);
	}

	else
	{
		gef::DebugOut("Scene file %s failed to load\n", asset);
	}

	return mesh;
}

gef::Scene* MeshManager::loadSceneAssets(gef::Platform& platform, const char* filename)
{
	gef::Scene* scene = new gef::Scene();

	if (scene->ReadSceneFromFile(platform, filename))
	{
		// if scene file loads successful
		// create material and mesh resources from the scene data
		scene->CreateMaterials(platform);
		scene->CreateMeshes(platform);
	}
	else
	{
		delete scene;
		scene = NULL;
	}

	return scene;
}

gef::Mesh* MeshManager::getMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}