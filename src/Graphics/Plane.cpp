#include <vector>

#include <glad/glad.h>

#include "Plane.hpp"
#include "../App/Log.hpp"
#include <iostream>

Plane::Plane(glm::vec2 size, glm::vec3 color, Interpreter* interpreter)
{
    float heighestPoint = 0;
    float middlePoint = 0;
    float lowestPoint = 0;

    glm::vec2 caseSize = size / size;
    glm::vec2 halfWorld = size / glm::vec2(2, 2);
    float* heightMap = new float[(size.x + 1) * (size.y + 1)];
    if (interpreter != nullptr)
    {
        color = glm::vec3(0, 1, 1);
        glm::vec2 input(-size.x / 2, -size.y / 2);
        interpreter->reset();
        interpreter->setVariable(input.x, input.y);
        heighestPoint = interpreter->interpretAST();
        lowestPoint = heighestPoint;

        //Precompute the heightmap for get the heighest and lowest point
        for (size_t y = 0; y <= size.y; y++)
        {
            for (size_t x = 0; x <= size.x; x++)
            {
                interpreter->reset();
                interpreter->setVariable(input.x + x, input.y + y);
                float height = interpreter->interpretAST();
                if (height > heighestPoint)
                {
                    heighestPoint = height;
                }

                if (height < lowestPoint)
                {
                    lowestPoint = height;
                }

                heightMap[(int)(size.x + 1) * y + x] = height;
            }
        }

        middlePoint = glm::mix(heighestPoint, lowestPoint, 0.5);
    }   
    else
    {
        for (size_t y = 0; y <= size.y; y++)
        {
            for (size_t x = 0; x <= size.x; x++)
            {
                heightMap[(int)(size.x + 1) * y + x] = 0;
            }
        }
    }

    /*
    for (size_t y = 0; y <= size.y; y++)
    {
        for (size_t x = 0; x <= size.x; x++)
        {
            std::cout << heightMap[(int)(size.x + 1) * y + x] << ' ';
        }
        std::cout << '\n';
    }
    */

    //Generate vertices
    std::vector<Vertex> vertices;
    vertices.reserve((size.x + 1) * (size.x + 1));
    for (size_t y = 0; y <= size.y; y++)
    {
        for (size_t x = 0; x <= size.x; x++)
        {
            float height = heightMap[(int)(size.x + 1) * y + x];
            if (interpreter != nullptr)
            {
                //Transform the linear interpolation equation to isolate the scale
                //x = a(1 - t) + t * b //we need to isolate t
                //t = (x - a) / (-a + b)
                float scale = (height - heighestPoint) / (-heighestPoint + lowestPoint);

                //So we can compute the color with this scale
                const glm::vec3 red = glm::vec3(1, 0, 0);
                const glm::vec3 blue = glm::vec3(0, 0, 1);
                color = (red - blue) * scale + blue;   
            }

            vertices.push_back({
                { (x * caseSize.x) - halfWorld.x, -height, (y * caseSize.y) - halfWorld.y},
                { color.x, color.y, color.z }
            });
        }
    }

    //Generate indices
    std::vector<std::uint32_t> indices;
    indices.reserve(size.x * size.y * 6);
    for (std::uint32_t y = 0; y < size.y; y++)
    {
        for (std::uint32_t x = 0; x < size.x; x++)
        {            
            std::uint32_t xGrid = x + y * (size.x + 1);
            indices.push_back(xGrid);
            indices.push_back(xGrid + size.x + 1);
            indices.push_back(xGrid + 1);

            indices.push_back(xGrid + size.x + 1);
            indices.push_back(xGrid + size.x + 2);
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

    delete[] heightMap;
}

void Plane::draw()
{
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_elementSize, GL_UNSIGNED_INT, 0);
}