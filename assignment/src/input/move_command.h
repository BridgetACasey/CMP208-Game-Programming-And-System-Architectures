//@BridgetACasey

#pragma once

#include "input_command.h"
#include "object/game_object.h"

#include <maths/math_utils.h>

class MoveCommand : public InputCommand
{
	void executeObjectCommand(GameObject* gameObject) override
	{
		gameObject->getBody()->ApplyForceToCenter(move, true);
	}

protected:
	b2Vec2 move = b2Vec2(0.0f, 0.0f);
};

class MoveLeftCommand : public MoveCommand
{
	void executeObjectCommand(GameObject* gameObject) override
	{
		gameObject->setActiveDirection(-1);
		gameObject->setRotation(gameObject->getRotation()->x(), gef::DegToRad(-90.0f), gameObject->getRotation()->z());
		move = b2Vec2(-gameObject->getMoveSpeed(), 0.0f);

		if (gameObject->getVelocity().x > -(gameObject->getMaxVelocity().x) && gameObject->getVelocity().x < gameObject->getMaxVelocity().x)
		{
			gameObject->getBody()->ApplyForceToCenter(move, true);
		}
	}
};

class MoveRightCommand : public MoveCommand
{
	void executeObjectCommand(GameObject* gameObject) override
	{
		gameObject->setActiveDirection(1);
		gameObject->setRotation(gameObject->getRotation()->x(), gef::DegToRad(90.0f), gameObject->getRotation()->z());
		move = b2Vec2(gameObject->getMoveSpeed(), 0.0f);

		if (gameObject->getVelocity().x > -(gameObject->getMaxVelocity().x) && gameObject->getVelocity().x < gameObject->getMaxVelocity().x)
		{
			gameObject->getBody()->ApplyForceToCenter(move, true);
		}
	}
};

class SprintCommand : public MoveCommand
{
	void executeObjectCommand(GameObject* gameObject) override
	{
		move = b2Vec2(gameObject->getActiveDirection() * gameObject->getMoveSpeed() * 0.5f, 0.0f);
		gameObject->getBody()->ApplyForceToCenter(move, true);
	}
};

class JumpCommand : public MoveCommand
{
	void executeObjectCommand(GameObject* gameObject) override
	{
		if (gameObject->getCanJump())
		{
			if (gameObject->getVelocity().y > -(gameObject->getMaxVelocity().y) && gameObject->getVelocity().y < gameObject->getMaxVelocity().y)
			{
				gameObject->setCanJump(false);
				move = b2Vec2(0.0f, gameObject->getJumpForce());
				gameObject->getBody()->ApplyForceToCenter(move, true);
			}
		}
	}
};