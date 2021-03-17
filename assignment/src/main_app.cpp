#include "main_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>


MainApp::MainApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	camera_position(gef::Vector4::kZero),
	camera_target(gef::Vector4::kZero),
	camera_up(gef::Vector4::kZero)
{
	projection_matrix.SetIdentity();
	view_matrix.SetIdentity();
}

void MainApp::Init()
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

	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);

	player = Player::create();
	//player->setMesh(primitive_builder_);
	//player->setBody(world);
	//player->UpdateFromSimulation(player->getBody());

	// setup the mesh for the player
	player->set_mesh(primitive_builder_->GetDefaultCubeMesh());

	// create a physics body for the player
	b2BodyDef player_body_def;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(0.0f, 4.0f);

	player_body_ = world->CreateBody(&player_body_def);

	// create the shape for the player
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.5f, 0.5f);

	// create the fixture
	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	// create the fixture on the rigid body
	player_body_->CreateFixture(&player_fixture_def);

	// update visuals from simulation data
	player->UpdateFromSimulation(player_body_);

	InitFont();

	SetupCamera();
	SetupLights();

	ground_ = GameObject::create();

	gef::Vector4 ground_half_dimensions(5.0f, 0.5f, 0.5f);

	// setup the mesh for the ground
	ground_mesh_ = primitive_builder_->CreateBoxMesh(ground_half_dimensions);
	ground_->set_mesh(ground_mesh_);

	// create a physics body
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(0.0f, 0.0f);

	ground_body_ = world->CreateBody(&body_def);

	// create the shape
	b2PolygonShape shape;
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	// create the fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;

	// create the fixture on the rigid body
	ground_body_->CreateFixture(&fixture_def);

	// update visuals from simulation data
	ground_->UpdateFromSimulation(ground_body_);
}

void MainApp::CleanUp()
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

bool MainApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float timeStep = 1.0f / 60.0f;

	world->Step(frame_time, velocityIterations, positionIterations);

	// update object visuals from simulation data
	player->UpdateFromSimulation(player_body_);

	gameInput->update(player);

	yPosition = player_body_->GetTransform().p.y;

	// don't have to update the ground visuals as it is static

	// collision detection
	// get the head of the contact list
	b2Contact* contact = world->GetContactList();
	// get contact count
	int contact_count = world->GetContactCount();

	for (int contact_num = 0; contact_num < contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			// DO COLLISION RESPONSE HERE
		}

		// Get next contact point
		contact = contact->GetNext();
	}

	return true;
}

void MainApp::Render()
{
	// setup camera

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

	// draw 3d geometry
	renderer_3d_->Begin();

	renderer_3d_->DrawMesh(*ground_);

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
void MainApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void MainApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void MainApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Y: %.1f FPS: %.1f", yPosition, fps_);
	}
}

void MainApp::SetupLights()
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

void MainApp::SetupCamera()
{
	projection_matrix = platform_.PerspectiveProjectionFov(gef::DegToRad(46.8f), (float)platform_.width() / (float)platform_.height(), 0.1f, 10.0f);

	camera_position = gef::Vector4(0.0f, 1.0f, 5.0f);
	camera_target = gef::Vector4(0.0f, 0.0f, 0.0f);
	camera_up = gef::Vector4(0.0f, 1.0f, 0.0f);

	view_matrix.LookAt(camera_position, camera_target, camera_up);
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