module;
#include <GLFW/glfw3.h>
#include <memory>
export module framework:core.application;

import :core.window;
import :listeners.keyboard;
import :listeners.mouse;
import :states.intro;
import :managers.state;

export class Application
{
public:
	Application(int width, int height, const char* title, float frameRate);
	~Application();

	void Run();

	void HandleInput();
	void Update();
	void Draw();

private:
	Window window;

	float desiredFrameRate;
	float lastFrameTime;
	float currentFrameTime;
	float deltaTime;
};


Application::Application(int width, int height, const char* title, float frameRate) : 
	window(width, height, title), desiredFrameRate(1.0f / frameRate), lastFrameTime(0.0f), 
	currentFrameTime(0.0f), deltaTime(0.0f)
{
	State_Manager::GetInstance()->ChangeState(std::make_unique<Intro_State>());
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
	currentFrameTime = static_cast<float>(glfwGetTime());
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
