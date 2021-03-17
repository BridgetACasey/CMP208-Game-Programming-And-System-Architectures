#ifndef _MAIN_APP_H
#define _MAIN_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include <graphics/mesh_instance.h>

#include "primitive_builder.h"
#include "input/game_input.h"
#include "object/player.h"

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

	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::Renderer3D* renderer_3d_;

	PrimitiveBuilder* primitive_builder_;
	gef::InputManager* input_manager_;
	GameInput* gameInput;

	Player* player;
	b2Body* player_body_;

	gef::Mesh* ground_mesh_;
	GameObject* ground_;
	b2Body* ground_body_;

	gef::Matrix44 projection_matrix;
	gef::Matrix44 view_matrix;

	gef::Vector4 camera_position;
	gef::Vector4 camera_target;
	gef::Vector4 camera_up;

	float fps_;
	float yPosition;

	b2World* world;
};

#endif // _SCENE_APP_H
