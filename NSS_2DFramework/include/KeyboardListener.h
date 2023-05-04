#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "GLFW/glfw3.h"

class KeyboardListener
{
public:
	static KeyboardListener* GetInstance();

	static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mod);

	static bool IsKeyPressed(int key);

private:
	KeyboardListener();
	~KeyboardListener();

	static KeyboardListener* instance;

	bool keyPressed[350];
};

#endif
