#include "Sprite.h"

Sprite::Sprite() : texture(nullptr), shader(nullptr), position(0.0f, 0.0f), size(0.0f, 0.0f),
	color(1.0f, 1.0f, 1.0f), model(1.0f), rotation(0.0f)
{
	InitRenderData();
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &vao);
}

void Sprite::Draw()
{
	shader->Use();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Center the origin before rotation
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Revert centering the origin
	model = glm::scale(model, glm::vec3(size, 1.0f));
	
	shader->SetInteger("ourTexture", 0);
	shader->SetMatrix4("model", model);
	shader->SetVector3f("spriteColor", color);

	texture->Bind();

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	texture->Unbind();
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

void Sprite::SetScale(glm::vec2 newSize)
{
	size = newSize;
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
