#include "level_state.h"
#include "context.h"

LevelState::LevelState(gef::Platform& platform) : State(platform)
{

}

LevelState* LevelState::create(gef::Platform& platform)
{
	return new LevelState(platform);
}

void LevelState::setup()
{
	if (firstSetup)
	{
		gef::DebugOut("Level: Performing first time setup!\n");

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
		player->setMesh(context_->getPrimitiveBuilder(), gef::Vector4(0.5f, 0.5f, 0.5f));
		player->setBody(world, b2BodyType::b2_dynamicBody);
		player->updateTransforms();

		ground = Obstacle::create();
		ground->setPosition(0.0f, 0.0f, 0.0f);
		ground->setMesh(context_->getPrimitiveBuilder(), gef::Vector4(5.0f, 0.5f, 0.5f));
		ground->setBody(world, b2BodyType::b2_staticBody);
		ground->updateTransforms();

		SetupCamera();
		SetupLights();
	}

	firstSetup = false;
}

void LevelState::onEnter()
{
	gef::DebugOut("Entering level\n");

	setup();
}

void LevelState::onExit()
{

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

	context_->getGameInput()->update(player);

	yPosition = player->getBody()->GetTransform().p.y;
}

void LevelState::render()
{
	// draw 3d geometry
	context_->getRenderer3D()->Begin(true);

	context_->getRenderer3D()->DrawMesh(*ground);
	context_->getRenderer3D()->DrawMesh(world_mesh_instance_);

	// draw player
	context_->getRenderer3D()->set_override_material(&context_->getPrimitiveBuilder()->red_material());
	context_->getRenderer3D()->DrawMesh(*player);
	context_->getRenderer3D()->set_override_material(NULL);

	context_->getRenderer3D()->End();

	// start drawing sprites, but don't clear the frame buffer
	context_->getSpriteRenderer()->Begin(false);

	DrawHUD();
	context_->getSpriteRenderer()->End();
}

void LevelState::DrawHUD()
{
	if (context_->getFont())
	{
		// display frame rate
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(720.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Y: %.1f FPS: %.1f", yPosition, fps_);
	}
}

void LevelState::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = context_->getRenderer3D()->default_shader_data();

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
	context_->getRenderer3D()->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(0.0f, 4.0f, 12.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	context_->getRenderer3D()->set_view_matrix(view_matrix);
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