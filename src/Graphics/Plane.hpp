#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "Vertex.hpp"

class Plane
{
public :
    Plane() = default;
    Plane(glm::vec2 worldSize, glm::vec2 boardSize);

    std::uint32_t elementSize;

private :
    std::uint32_t m_vao;
    std::uint32_t m_ebo;
    std::uint32_t m_vbo;
};