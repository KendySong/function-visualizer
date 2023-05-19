#include <vector>

#include <glad/glad.h>

#include "Plane.hpp"
#include <iostream>

Plane::Plane(glm::vec2 worldSize, glm::vec2 boardSize)
{
    glm::vec2 caseSize = worldSize / boardSize;
    glm::vec2 halfWorld = worldSize / glm::vec2(2, 2);

    std::vector<Vertex> vertices;
    std::vector<std::uint32_t> indices;

    vertices.reserve((boardSize.x + 1) * (boardSize.x + 1));
    for (size_t y = 0; y <= boardSize.y; y++)
    {
        for (size_t x = 0; x <= boardSize.x; x++)
        {
            vertices.push_back({ 
                { (x * caseSize.x) - halfWorld.x, 0, (y * caseSize.y) - halfWorld.y },
                { 0, 1, 0 } 
            });
        }
    }

    indices.reserve(boardSize.x * boardSize.y * 6);
    for (std::uint32_t y = 0; y < boardSize.y; y++)
    {
        for (std::uint32_t x = 0; x < boardSize.x; x++)
        {            
            std::uint32_t xGrid = x + y * (boardSize.x + 1);
            indices.push_back(xGrid);
            indices.push_back(xGrid + boardSize.x + 1);
            indices.push_back(xGrid + 1);

            indices.push_back(xGrid + boardSize.x + 1);
            indices.push_back(xGrid + boardSize.x + 2);
            indices.push_back(xGrid + 1);
        }
    }
    this->elementSize = indices.size();

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 2 * sizeof(glm::vec3), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
}