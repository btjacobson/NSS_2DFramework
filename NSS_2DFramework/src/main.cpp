#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Window.h"

int main()
{
	Window window(800, 600, "Test");

	while (window.IsRunning())
	{
		window.HandleInput();
		window.Clear();
		window.Display();
	}
}