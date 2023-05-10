#ifndef ENTITY_H
#define ENTITY_H

#include "glm.hpp"

#include "renderer/Sprite.h"
#include "renderer/Shader.h"

class Entity
{
public:
	Entity();
	~Entity();

private:
	glm::vec2 position;
};

#endif