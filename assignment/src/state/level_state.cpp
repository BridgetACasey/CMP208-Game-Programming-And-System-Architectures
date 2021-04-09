#include "level_state.h"
#include "context.h"

LevelState::LevelState(gef::Platform& platform) : State(platform)
{
	campfire = nullptr;
	player = nullptr;
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
	if (!context_->getGamePlaying())
	{
		delete world;
		world = NULL;

		delete camera;
		camera = NULL;

		delete player;
		player = NULL;

		delete campfire;
		campfire = NULL;

		for (Collectible* coin : collectibles)
		{
			delete coin;
		}
		
		for (Ice* iceObject : ice)
		{
			delete iceObject;
		}
		
		for (Lava* lavaObject : lava)
		{
			delete lavaObject;
		}
		
		for (Obstacle* obstacle : obstacles)
		{
			delete obstacle;
		}

		collectibles.clear();
		ice.clear();
		lava.clear();
		obstacles.clear();

		gef::Default3DShaderData& default_shader_data = context_->getRenderer3D()->default_shader_data();
		default_shader_data.CleanUp();

		if (context_->getGameWon())
		{
			context_->setGameWon(false);
		}

		firstSetup = true;
	}

	if (firstSetup)
	{
		gef::DebugOut("Level: Performing first time setup!\n");

		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);
		world->SetContactListener(&collision);

		setupPlayer();
		setupCollectibles();
		setupObstacles();
		setupLava();
		setupIce();

		campfire = Campfire::create();
		campfire->setPosition(3.0f, 0.0f, 0.0f);
		campfire->setScale(0.5f, 0.5f, 0.5f);
		campfire->set_mesh(context_->getMeshManager()->getMesh(MeshID::CAMPFIRE));
		campfire->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(1.0f, 1.5f, 1.0f));
		campfire->update(0.0f);

		SetupCamera();
		SetupLights();

		context_->getGameAudio()->getListener().SetTransform(player->transform());

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

	if (context_->getGameInput()->getKeyboard()->IsKeyPressed(context_->getGameInput()->getKeyboard()->KC_ESCAPE) ||
		context_->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_SELECT)
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

	for (Collectible* coin : collectibles)
	{
		coin->update(deltaTime);
	}

	if (campfire->getContacted())
	{
		context_->setPlayerScore(player->getCoins());
		context_->setGamePlaying(false);
		context_->setGameWon(true);
		context_->setActiveState(StateLabel::END_SCREEN);
	}

	if (!player->getIsAlive())
	{
		context_->setPlayerScore(player->getCoins());
		context_->setGamePlaying(false);
		context_->setGameWon(false);
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

	context_->getRenderer3D()->DrawMesh(*campfire);

	// draw player
	context_->getRenderer3D()->DrawMesh(*player);

	for (Collectible* coin : collectibles)
	{
		if (!coin->getCollected())
		{
			context_->getRenderer3D()->DrawMesh(*coin);
		}
	}

	for (Ice* iceObject : ice)
	{
		context_->getRenderer3D()->DrawMesh(*iceObject);
	}

	for (Lava* lavaObject : lava)
	{
		context_->getRenderer3D()->DrawMesh(*lavaObject);
	}

	for (Obstacle* obstacle : obstacles)
	{
		context_->getRenderer3D()->DrawMesh(*obstacle);
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
			"X: %.1f Y: %.1f FPS: %.1f", player->getPosition()->x(), player->getPosition()->y(), fps_);

		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(775.0f, 75.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT,
			"Coins: %.1i", player->getCoins());
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
	default_point_light.set_colour(gef::Colour(0.9f, 0.7f, 0.7f, 1.0f));
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
	camera->eye = gef::Vector4(0.0f, 4.0f, 6.0f);
	camera->lookAt = gef::Vector4(0.0f, 0.0f, 0.0f);
	camera->up = gef::Vector4(0.0f, 1.0f, 0.0f);

	camera->view_matrix.LookAt(camera->eye, camera->lookAt, camera->up);
	context_->getRenderer3D()->set_view_matrix(camera->view_matrix);
}

void LevelState::setupPlayer()
{
	player = Player::create();
	player->setPosition(0.0f, 4.0f, 0.0f);
	player->setScale(0.5f, 0.5f, 0.5f);
	player->set_mesh(context_->getMeshManager()->getMesh(MeshID::PLAYER));
	player->setBody(world, b2BodyType::b2_dynamicBody, gef::Vector4(0.5f, 0.5f, 0.5f));
	player->setMoveSpeed(25.0f);
	player->setJumpForce(1200.0f);
	player->update(0.0f);
}

void LevelState::setupLava()
{
	int objectTotal = 1;

	Lava* newLava;

	for (int i = 0; i < objectTotal; ++i)
	{
		newLava = Lava::create();
		newLava->setPosition(-2.0f, 0.0f, 0.0f);
		newLava->setScale(0.1f, 0.1f, 0.1f);
		newLava->set_mesh(context_->getMeshManager()->getMesh(MeshID::LAVA));
		newLava->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
		newLava->update(0.0f);

		lava.push_back(newLava);
	}

	newLava = NULL;
}

void LevelState::setupIce()
{
	int objectTotal = 1;
	
	Ice* newIce;

	for (int i = 0; i < objectTotal; ++i)
	{
		newIce = Ice::create();
		newIce->setPosition(0.0f, 0.0f, 0.0f);
		newIce->setScale(0.1f, 0.1f, 0.1f);
		newIce->set_mesh(context_->getMeshManager()->getMesh(MeshID::ICE));
		newIce->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
		newIce->update(0.0f);

		ice.push_back(newIce);
	}

	newIce = NULL;
}

void LevelState::setupObstacles()
{
	Obstacle* snow;
	Obstacle* stone;

	snow = Obstacle::create();
	snow->setPosition(-1.0f, 0.0f, 0.0f);
	snow->setScale(0.1f, 0.1f, 0.1f);
	snow->set_mesh(context_->getMeshManager()->getMesh(MeshID::SNOW));
	snow->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
	snow->update(0.0f);

	stone = Obstacle::create();
	stone->setPosition(1.0f, 0.0f, 0.0f);
	stone->setScale(0.1f, 0.1f, 0.1f);
	stone->set_mesh(context_->getMeshManager()->getMesh(MeshID::STONE));
	stone->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
	stone->update(0.0f);

	obstacles.push_back(snow);
	obstacles.push_back(stone);
}

void LevelState::setupCollectibles()
{
	int objectTotal = 1;

	Collectible* coin;
	
	for (int i = 0; i < objectTotal; ++i)
	{
		coin = Collectible::create();
		coin->setPosition(2.0f, 3.0f, 0.0f);
		coin->setScale(2.0f, 2.0f, 1.0f);
		coin->set_mesh(context_->getMeshManager()->getMesh(MeshID::COIN));
		coin->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
		coin->update(0.0f);

		collectibles.push_back(coin);
	}

	coin = NULL;
}