//@BridgetACasey

#include "level_state.h"
#include "context.h"

LevelState::LevelState(gef::Platform& platform) : State(platform)
{
	player = nullptr;
	campfire = nullptr;
	camera = nullptr;
	world = nullptr;
	parallax = nullptr;
}

LevelState* LevelState::create(gef::Platform& platform)
{
	return new LevelState(platform);
}

void LevelState::setup()
{
	//If the game has been completed once already, delete everything and reinstantiate it
	if (!context->getGamePlaying())
	{
		delete world;
		world = NULL;

		delete camera;
		camera = NULL;

		delete player;
		player = NULL;

		delete parallax;
		parallax = NULL;

		for (GameObject* object : map)
		{
			delete object;
		}

		map.clear();

		gef::Default3DShaderData& default_shader_data = context->getRenderer3D()->default_shader_data();
		default_shader_data.CleanUp();

		if (context->getGameWon())
		{
			context->setGameWon(false);
		}

		firstSetup = true;
	}

	if (firstSetup)
	{
		gef::DebugOut("Level: Performing first time setup!\n");

		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);
		world->SetContactListener(&collisionListener);

		setupPlayer();
		setupCampfire();

		readMapData("map-data.csv");

		setupCamera();
		setupLighting();

		sky.set_height(platform.height());
		sky.set_width(platform.width());
		sky.set_position(platform.width() / 2.0f, platform.height() / 2.0f, 1.0f);
		sky.set_texture(context->getTextureManager()->getTexture(TextureID::PARALLAX_SKY));

		parallax = ParallaxBackground::create(platform, context);

		context->getGameAudio()->playMusic(MusicID::LEVEL);
	}

	firstSetup = false;
}

void LevelState::onEnter()
{
	gef::DebugOut("Entering level\n");

	setup();

	context->setGamePlaying(true);

	player->setMoveSpeed(context->getPlayerSpeed());
	player->setJumpForce(context->getPlayerJumpForce());
}

void LevelState::onExit()
{

}

void LevelState::handleInput()
{
	context->getGameInput()->update();

	if (context->getGameInput()->getKeyboard()->IsKeyPressed(context->getGameInput()->getKeyboard()->KC_ESCAPE) ||
		context->getGameInput()->getSonyController()->buttons_pressed() == gef_SONY_CTRL_SELECT)
	{
		context->setActiveState(StateLabel::PAUSE_MENU);
	}
}

bool LevelState::update(float deltaTime)
{
	fps = 1.0f / deltaTime;

	camera->updateFollow(player);
	context->getRenderer3D()->set_view_matrix(camera->view);

	context->getGameAudio()->getListener().SetTransform(player->transform());
	context->getGameAudio()->update();

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
		context->getGameAudio()->getManager()->StopPlayingSampleVoice((Int32)SoundEffectID::FIRE);
		context->setPlayerScore(player->getCoins());
		context->setGamePlaying(false);
		context->setGameWon(true);
		context->setActiveState(StateLabel::END_SCREEN);
	}

	if (!player->getIsAlive())
	{
		context->setPlayerScore(player->getCoins());
		context->setGamePlaying(false);
		context->setGameWon(false);
		context->setActiveState(StateLabel::END_SCREEN);
	}

	context->getGameInput()->processGameObjectCommands(player);

	world->Step(deltaTime, velocityIterations, positionIterations);

	return true;
}

void LevelState::render()
{
	// draw 3d geometry
	context->getRenderer3D()->Begin(true);

	context->getRenderer3D()->DrawMesh(*player);
	context->getRenderer3D()->DrawMesh(*campfire);

	for (GameObject* object : map)
	{
		if (object->getIsAlive())
		{
			context->getRenderer3D()->DrawMesh(*object);
		}
	}

	context->getRenderer3D()->End();

	// start drawing sprites, but don't clear the frame buffer
	context->getSpriteRenderer()->Begin(false);

	context->getSpriteRenderer()->DrawSprite(sky);
	parallax->renderBackgrounds();

	if (context->getFont())
	{
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 25.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT,
			"X: %.1f   Y: %.1f", player->getPosition()->x(), player->getPosition()->y());
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 50.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT,
			"FPS: %.1f", fps);
		context->getFont()->RenderText(context->getSpriteRenderer(), gef::Vector4(925.0f, 125.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT,
			"Coins: %.1i", player->getCoins());
	}

	context->getSpriteRenderer()->End();
}

void LevelState::setupLighting()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = context->getRenderer3D()->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.35f, 0.35f, 0.5f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight point_light;
	
	point_light.set_colour(gef::Colour(0.7f, 0.7f, 0.9f, 1.0f));
	point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(point_light);
}

