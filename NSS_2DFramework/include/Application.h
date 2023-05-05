#ifndef APPLICATION_H
#define APPLICATION_H

#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"

#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture2D.h"

class Application
{
public:
	Application(int width, int height, const char* title);
	~Application();

	void Run();
	void HandleInput();

private:
	Window window;
	Sprite sprite;
};

#endif