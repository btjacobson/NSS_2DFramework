#ifndef MOUSE_LISTENER_H
#define MOUSE_LISTENER_H

#include <GLFW/glfw3.h>

class MouseListener
{
public:
	static MouseListener* GetInstance();

	static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void EndFrame();

	static float GetX();
	static float GetY();
	static float GetLastX();
	static float GetLastY();
	static float GetDX();
	static float GetDY();
	static float GetScrollX();
	static float GetScrollY();

	static bool IsDragging();
	static bool MouseButtonPressed(int button);

private:
	MouseListener();
	~MouseListener();

	static MouseListener* instance;

	double scrollX;
	double scrollY;
	double xPos;
	double yPos;
	double lastX;
	double lastY;
	bool isDragging;
	bool mouseButtonPressed[3];
};

#endif
