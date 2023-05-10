#include "core/Application.h"

#include <windows.h>

Application::Application(int width, int height, const char* title) :
	window(width, height, title), camera(800, 600)
{
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/amethyst.png", "amethyst");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/diamond.png", "diamond");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/emerald.png", "emerald");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/ruby.png", "ruby");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/sapphire.png", "sapphire");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/topaz.png", "topaz");
	Asset_Manager::GetInstance()->LoadTextureFromFile("assets/textures/board.png", "board");

	Asset_Manager::GetInstance()->LoadShaderFromFile("assets/shaders/base_shader.vert", "assets/shaders/base_shader.frag", "basic");

	srand(time(NULL));

	int randomVal = 0;
	std::string gem = "";

	gameBoard = new Sprite(
		Asset_Manager::GetInstance()->GetTexture("board"),
		Asset_Manager::GetInstance()->GetShader("basic"),
		glm::vec2(0, 0), -0.1f);

	for (int width = gameBoard->GetPosition().x; width < 11; width++)
	{
		std::vector<Sprite*> vec;

		for (int height = gameBoard->GetPosition().y; height < 11; height++)
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
				glm::vec2(width, height));

			vec.push_back(sprite);
		}
		test.push_back(vec);
	}

	camera.SetZoom(2.0f);
	camera.SetPosition(gameBoard->GetPosition());
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

		gameBoard->Draw(camera.GetProjectionMatrix(), camera.GetViewMatrix());

		for (auto row = test.begin(); row != test.end(); row++) 
		{
			for (auto col = row->begin(); col != row->end(); col++)
			{
				(*col)->Draw(camera.GetProjectionMatrix(), camera.GetViewMatrix());
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
