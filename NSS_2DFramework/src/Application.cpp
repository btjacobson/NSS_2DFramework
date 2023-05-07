#include "Application.hpp"

Application::Application(int width, int height, const char* title) :
	window(width, height, title)
{

}

Application::~Application()
{
	glfwTerminate();
}

void Application::Run()
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window.GetWidth()), static_cast<GLfloat>(window.GetHeight()), 0.0f, -1.0f, 1.0f);

	//Texture2D tTex = Texture2D(16, 16, data);
	//Texture2D tTex2 = Texture2D(16, 16, data2);
	
	//Sprite sprite = Sprite(&tTex, &shader,
	//	glm::vec2(100.0f, 100.0f),
	//	glm::vec2(100.0f, 100.0f));

	//Sprite sprite2 = Sprite(&tTex2, &shader, 
	//	glm::vec2(200.0f, 100.0f), 
	//	glm::vec2(100.0f, 100.0f));

	while (!window.ShouldClose())
	{
		HandleInput();
		window.Clear();

		//sprite.Draw(projection);
		//sprite2.Draw(projection);

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
