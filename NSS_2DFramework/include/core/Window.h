#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "listeners/MouseListener.h"
#include "listeners/KeyboardListener.h"

enum VSync
{
	OFF = 0,
	ON = 1
};

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
	VSync vsync;
	const char* title;

	GLFWwindow* window;
};

#endif