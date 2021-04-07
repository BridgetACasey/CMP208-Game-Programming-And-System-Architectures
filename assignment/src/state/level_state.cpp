#include "level_state.h"
#include "context.h"

LevelState::LevelState(gef::Platform& platform) : State(platform)
{
	ground = nullptr;
	player = nullptr;
	coin = nullptr;
	trap = nullptr;
	camera = nullptr;
	world = nullptr;

	fps_ = 0.0f;
}

LevelState* LevelState::create(gef::Platform& platform)
{
	return new LevelState(platform);
}

void LevelState::setup()
{
	if (context_->getGameComplete())
	{
		delete world;
		world = NULL;

		delete player;
		player = NULL;

		delete coin;
		coin = NULL;

		delete trap;
		trap = NULL;

		delete ground;
		ground = NULL;

		delete camera;
		camera = NULL;

		gef::Default3DShaderData& default_shader_data = context_->getRenderer3D()->default_shader_data();
		default_shader_data.CleanUp();

		context_->setGameComplete(false);
		firstSetup = true;
	}

	if (firstSetup)
	{
		gef::DebugOut("Level: Performing first time setup!\n");

		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);
		world->SetContactListener(&collision);

		player = Player::create();
		player->setPosition(0.0f, 4.0f, 0.0f);
		player->setDefaultMesh(context_->getPrimitiveBuilder(), gef::Vector4(0.5f, 0.5f, 0.5f));
		player->setBody(world, b2BodyType::b2_dynamicBody);
		player->setMoveSpeed(25.0f);
		player->setJumpForce(1200.0f);
		player->update(0.0f);

		coin = Collectible::create();
		coin->setPosition(2.0f, 3.0f, 0.0f);
		coin->setScale(2.0f, 2.0f, 1.0f);
		coin->set_mesh(context_->getMeshManager()->getMesh(MeshID::COIN));
		coin->setBody(world, b2BodyType::b2_staticBody);
		coin->update(0.0f);

		trap = Trap::create();
		trap->setPosition(-2.0f, 0.5f, 0.0f);
		trap->setRotation(-1.571f, 0.0f, 0.0f);
		trap->setScale(0.025f, 0.025f, 0.025f);
		trap->set_mesh(context_->getMeshManager()->getMesh(MeshID::TRAP));
		trap->setBody(world, b2BodyType::b2_staticBody);
		trap->update(0.0f);

		ground = Obstacle::create();
		ground->setPosition(0.0f, 0.0f, 0.0f);
		ground->setDefaultMesh(context_->getPrimitiveBuilder(), gef::Vector4(5.0f, 0.5f, 0.5f));
		ground->setBody(world, b2BodyType::b2_staticBody);
		ground->update(0.0f);

		SetupCamera();
		SetupLights();

		context_->getGameAudio()->getListener().SetTransform(player->transform());

		coinCollection.Init((int)SoundEffectID::COLLECTED, false);
		coinCollection.set_position(*coin->getPosition());
		coinCollection.set_radius(1.5f);
		context_->getGameAudio()->get3D()->AddEmitter(coinCollection);

		context_->getGameAudio()->playMusic(MusicID::LEVEL);
	}

	firstSetup = false;
}

void LevelState::onEnter()
{
	gef::DebugOut("Entering level\n");

	setup();

	context_->setGamePlaying(true);
}

void LevelState::onExit()
{

}

void LevelState::handleInput()
{
	context_->getGameInput()->update();

	if (context_->getGameInput()->getKeyboard()->IsKeyPressed(context_->getGameInput()->getKeyboard()->KC_ESCAPE))
	{
		context_->setActiveState(StateLabel::PAUSE_MENU);
	}
}

bool LevelState::update(float deltaTime)
{
	context_->getGameAudio()->getListener().SetTransform(player->transform());
	context_->getGameAudio()->update();

	camera->updateFollow(player);
	context_->getRenderer3D()->set_view_matrix(camera->view_matrix);

	fps_ = 1.0f / deltaTime;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float timeStep = 1.0f / 60.0f;

	// update object visuals from simulation data
	// don't have to update the ground visuals as it is static

	player->update(deltaTime);
	coin->update(deltaTime);
	trap->update(deltaTime);

	if (!player->getIsAlive())
	{
		context_->setPlayerScore(player->getCoins());
		context_->setGamePlaying(false);
		context_->setGameComplete(true);
		context_->setActiveState(StateLabel::END_SCREEN);
	}

	context_->getGameInput()->processGameObjectCommands(player);

	world->Step(deltaTime, velocityIterations, positionIterations);

	return true;
}

void LevelState::render()
{
	// draw 3d geometry
	context_->getRenderer3D()->Begin(true);

	context_->getRenderer3D()->DrawMesh(*ground);

	// draw player
	context_->getRenderer3D()->DrawMesh(*player);

	if (!coin->getCollected())
	{
		context_->getRenderer3D()->DrawMesh(*coin);
	}

	if (!trap->getTriggered())
	{
		context_->getRenderer3D()->DrawMesh(*trap);
	}

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
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(650.0f, 500.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT,
			"Y: %.1f FPS: %.1f Coins: %.1i", player->getPosition()->y(), fps_, player->getCoins());
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
	camera = new Camera();

	camera->fov = gef::DegToRad(45.0f);
	camera->aspect_ratio = (float)platform_.width() / (float)platform_.height();
	camera->projection_matrix = platform_.PerspectiveProjectionFov(camera->fov, camera->aspect_ratio, 0.1f, 100.0f);
	context_->getRenderer3D()->set_projection_matrix(camera->projection_matrix);

	// view
	camera->eye = gef::Vector4(0.0f, 4.0f, 12.0f);
	camera->lookAt = gef::Vector4(0.0f, 0.0f, 0.0f);
	camera->up = gef::Vector4(0.0f, 1.0f, 0.0f);

	camera->view_matrix.LookAt(camera->eye, camera->lookAt, camera->up);
	context_->getRenderer3D()->set_view_matrix(camera->view_matrix);
}