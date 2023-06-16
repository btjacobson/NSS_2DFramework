#include "core/Application.h"

#include <windows.h>

Application::Application(int width, int height, const char* title, float frameRate) : 
	window(width, height, title), desiredFrameRate(1.0f / frameRate), lastFrameTime(0.0f), 
	currentFrameTime(0.0f), deltaTime(0.0f)
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
		Update();
		Draw();
	}
}

void Application::HandleInput()
{
	window.HandleInput();
	State_Manager::GetInstance()->HandleInput();
}

void Application::Update()
{
	currentFrameTime = glfwGetTime();
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	State_Manager::GetInstance()->Update(deltaTime);
	MouseListener::GetInstance()->Update();
}

void Application::Draw()
{
	window.Clear();
	State_Manager::GetInstance()->Draw();
	window.Display();
}
