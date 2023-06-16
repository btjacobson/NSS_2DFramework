#include "core/Application.h"

#include <windows.h>

Application::Application(int width, int height, const char* title) : window(width, height, title), debugMode(false)
{
	State_Manager::GetInstance()->ChangeState(new Intro_State());
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

		State_Manager::GetInstance()->Update();

		window.Display();

		if (debugMode)
		{
			std::cout << MouseListener::GetInstance()->GetX() << "," << MouseListener::GetInstance()->GetY() << std::endl;
		}

		MouseListener::GetInstance()->Update();
	}
}

void Application::HandleInput()
{
	window.HandleInput();
	State_Manager::GetInstance()->HandleInput();

	if (KeyboardListener::GetInstance()->IsKeyPressed(GLFW_KEY_F1))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		debugMode = true;
	}
	else if (KeyboardListener::GetInstance()->IsKeyPressed(GLFW_KEY_F2))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		debugMode = false;
	}
}
