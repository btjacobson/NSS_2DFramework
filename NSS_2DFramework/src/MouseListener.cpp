#include "MouseListener.hpp"

MouseListener* MouseListener::instance = new MouseListener();

MouseListener::MouseListener()
{
    scrollX = 0.0;
    scrollY = 0.0;
    xPos = 0.0;
    yPos = 0.0;
    lastX = 0.0;
    lastY = 0.0;
    isDragging = false;

    for (int i = 0; i < 3; ++i)
    {
        mouseButtonPressed[i] = 0;
    }
}

MouseListener::~MouseListener()
{
    delete instance;
    instance = nullptr;
}

MouseListener* MouseListener::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new MouseListener();
    }

    return instance;
}

void MouseListener::MousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
    instance->lastX = instance->xPos;
    instance->lastY = instance->yPos;
    instance->xPos = xPos;
    instance->yPos = yPos;
    instance->isDragging = instance->mouseButtonPressed[0];
}

void MouseListener::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        instance->mouseButtonPressed[button] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        instance->mouseButtonPressed[button] = false;
        instance->isDragging = false;
    }
}

void MouseListener::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    instance->scrollX = xOffset;
    instance->scrollY = yOffset;
}

void MouseListener::EndFrame()
{
    instance->scrollX = 0;
    instance->scrollY = 0;
    instance->lastX = instance->xPos;
    instance->lastY = instance->yPos;
}

float MouseListener::GetX()
{
    return (float)instance->xPos;
}

float MouseListener::GetY()
{
    return (float)instance->yPos;
}

float MouseListener::GetLastX()
{
    return (float)instance->lastX;
}

float MouseListener::GetLastY()
{
    return (float)instance->lastY;
}

float MouseListener::GetDX()
{
    return (float)(instance->xPos - instance->lastX);
}

float MouseListener::GetDY()
{
    return (float)(instance->lastY - instance->yPos);
}

float MouseListener::GetScrollX()
{
    return (float)instance->scrollX;
}

float MouseListener::GetScrollY()
{
    return (float)instance->scrollY;
}

bool MouseListener::IsDragging()
{
    return instance->isDragging;
}

bool MouseListener::MouseButtonPressed(int button)
{
    return instance->mouseButtonPressed[button];
}
