#include "core/Application.h"

#include <windows.h>

Application::Application(int width, int height, const char* title) :
	window(width, height, title)
{
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/amethyst.png", "amethyst");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/diamond.png", "diamond");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/emerald.png", "emerald");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/ruby.png", "ruby");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/sapphire.png", "sapphire");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/topaz.png", "topaz");

	Asset_Manager::GetInstance()->LoadShaderFromFile("assets/shaders/base_shader.vert", "assets/shaders/base_shader.frag", "basic");

	srand(time(NULL));

	int randomVal = 0;
	std::string gem = "";

	for (int width = 1; width < 11; width++)
	{
		std::vector<Sprite*> vec;
		for (int height = 1; height < 11; height++)
		{
			randomVal = rand() % 6;
			switch (randomVal)
			{
			case 0:
				gem = "amethyst";
				break;
			case 1:
				gem = "diamond";
				break;
			case 2:
				gem = "emerald";
				break;
			case 3:
				gem = "ruby";
				break;
			case 4:
				gem = "sapphire";
				break;
			case 5:
				gem = "topaz";
				break;
			}

			Sprite* sprite = new Sprite(
				Asset_Manager::GetInstance()->GetTexture(gem),
				Asset_Manager::GetInstance()->GetShader("basic"),
				glm::vec2(width * 52.0f, height * 52.0f),
				glm::vec2(50.0f, 50.0f));

			vec.push_back(sprite);
		}
		test.push_back(vec);
	}
}

Application::~Application()
{
	glfwTerminate();
}

void Application::Run()
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window.GetWidth()), static_cast<GLfloat>(window.GetHeight()), 0.0f, -1.0f, 1.0f);

	while (!window.ShouldClose())
	{
		HandleInput();
		window.Clear();

		for (auto row = test.begin(); row != test.end(); row++) 
		{
			for (auto col = row->begin(); col != row->end(); col++)
			{
				(*col)->Draw(projection);
			}
		}

		window.Display();
		std::cout << MouseListener::GetInstance()->GetX() << "," << MouseListener::GetInstance()->GetY() << std::endl;
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
