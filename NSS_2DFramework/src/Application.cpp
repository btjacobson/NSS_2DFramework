#include "Application.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
	Shader shader("shaders/base_shader.vert", "shaders/base_shader.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window.GetWidth()), static_cast<GLfloat>(window.GetHeight()), 0.0f, -1.0f, 1.0f);

	int width;
	int height;
	int channels;

	unsigned char* data = stbi_load("sprite.png", &width, &height, &channels, STBI_rgb_alpha);
	unsigned char* data2 = stbi_load("box.png", &width, &height, &channels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	sprite = Sprite();
	Sprite sprite2 = Sprite();
	Texture2D tTex = Texture2D();
	Texture2D tTex2 = Texture2D();
	tTex.Generate(16, 16, data);
	tTex2.Generate(16, 16, data2);

	sprite.SetTexture(&tTex);
	sprite.SetShader(&shader);
	sprite.SetPosition(glm::vec2(100.0f, 100.0f));
	sprite.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	sprite.SetScale(glm::vec2(100.0f, 100.0f));

	sprite2.SetTexture(&tTex2);
	sprite2.SetShader(&shader);
	sprite2.SetPosition(glm::vec2(200.0f, 100.0f));
	sprite2.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	sprite2.SetScale(glm::vec2(100.0f, 100.0f));

	stbi_image_free(data);
	stbi_image_free(data2);

	while (!window.ShouldClose())
	{
		HandleInput();
		window.Clear();

		shader.Use();
		shader.SetMatrix4("projection", projection);
		sprite.Draw();
		sprite2.Draw();

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

	if (KeyboardListener::GetInstance()->IsKeyPressed(GLFW_KEY_S))
	{
		sprite.SetPosition(glm::vec2(sprite.GetPosition().x + 1, sprite.GetPosition().y + 1));
	}
}
