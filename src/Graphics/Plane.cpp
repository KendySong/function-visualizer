#include <vector>

#include <glad/glad.h>

#include "Plane.hpp"
#include "../App/Log.hpp"

Plane::Plane(glm::vec2 worldSize, glm::vec2 gridSize, Interpreter* interpreter)
{
    glm::vec2 caseSize = worldSize / gridSize;
    glm::vec2 halfWorld = worldSize / glm::vec2(2, 2);

    std::vector<Vertex> vertices;
    std::vector<std::uint32_t> indices;

    //Generate vertices
    glm::vec2 input(-gridSize.x / 2, -gridSize.y / 2);
    vertices.reserve((gridSize.x + 1) * (gridSize.x + 1));
    for (size_t y = 0; y <= gridSize.y; y++)
    {
        for (size_t x = 0; x <= gridSize.x; x++)
        {
            float height = 0;
            if (interpreter != nullptr)
            {
                interpreter->reset();
                interpreter->setVariable(input.x + x, input.y + y);
                height = interpreter->interpretAST();
#ifdef DEBUG
                std::string xStr = std::to_string(input.x + x);
                std::string yStr = std::to_string(input.y + y);
                std::string heightStr = std::to_string(height);
                Log::instance()->log("[INFO] x[" + xStr + "] y[" + yStr + "] = " + heightStr + '\n', GREEN);
#endif
            }

            vertices.push_back({ 
                { (x * caseSize.x) - halfWorld.x, -height, (y * caseSize.y) - halfWorld.y},
                { 0, 1, 0}
            });
        }
    }

    //Generate indices
    indices.reserve(gridSize.x * gridSize.y * 6);
    for (std::uint32_t y = 0; y < gridSize.y; y++)
    {
        for (std::uint32_t x = 0; x < gridSize.x; x++)
        {            
            std::uint32_t xGrid = x + y * (gridSize.x + 1);
            indices.push_back(xGrid);
            indices.push_back(xGrid + gridSize.x + 1);
            indices.push_back(xGrid + 1);

            indices.push_back(xGrid + gridSize.x + 1);
            indices.push_back(xGrid + gridSize.x + 2);
            indices.push_back(xGrid + 1);
        }
    }
    m_elementSize = indices.size();

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

void Plane::draw()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glDrawElements(GL_TRIANGLES, m_elementSize, GL_UNSIGNED_INT, 0);
}