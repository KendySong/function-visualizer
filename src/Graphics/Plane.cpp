#include <glad/glad.h>

#include "Plane.hpp"

Plane::Plane(glm::vec2 size)
{
    //Load and configure plane
    Vertex planeVertices[]
    {
        {{ -0.5, 0,  0.5 }, {0, 1, 0}},
        {{ -0.5, 0, -0.5 }, {0, 1, 0}},
        {{  0.5, 0,  0.5 }, {0, 1, 0}},
        {{  0.5, 0, -0.5 }, {0, 1, 0}},
        {{ -0.5, 0, -0.5 }, {0, 1, 0}},
        {{  0.5, 0,  0.5 }, {0, 1, 0}},
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof planeVertices, planeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 2 * sizeof(glm::vec3), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
}