#include "Shader.h"

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
	vertexShader = 0;
	fragmentShader = 0;
	program = 0;

	LoadFiles(vertexFilePath, fragmentFilePath);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::Use()
{
	glUseProgram(program);
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniform1f(glGetUniformLocation(program, name), value);
}
void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniform1i(glGetUniformLocation(program, name), value);
}
void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniform2f(glGetUniformLocation(program, name), x, y);
}
void Shader::SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniform2f(glGetUniformLocation(program, name), value.x, value.y);
}
void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniform3f(glGetUniformLocation(program, name), x, y, z);
}
void Shader::SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniform3f(glGetUniformLocation(program, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniform4f(glGetUniformLocation(program, name), x, y, z, w);
}
void Shader::SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniform4f(glGetUniformLocation(program, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
{
	if (useShader)
	{
		Use();
	}

	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader::GetProgramID()
{
	return program;
}

void Shader::LoadFiles(const char* vertexFilePath, const char* fragmentFilePath)
{
	std::string vertLine;
	std::string vertContents;
	std::ifstream vertFile(vertexFilePath);

	if (vertFile.is_open())
	{
		while (getline(vertFile, vertLine))
		{
			vertContents.append(vertLine + "\n");
		}

		Create(vertContents.c_str(), GL_VERTEX_SHADER);

		vertFile.close();
	}
	else
	{
		// TODO: Error reporting
	}

	std::string fragLine;
	std::string fragContents;
	std::ifstream fragFile(fragmentFilePath);

	if (fragFile.is_open())
	{
		while (getline(fragFile, fragLine))
		{
			fragContents.append(fragLine + "\n");
		}

		Create(fragContents.c_str(), GL_FRAGMENT_SHADER);

		fragFile.close();
	}
	else
	{
		// TODO: Error reporting
	}

	CompileAndLink();
}

void Shader::Create(const char* fileContents, GLenum shaderType)
{
	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		vertexShader = glCreateShader(shaderType);
		glShaderSource(vertexShader, 1, &fileContents, NULL);
		break;

	case GL_FRAGMENT_SHADER:
		fragmentShader = glCreateShader(shaderType);
		glShaderSource(fragmentShader, 1, &fileContents, NULL);
		break;

	default:
		break;
	}
}

void Shader::CompileAndLink()
{
	GLint result = GL_FALSE;
	int logLength;

	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(vertexShader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> fragShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(fragmentShader, logLength, NULL, &fragShaderError[0]);
	std::cout << &fragShaderError[0] << std::endl;

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> programError((logLength > 1) ? logLength : 1);
	glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
	std::cout << &programError[0] << std::endl;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
