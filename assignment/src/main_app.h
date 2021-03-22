#ifndef _MAIN_APP_H
#define _MAIN_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include <graphics/mesh_instance.h>
#include <graphics/scene.h>

#include "primitive_builder.h"
#include "input/game_input.h"
#include "object/player.h"
#include "object/obstacle.h"
#include <object/collision_listener.h>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class MainApp : public gef::Application
{
public:
	MainApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();
	void SetupCamera();
	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::Renderer3D* renderer_3d_;

	PrimitiveBuilder* primitive_builder_;
	gef::InputManager* input_manager_;

	gef::MeshInstance world_mesh_instance_;
	gef::Scene* scene_assets_;

	GameInput* gameInput;

	Player* player;
	Obstacle* ground;

	float fps_;
	float yPosition;

	b2World* world;
	CollisionListener collision;
};

#endif // _MAIN_APP_H
