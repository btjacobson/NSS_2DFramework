#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Shader
{
public:
	Shader(const char* vertexFilePath, const char* fragmentFilePath);
	~Shader();

	void Use();

	GLuint GetProgramID();

private:
	void LoadFiles(const char* vertexFilePath, const char* fragmentFilePath);
	void Create(const char* fileContents, GLenum shaderType);
	void CompileAndLink();

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
};

#endif
