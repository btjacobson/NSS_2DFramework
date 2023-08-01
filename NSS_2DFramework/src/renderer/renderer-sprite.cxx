module;
#include "GL/glew.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"
export module framework:renderer.sprite;

import :renderer.texture2d;
import :renderer.shader;

export class Sprite
{
public:
	Sprite(Texture2D* newTexture, Shader* newShader, glm::vec2 newPosition, GLuint newZOrder = 0.0f,
		glm::vec2 newScale = glm::vec2(1.0f, 1.0f), glm::vec3 newColor = glm::vec3(1.0f, 1.0f, 1.0f),
		GLfloat newRotation = 0.0f);
	~Sprite();

	void Draw(glm::mat4& projection, glm::mat4& view);
	void Update();

	void SetTexture(Texture2D* newTexture);
	void SetShader(Shader* newShader);
	void SetPosition(glm::vec2 newPosition);
	void SetScale(glm::vec2 newScale);
	void SetColor(glm::vec3 newColor);
	void Rotate(GLfloat newRotation);

	glm::vec2 GetPosition();

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
	GLuint zOrder;
};

Sprite::Sprite(Texture2D* newTexture, Shader* newShader, glm::vec2 newPosition, GLuint newZOrder, glm::vec2 newScale, glm::vec3 newColor, GLfloat newRotation) :
	texture(newTexture), shader(newShader), position(newPosition), zOrder(newZOrder), scale(newScale),
	color(newColor), model(1.0f), rotation(newRotation)
{
	InitRenderData();
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &vao);
}

void Sprite::Draw(glm::mat4& projection, glm::mat4& view)
{
	texture->Bind();
	shader->Use();

	shader->SetInteger("ourTexture", 0);
	shader->SetMatrix4("projection", projection);
	shader->SetMatrix4("view", view);
	shader->SetMatrix4("model", model);
	shader->SetVector3f("spriteColor", color);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, zOrder));
	model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, zOrder)); // Center the origin before rotation
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, zOrder)); // Revert centering the origin
	model = glm::scale(model, glm::vec3(scale, 1.0f));

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	texture->Unbind();
}

void Sprite::Update()
{

}

void Sprite::SetTexture(Texture2D* newTexture)
{
	texture = newTexture;
}

void Sprite::SetShader(Shader* newShader)
{
	shader = newShader;
}

void Sprite::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
}

void Sprite::SetScale(glm::vec2 newScale)
{
	scale = newScale;
}

void Sprite::SetColor(glm::vec3 newColor)
{
	color = newColor;
}

void Sprite::Rotate(GLfloat newRotation)
{
	rotation = newRotation;
}

glm::vec2 Sprite::GetPosition()
{
	return position;
}

void Sprite::InitRenderData()
{
	GLuint vbo;
	GLfloat vertices[] =
	{
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	unsigned int ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
