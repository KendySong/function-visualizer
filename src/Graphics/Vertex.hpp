#pragma once
#include <glm/glm.hpp>

struct Vertex
{
    Vertex(const glm::vec3& position, const glm::vec3& color);

    glm::vec3 position;
    glm::vec3 color;
};