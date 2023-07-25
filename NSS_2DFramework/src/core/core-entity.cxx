module;
#include "glm.hpp"
export module framework:core.entity;

export class Entity
{
public:
	Entity();
	~Entity();

private:
	glm::vec2 position;
};