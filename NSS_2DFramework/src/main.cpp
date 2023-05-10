#include "core/Application.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
	stbi_set_flip_vertically_on_load(true);

	Application application(800, 600, "Test");
	application.Run();

	return 0;
}