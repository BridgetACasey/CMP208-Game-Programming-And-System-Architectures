//@BridgetACasey

#pragma once

#include "state.h"
#include "ui/button.h"

class HelpState : public State
{
protected:
	HelpState(gef::Platform& platform);

public:
	static HelpState* create(gef::Platform& platform);

	void setup() override;

	void onEnter() override;
	void onExit() override;

	void handleInput() override;
	void update(float deltaTime) override;
	void render() override;

private:
	Button* backButton;
};