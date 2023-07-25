module;

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"

export module framework:core.window;


import :listeners.keyboard;
import :listeners.mouse;

export enum VSync
{
    OFF = 0,
    ON = 1
};

export class Window
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



Window::Window(int width, int height, const char* title)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->window = nullptr;

    Init();
}

Window::~Window()
{
    glfwDestroyWindow(window);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

int Window::GetWidth()
{
    return width;
}

int Window::GetHeight()
{
    return height;
}

void Window::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::HandleInput()
{
    glfwPollEvents();
}

void Window::Display()
{
    glfwSwapBuffers(window);
}

void Window::SetupCallbacks()
{
    glfwSetCursorPosCallback(window, MouseListener::GetInstance()->MousePositionCallback);
    glfwSetMouseButtonCallback(window, MouseListener::GetInstance()->MouseButtonCallback);
    glfwSetScrollCallback(window, MouseListener::GetInstance()->MouseScrollCallback);
    glfwSetKeyCallback(window, KeyboardListener::GetInstance()->KeyCallback);
}

int Window::Init()
{
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "ERROR: could not open window with GLFW\n");
        glfwTerminate();
        return -1;
    }

    SetupCallbacks();

    glfwSwapInterval(ON);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}