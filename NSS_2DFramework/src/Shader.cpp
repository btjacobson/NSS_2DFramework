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
