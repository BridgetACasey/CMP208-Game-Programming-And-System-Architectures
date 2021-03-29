//@BridgetACasey

#pragma once

#include "state.h"
#include "ui/button.h"

class EndState : public State
{
protected:
	EndState(gef::Platform& platform);

public:
	static EndState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	bool update(float deltaTime) override;
	void render() override;

	void setLastScore(int lastScore_);

private:
	int lastScore;
	int highestScore;

	Button* restartButton;
};