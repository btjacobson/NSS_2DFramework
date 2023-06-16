#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"

#include "managers/Asset_Manager.h"
#include "managers/Entity_Manager.h"
#include "managers/State_Manager.h"

#include "states/Intro_State.h"

#include <chrono>

class Application
{
public:
	Application(int width, int height, const char* title, float frameRate);
	~Application();

	void Run();
	void HandleInput();

private:
	Window window;

	float desiredFrameRate;
	bool debugMode;
};

#endif