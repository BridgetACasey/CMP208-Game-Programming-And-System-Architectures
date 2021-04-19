#include "level_state.h"
#include "context.h"

LevelState::LevelState(gef::Platform& platform) : State(platform)
{
	player = nullptr;
	campfire = nullptr;
	camera = nullptr;
	world = nullptr;
	parallax = nullptr;

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

		for (GameObject* object : map)
		{
			delete object;
		}

		map.clear();

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
		setupCampfire();

		readMapData("map-data.csv");

		setupCamera();
		setupLighting();

		sky.set_height(platform_.height());
		sky.set_width(platform_.width());
		sky.set_position(platform_.width() / 2.0f, platform_.height() / 2.0f, 1.0f);
		sky.set_texture(context_->getTextureManager()->getTexture(TextureID::PARALLAX_SKY));

		parallax = ParallaxBackground::create(platform_, context_);

		//context_->getGameAudio()->playMusic(MusicID::LEVEL);
	}

	firstSetup = false;
}

void LevelState::onEnter()
{
	gef::DebugOut("Entering level\n");

	setup();

	context_->setGamePlaying(true);

	player->setMoveSpeed(context_->getPlayerSpeed());
	player->setJumpForce(context_->getPlayerJumpForce());
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
	camera->updateFollow(player);
	context_->getRenderer3D()->set_view_matrix(camera->view_matrix);

	context_->getGameAudio()->getListener().SetTransform(player->transform());
	context_->getGameAudio()->update();

	pointLight.set_position(gef::Vector4(player->getPosition()->x(), player->getPosition()->y(), player->getPosition()->z()));

	fps_ = 1.0f / deltaTime;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float timeStep = 1.0f / 60.0f;

	// update object visuals from simulation data

	parallax->updateBackgrounds(deltaTime);
	player->update(deltaTime);

	for (GameObject* object : map)
	{
		object->update(deltaTime);
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

	context_->getRenderer3D()->DrawMesh(*player);
	context_->getRenderer3D()->DrawMesh(*campfire);

	for (GameObject* object : map)
	{
		if (object->getIsAlive())
		{
			context_->getRenderer3D()->DrawMesh(*object);
		}
	}

	context_->getRenderer3D()->End();

	// start drawing sprites, but don't clear the frame buffer
	context_->getSpriteRenderer()->Begin(false);

	context_->getSpriteRenderer()->DrawSprite(sky);
	parallax->renderBackgrounds();

	if (context_->getFont())
	{
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(925.0f, 25.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT,
			"VX: %.1f   VY: %.1f   AV: %.1f", player->getVelocity().x, player->getVelocity().y, player->getBody()->GetAngularVelocity());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT,
			"X: %.1f   Y: %.1f", player->getPosition()->x(), player->getPosition()->y());
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(925.0f, 75.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT,
			"FPS: %.1f", fps_);
		context_->getFont()->RenderText(context_->getSpriteRenderer(), gef::Vector4(925.0f, 125.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT,
			"Coins: %.1i", player->getCoins());
	}

	context_->getSpriteRenderer()->End();
}

void LevelState::setupLighting()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = context_->getRenderer3D()->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.35f, 0.35f, 0.5f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	pointLight.set_colour(gef::Colour(0.7f, 0.7f, 0.9f, 1.0f));
	pointLight.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(pointLight);
}

void LevelState::setupCamera()
{
	// projection
	camera = new Camera();

	camera->fov = gef::DegToRad(45.0f);
	camera->aspect_ratio = (float)platform_.width() / (float)platform_.height();
	camera->projection_matrix = platform_.PerspectiveProjectionFov(camera->fov, camera->aspect_ratio, 0.1f, 100.0f);
	context_->getRenderer3D()->set_projection_matrix(camera->projection_matrix);

	// view

	if (player)
	{
		camera->eye = gef::Vector4(0.0f, player->getPosition()->y(), 12.0f);
		camera->lookAt = gef::Vector4(0.0f, 0.0f, 0.0f);
		camera->up = gef::Vector4(0.0f, 1.0f, 0.0f);
	}

	camera->view_matrix.LookAt(camera->eye, camera->lookAt, camera->up);
	context_->getRenderer3D()->set_view_matrix(camera->view_matrix);
}

