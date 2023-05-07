#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"

#include "Window.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
#include "Texture2D.hpp"
#include "AssetManager.hpp"

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