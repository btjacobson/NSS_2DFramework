#ifndef TEXTURE_2D
#define TEXTURE_2D

#include "GL/glew.h"

class Texture2D
{
public:
	Texture2D(GLuint width, GLuint height, unsigned char* data);

	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind();
	void Unbind();

private:
	GLuint id;
	GLuint width;
	GLuint height;
	GLuint internalFormat;
	GLuint imageFormat;
	GLuint wrapS;
	GLuint wrapT;
	GLuint filterMin;
	GLuint filterMax;
};

#endif
