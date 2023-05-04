#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	void HandleInput();
	void Clear();
	void Display();

	bool IsRunning();

private:
	void Build();

	int width;
	int height;
	const char* title;
	GLFWwindow* window;
};

#endif