#include "core/Application.h"

#include <windows.h>

Application::Application(int width, int height, const char* title, float frameRate) : 
	window(width, height, title), debugMode(false), desiredFrameRate(1.0f / frameRate)
{
	State_Manager::GetInstance()->ChangeState(new Intro_State());
}

Application::~Application()
{
	glfwTerminate();
}

void Application::Run()
{
	std::chrono::time_point lastFrameTime = std::chrono::high_resolution_clock::now();
	std::chrono::time_point currentTime = lastFrameTime;
	std::chrono::duration<float> deltaTime = lastFrameTime - currentTime;
	float dt;
	float totalTime = 0.0f;
	float averageFrameRate = 0.0f;
	int frameCount = 0;

	while (!window.ShouldClose())
	{
		currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = currentTime - lastFrameTime;
		dt = deltaTime.count();

		HandleInput();
		window.Clear();

		State_Manager::GetInstance()->Update(dt);

		window.Display();

		if (debugMode)
		{
			std::cout << MouseListener::GetInstance()->GetX() << "," << MouseListener::GetInstance()->GetY() << std::endl;
		}

		MouseListener::GetInstance()->Update();

		if (dt >= desiredFrameRate)
		{
			lastFrameTime = currentTime;

			std::this_thread::sleep_for(std::chrono::duration<float>(desiredFrameRate - dt));

			frameCount++;
			totalTime += dt;

			if (totalTime >= 1.0f)
			{
				averageFrameRate = frameCount / totalTime;
				std::cout << "Average frame rate: " << averageFrameRate << std::endl;

				frameCount = 0;
				totalTime = 0.0f;
			}
		}
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
