module;
#include "GLFW/glfw3.h"
export module framework:listeners.keyboard;

export class KeyboardListener
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

KeyboardListener* KeyboardListener::instance = new KeyboardListener();

KeyboardListener::KeyboardListener()
{
    for (int i = 0; i < 350; ++i)
    {
        keyPressed[i] = 0;
    }
}

KeyboardListener::~KeyboardListener()
{
    delete instance;
    instance = nullptr;
}

KeyboardListener* KeyboardListener::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new KeyboardListener();
    }

    return instance;
}

void KeyboardListener::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mod)
{
    if (action == GLFW_PRESS)
    {
        instance->keyPressed[key] = true;
    }

    if (action == GLFW_RELEASE)
    {
        instance->keyPressed[key] = false;
    }
}

bool KeyboardListener::IsKeyPressed(int key)
{
    return instance->keyPressed[key];
}