void LevelState::setupCamera()
{
	// projection
	camera = new Camera();

	camera->fov = gef::DegToRad(45.0f);
	camera->aspectRatio = (float)platform.width() / (float)platform.height();
	camera->projection = platform.PerspectiveProjectionFov(camera->fov, camera->aspectRatio, 0.1f, 100.0f);
	context->getRenderer3D()->set_projection_matrix(camera->projection);

	// view

	if (player)
	{
		camera->eye = gef::Vector4(0.0f, player->getPosition()->y(), 12.0f);
		camera->lookAt = gef::Vector4(0.0f, 0.0f, 0.0f);
		camera->up = gef::Vector4(0.0f, 1.0f, 0.0f);
	}

	camera->view.LookAt(camera->eye, camera->lookAt, camera->up);
	context->getRenderer3D()->set_view_matrix(camera->view);
}

void LevelState::setupPlayer()
{
	player = Player::create();
	player->setPosition(2.0f, 21.0f, 0.0f);
	player->setScale(0.5f, 0.5f, 0.5f);
	player->setMaxVelocity(b2Vec2(context->getPlayerSpeed(), context->getPlayerSpeed() / 2.0f));
	player->set_mesh(context->getMeshManager()->getMesh(MeshID::PLAYER));
	player->setBody(world, b2BodyType::b2_dynamicBody, gef::Vector4(0.4f, 0.5f, 0.5f));
	player->update(0.0f);
}

void LevelState::setupCampfire()
{
	campfire = Campfire::create();
	campfire->setPosition(125.0f, 24.75f, 0.0f);
	campfire->setScale(0.4f, 0.4f, 0.4f);
	campfire->set_mesh(context->getMeshManager()->getMesh(MeshID::CAMPFIRE));
	campfire->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(1.0f, 1.5f, 1.0f));
	campfire->update(0.0f);

	fireEmitter.Init((int)SoundEffectID::FIRE, true);
	fireEmitter.set_radius(24.0f);
	fireEmitter.set_position(*campfire->getPosition());
	context->getGameAudio()->get3D()->AddEmitter(fireEmitter);
}

void LevelState::readMapData(const char* filePath)
{
	//Parses a .csv file and loads the values into a vector to be later used to generate a map
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
	/*
	* Generates a map of game objects based on int values loaded from a .csv file.
	* 
	* Since all objects apart from the player and campfire are blocks of uniform size, it is easy to
	* design the level in 2D grid form, and load the values into a vector. It is then iterated through
	* and divided up by a given height and width, and the indexes can be used as the x and y coordinates.
	* 
	* This is much faster and easier than designing the level within the application or arranging the
	* objects by hand.
	*/

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
				object->set_mesh(context->getMeshManager()->getMesh(MeshID::SNOW));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);
				break;

			case MapObjectID::STONE_GROUND:	//These types of stone can be used to jump off
				object = Obstacle::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->setCollisionTag(CollisionTag::OBSTACLE_GROUND);
				object->set_mesh(context->getMeshManager()->getMesh(MeshID::STONE));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);
				break;

			case MapObjectID::STONE_WALL:	//These types of stone do not apply a force
				object = Obstacle::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->setCollisionTag(CollisionTag::OBSTACLE_WALL);
				object->set_mesh(context->getMeshManager()->getMesh(MeshID::STONE));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->getBody()->SetAwake(false);
				object->update(0.0f);
				break;

			case MapObjectID::ICE:
				object = Ice::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->set_mesh(context->getMeshManager()->getMesh(MeshID::ICE));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);
				break;

			case MapObjectID::LAVA:
				object = Lava::create();
				object->setPosition(x, y, 0.0f);
				object->setScale(0.1f, 0.1f, 0.1f);
				object->set_mesh(context->getMeshManager()->getMesh(MeshID::LAVA));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);
				break;

			case MapObjectID::COIN:
				object = Collectible::create();
				object->setPosition(x, y, 0.0f);
				object->set_mesh(context->getMeshManager()->getMesh(MeshID::COIN));
				object->setBody(world, b2BodyType::b2_staticBody, gef::Vector4(0.5f, 0.5f, 0.5f));
				object->update(0.0f);

				//Audio emitters that trigger when the player collects a coin
				emitter.Init((int)SoundEffectID::COLLECTED, false);
				emitter.set_radius(2.5f);
				emitter.set_position(*object->getPosition());
				context->getGameAudio()->get3D()->AddEmitter(emitter);
				break;

			default:
				object = nullptr;
			}

			//Only add the game object to the level map if its Map ID is > 0
			//Otherwise, the map would be enormous and filled with null objects where there is empty space on the map
			if (object)
			{
				map.push_back(object);
			}

			//Since the MapData vector is not 2D and the width and height of the map are passed in separately,
			//another variable must be used to keep track of the current index
			++current;
		}
	}
}