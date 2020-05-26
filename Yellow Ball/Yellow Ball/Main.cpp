#include "Application.h"

int main(int argc, char *argv[])
{
	Application app;
	if (app.Init())
		app.Loop();

	return 0;
}