#include <platform/vita/system/platform_vita.h>
#include "main_app.h"

unsigned int sceLibcHeapSize = 128*1024*1024;	// Sets up the heap area size as 128MiB.

int main(void)
{
	// initialisation
	gef::PlatformVita platform;

	MainApp myApp(platform);
	myApp.Run();

	return 0;
}