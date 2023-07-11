#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "Vertex.hpp"
#include "../Interpreter/Interpreter.hpp"

class Plane
{
public :
    Plane() = default;
    Plane(glm::vec2 size, glm::vec3 color, Interpreter* interpreter, glm::vec2 offset = glm::vec2(0, 0));
    void draw(); 

private :
    std::uint32_t m_elementSize;
    std::uint32_t m_vao;
    std::uint32_t m_ebo;
    std::uint32_t m_vbo;
};