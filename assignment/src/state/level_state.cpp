#include "level_state.h"

LevelState::LevelState(gef::Platform& platform) : State(platform)
{

}

LevelState* LevelState::create(gef::Platform& platform)
{
	return new LevelState(platform);
}

void LevelState::init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	input_manager_ = gef::InputManager::Create(platform_);

	// make sure if there is a panel to detect touch input, then activate it
	if (input_manager_ && input_manager_->touch_manager() && (input_manager_->touch_manager()->max_num_panels() > 0))
	{
		input_manager_->touch_manager()->EnablePanel(0);
	}

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	gameInput = GameInput::create(platform_, input_manager_);

	// load the assets in from the .scn
	const char* scene_asset_filename = "world.scn";
	scene_assets_ = LoadSceneAssets(platform_, scene_asset_filename);
	if (scene_assets_)
	{
		world_mesh_instance_.set_mesh(GetMeshFromSceneAssets(scene_assets_));
	}
	else
	{
		gef::DebugOut("Scene file %s failed to load\n", scene_asset_filename);
	}

	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);
	world->SetContactListener(&collision);

	player = Player::create();
	player->setPosition(0.0f, 4.0f, 0.0f);
	player->setMesh(primitive_builder_, gef::Vector4(0.5f, 0.5f, 0.5f));
	player->setBody(world, b2BodyType::b2_dynamicBody);
	player->updateTransforms();

	ground = Obstacle::create();
	ground->setPosition(0.0f, 0.0f, 0.0f);
	ground->setMesh(primitive_builder_, gef::Vector4(5.0f, 0.5f, 0.5f));
	ground->setBody(world, b2BodyType::b2_staticBody);
	ground->updateTransforms();

	InitFont();

	SetupCamera();
	SetupLights();
}

void LevelState::handleInput()
{

}

void LevelState::update(float deltaTime)
{
	fps_ = 1.0f / deltaTime;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float timeStep = 1.0f / 60.0f;

	world->Step(deltaTime, velocityIterations, positionIterations);

	// update object visuals from simulation data
	// don't have to update the ground visuals as it is static
	player->updateTransforms();

	gameInput->update(player);

	yPosition = player->getBody()->GetTransform().p.y;
}

void LevelState::render()
{
	// draw 3d geometry
	renderer_3d_->Begin();

	renderer_3d_->DrawMesh(*ground);
	renderer_3d_->DrawMesh(world_mesh_instance_);

	// draw player
	renderer_3d_->set_override_material(&primitive_builder_->red_material());
	renderer_3d_->DrawMesh(*player);
	renderer_3d_->set_override_material(NULL);

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);

	DrawHUD();
	sprite_renderer_->End();
}

void LevelState::onEnter()
{

}

void LevelState::onExit()
{

}

void LevelState::CleanUp()
{
	CleanUpFont();

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;
}

void LevelState::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void LevelState::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void LevelState::DrawHUD()
{
	if (font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(720.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Y: %.1f FPS: %.1f", yPosition, fps_);
	}
}

void LevelState::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void LevelState::SetupCamera()
{
	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(0.0f, 4.0f, 12.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);
}

gef::Scene* LevelState::LoadSceneAssets(gef::Platform& platform, const char* filename)
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

gef::Mesh* LevelState::GetMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}

/*
void MainApp::ProcessTouchInput()
{
	const gef::TouchInputManager* touch_input = input_manager_->touch_manager();
	if (touch_input && (touch_input->max_num_panels() > 0))
	{
		// get the active touches for this panel
		const gef::TouchContainer& panel_touches = touch_input->touches(0);

		// go through the touches
		for (gef::ConstTouchIterator touch = panel_touches.begin(); touch != panel_touches.end(); ++touch)
		{
			// if active touch id is -1, then we are not currently processing a touch
			if (active_touch_id_ == -1)
			{
				// check for the start of a new touch
				if (touch->type == gef::TT_NEW)
				{
					active_touch_id_ = touch->id;

					// do any processing for a new touch here
					// we're just going to record the position of the touch
					touch_position_ = touch->position;
				}
			}
			else if (active_touch_id_ == touch->id)
			{
				// we are processing touch data with a matching id to the one we are looking for
				if (touch->type == gef::TT_ACTIVE)
				{
					// update an active touch here
					// we're just going to record the position of the touch
					touch_position_ = touch->position;
				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// the touch we are tracking has been released
					// perform any actions that need to happen when a touch is released here
					// we're not doing anything here apart from resetting the active touch id
					active_touch_id_ = -1;
				}
			}
		}
	}
}
*/