#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include "GL/glew.h"

#include <iostream>

class Texture2D
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

#endif
