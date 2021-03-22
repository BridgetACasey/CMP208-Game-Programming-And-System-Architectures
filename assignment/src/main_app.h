#ifndef _MAIN_APP_H
#define _MAIN_APP_H

#include <system/application.h>
#include <system/platform.h>

#include "state/context.h"

class MainApp : public gef::Application
{
public:
	MainApp(gef::Platform& platform);

	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();

private:
	Context* context;
};

#endif // _MAIN_APP_H
