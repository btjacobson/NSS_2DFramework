#ifndef APPLICATION_H
#define APPLICATION_H

#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"

#include "Window.h"

#include "renderer/Shader.h"
#include "renderer/Sprite.h"
#include "renderer/Texture2D.h"
#include "managers/Asset_Manager.h"

class Application
{
public:
	Application(int width, int height, const char* title);
	~Application();

	void Run();
	void HandleInput();

private:
	Window window;
};

#endif