void LevelState::setupPlayer()
{
	player = Player::create();
	//player->setPosition(2.0f, 21.0f, 0.0f);
	player->setPosition(120.0f, 23.0f, 0.0f);
	player->setScale(0.5f, 0.5f, 0.5f);
	player->setMaxVelocity(b2Vec2(context_->getPlayerSpeed(), context_->getPlayerSpeed() / 2.0f));
	player->set_mesh(context_->getMeshManager()->getMesh(MeshID::PLAYER));
	player->setBody(world, b2BodyType::b2_dynamicBody, gef::Vector4(0.4f, 0.5f, 0.5f));
	player->update(0.0f);
}

void LevelState::setupCampfire()
{
	campfire = Campfire::create();
	campfire->setPosition(125.0f, 24.75f, 0.0f);
	campfire->setScale(0.4f, 0.4f, 0.4f);
	campfire->set_mesh(context_->getMeshManager()->getMesh(MeshID::CAMPFIRE));
	campfire->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(1.0f, 1.5f, 1.0f));
	campfire->update(0.0f);
}

void LevelState::readMapData(const char* filePath)
{
	std::string line, value;
	std::ifstream mapFile;
	std::vector<int> mapData;

	if (filePath)
	{
		mapFile.open(filePath);

		if (!mapFile.is_open())
		{
			std::cerr << "Error: failed to open '" << filePath << "'.\n";
			return;
		}
	}

	while (std::getline(mapFile, line))	
	{
		std::stringstream s(line);

		while (getline(s, value, ','))
		{
			mapData.push_back(std::stoi(value));
		}
	}

	generateMap(mapData, 128, 32);
}

void LevelState::generateMap(std::vector<int>& mapData, const int width, const int height)
{
	GameObject* object = nullptr;
	AudioEmitter emitter;

	int current = 0;

	for (int y = height; y > 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			switch (mapData.at(current))
			{
			case MapObjectID::SNOW:
				object = Obstacle::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->set_mesh(context_->getMeshManager()->getMesh(MeshID::SNOW));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);
				break;

			case MapObjectID::STONE_GROUND:
				object = Obstacle::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->setCollisionTag(CollisionTag::OBSTACLE_GROUND);
				object->set_mesh(context_->getMeshManager()->getMesh(MeshID::STONE));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);
				break;

			case MapObjectID::STONE_WALL:
				object = Obstacle::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->setCollisionTag(CollisionTag::OBSTACLE_WALL);
				object->set_mesh(context_->getMeshManager()->getMesh(MeshID::STONE));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				//object->getBody()->SetAwake(false);
				object->update(0.0f);
				break;

			case MapObjectID::ICE:
				object = Ice::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->set_mesh(context_->getMeshManager()->getMesh(MeshID::ICE));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);
				break;

			case MapObjectID::LAVA:
				object = Lava::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->set_mesh(context_->getMeshManager()->getMesh(MeshID::LAVA));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);
				break;

			case MapObjectID::COIN:
				object = Collectible::create();
				object->setPosition(x, y, 0.0f);
				object->set_mesh(context_->getMeshManager()->getMesh(MeshID::COIN));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);

				emitter.Init((int)SoundEffectID::COLLECTED, false);
				emitter.set_radius(3.0f);
				emitter.set_position(*object->getPosition());
				context_->getGameAudio()->get3D()->AddEmitter(emitter);
				break;

			default:
				object = nullptr;
			}

			if (object)
			{
				map.push_back(object);
			}

			++current;
		}
	}
}