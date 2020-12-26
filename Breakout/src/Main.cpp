#include "bkout.h"

#include "System/Application.h"

int main()
{
	Breakout::Application* app = new Breakout::Application();

	app->Start();
	app->Run();
	app->Stop();

	delete app;
}