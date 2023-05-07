#include "Texture2D.hpp"

Texture2D::Texture2D(GLuint width, GLuint height, GLenum format, unsigned char* data) :
	width(width), height(height), wrapS(GL_REPEAT), wrapT(GL_REPEAT), 
	filterMin(GL_NEAREST), filterMax(GL_NEAREST)
{
	Generate(width, height, format, data);
}

void Texture2D::Generate(GLuint width, GLuint height, GLenum format, unsigned char* data)
{
	this->width = width;
	this->height = height;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

	glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
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
