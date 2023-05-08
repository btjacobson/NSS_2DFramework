#include "Application.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
	Application application(800, 600, "Test");
	application.Run();

	return 0;
}