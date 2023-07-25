module;
#include "GL/glew.h"
#include "stb_image.h"
#include <iostream>
export module framework:renderer.texture2d;

export class Texture2D
{
public:
	Texture2D(const char* filepath);

	void Generate(const char* filepath);
	void Bind();
	void Unbind();

private:
	GLuint id;
	GLuint wrapS;
	GLuint wrapT;
	GLuint filterMin;
	GLuint filterMax;

	int width;
	int height;
	int channels;
};

Texture2D::Texture2D(const char* filepath) :
	wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_NEAREST), filterMax(GL_NEAREST)
{
	Generate(filepath);
}

void Texture2D::Generate(const char* filepath)
{
	unsigned char* data = stbi_load(filepath, &width, &height, &channels, STBI_rgb_alpha);
	if (!data)
	{
		std::cout << "Failed to load texture: " << filepath << std::endl;
	}

	GLenum format = (channels ? GL_RGBA : GL_RGB);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

	glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture2D::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
