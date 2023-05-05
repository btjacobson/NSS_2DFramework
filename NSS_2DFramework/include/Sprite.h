#ifndef SPRITE_H
#define SPRITE_H

#include "GL/glew.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"

#include "Texture2D.h"
#include "Shader.h"

class Sprite
{
public:
	Sprite(Texture2D* newTexture, Shader* newShader, glm::vec2 newPosition, 
		glm::vec2 newScale = glm::vec2(1.0f, 1.0f), glm::vec3 newColor = glm::vec3(1.0f, 1.0f, 1.0f),
		GLfloat newRotation = 0.0f);
	~Sprite();

	void Draw(glm::mat4& projection);
	void Update();

	void SetTexture(Texture2D* newTexture);
	void SetShader(Shader* newShader);
	void SetPosition(glm::vec2 newPosition);
	void SetScale(glm::vec2 newScale);
	void SetColor(glm::vec3 newColor);
	void Rotate(GLfloat newRotation);

private:
	void InitRenderData();

	Texture2D* texture;
	Shader* shader;

	glm::vec2 position;
	glm::vec2 scale;
	glm::vec3 color;
	glm::mat4 model;

	GLfloat rotation;
	GLuint vao;
};

#endif
