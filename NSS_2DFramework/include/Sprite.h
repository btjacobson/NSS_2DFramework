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
	Sprite();
	~Sprite();

	void Draw();

	void SetTexture(Texture2D* newTexture);
	void SetShader(Shader* newShader);
	void SetPosition(glm::vec2 newPosition);
	void SetSize(glm::vec2 newSize);
	void SetColor(glm::vec3 newColor);
	void Rotate(GLfloat newRotation);

private:
	void InitRenderData();

	Texture2D* texture;
	Shader* shader;

	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;
	glm::mat4 model;

	GLfloat rotation;
	GLuint vao;
};

#endif
