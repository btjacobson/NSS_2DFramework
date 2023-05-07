#ifndef TEXTURE_2D_HPP
#define TEXTURE_2D_HPP

#include "GL/glew.h"

class Texture2D
{
public:
	Texture2D(GLuint width, GLuint height, GLenum format, unsigned char* data);

	void Generate(GLuint width, GLuint height, GLenum format, unsigned char* data);
	void Bind();
	void Unbind();

private:
	GLuint id;
	GLuint width;
	GLuint height;
	GLuint wrapS;
	GLuint wrapT;
	GLuint filterMin;
	GLuint filterMax;
};

#endif
