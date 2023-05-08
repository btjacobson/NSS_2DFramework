#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

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
	void SetFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
	void SetInteger(const GLchar* name, GLint value, GLboolean useShader = false);
	void SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);
	void SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);
	void SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);
	void SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);

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
