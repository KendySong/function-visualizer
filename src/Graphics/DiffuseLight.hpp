#pragma once
#include <glm/glm.hpp>

struct DiffuseLight
{
	DiffuseLight() = default;
	DiffuseLight(glm::vec3 position, glm::vec4 light);

	glm::vec3 position;
	glm::vec4 color;
};