#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "Vertex.hpp"

class Plane
{
public :
    Plane() = default;
    Plane(glm::vec2 size);

    
private :
    std::uint32_t m_vao;
    std::uint32_t m_vbo;
};