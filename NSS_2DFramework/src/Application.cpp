#include "Application.hpp"

#include <windows.h>

Application::Application(int width, int height, const char* title) :
	window(width, height, title)
{
	AssetManager::GetInstance()->LoadTextureFromFile("assets/sprite.png", "coin");
	AssetManager::GetInstance()->LoadShaderFromFile("shaders/base_shader.vert", "shaders/base_shader_frag", "basic");
	AssetManager::GetInstance()->LoadShaderFromFile("shaders/test_shader.vert", "shaders/test_shader_frag", "test");
}

Application::~Application()
{
	glfwTerminate();
}

void Application::Run()
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window.GetWidth()), static_cast<GLfloat>(window.GetHeight()), 0.0f, -1.0f, 1.0f);
	
	Sprite sprite = Sprite(
		AssetManager::GetInstance()->GetTexture("coin"), 
		AssetManager::GetInstance()->GetShader("basic"),
		glm::vec2(100.0f, 100.0f),
		glm::vec2(100.0f, 100.0f));

	while (!window.ShouldClose())
	{
		HandleInput();
		window.Clear();

		sprite.Draw(projection);

		window.Display();
		MouseListener::GetInstance()->EndFrame();
	}
}

void Application::HandleInput()
{
	window.HandleInput();

	if (KeyboardListener::GetInstance()->IsKeyPressed(GLFW_KEY_F1))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (KeyboardListener::GetInstance()->IsKeyPressed(GLFW_KEY_F2))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
