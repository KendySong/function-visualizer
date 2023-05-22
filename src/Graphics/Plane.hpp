#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "Vertex.hpp"
#include "../Interpreter/Interpreter.hpp"

class Plane
{
public :
    Plane() = default;
    Plane(glm::vec2 worldSize, glm::vec2 gridSize, glm::vec3 color, Interpreter* interpreter);
    void draw(); 

private :
    std::uint32_t m_elementSize;
    std::uint32_t m_vao;
    std::uint32_t m_ebo;
    std::uint32_t m_vbo;
};