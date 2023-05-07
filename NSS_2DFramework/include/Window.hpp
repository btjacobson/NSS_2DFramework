#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "MouseListener.hpp"
#include "KeyboardListener.hpp"

class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	bool ShouldClose();
	int GetWidth();
	int GetHeight();

	void Clear();
	void HandleInput();
	void Display();
	void SetupCallbacks();

private:
	int Init();

	int width;
	int height;
	const char* title;

	GLFWwindow* window;
};

#endif