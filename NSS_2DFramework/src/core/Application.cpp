#include "core/Application.h"

#include <windows.h>

Application::Application(int width, int height, const char* title) :
	window(width, height, title), camera(800, 600)
{
	State_Manager::GetInstance()->ChangeState(new Intro_State());

	camera.SetZoom(50.0f);
	camera.SetPosition(glm::vec2(-25.0f, -25.0f));
}

Application::~Application()
{
	glfwTerminate();
}

void Application::Run()
{
	while (!window.ShouldClose())
	{
		HandleInput();
		window.Clear();

		window.Display();
		std::cout << MouseListener::GetInstance()->GetX() << "," << MouseListener::GetInstance()->GetY() << std::endl;
		MouseListener::GetInstance()->Update();
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
