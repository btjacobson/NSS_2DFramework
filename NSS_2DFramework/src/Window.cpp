#include "Window.h"

Window::Window(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->window = nullptr;

	Build();
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::HandleInput()
{
	glfwPollEvents();
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Display()
{
	glfwSwapBuffers(window);
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(window);
}

void Window::Build()
{
	if (!glfwInit())
	{
		return;
	}

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		return;
	}

	glViewport(0, 0, width, height);
}
