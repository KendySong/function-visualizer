#include <vector>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "Sandbox.hpp"
#include "../Config.hpp"
#include "../Graphics/Vertex.hpp"
#include "Application.hpp"

Sandbox::Sandbox(GLFWwindow* window)
{
    p_window = window;
    m_shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    glUseProgram(m_shader.getProgram());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Vertex vertices[]
    {
        {{ -0.5, 0,  0.5 }, {0, 1, 0}},
        {{ -0.5, 0, -0.5 }, {0, 1, 0}},
        {{  0.5, 0,  0.5 }, {0, 1, 0}},
        {{  0.5, 0, -0.5 }, {0, 1, 0}},
        {{ -0.5, 0, -0.5 }, {0, 1, 0}},
        {{  0.5, 0,  0.5 }, {0, 1, 0}},
    };

    std::uint32_t vao = 0;
    std::uint32_t vbo = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 2 * sizeof(glm::vec3), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));

    float aspectRatio = WIN_WIDTH / WIN_HEIGHT;
    glm::mat4x4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 99999999.0f);
    m_shader.setMat4x4("projection", projection);

    m_camera = OrbitCamera(window, glm::vec3(0, 0, 0), 2);
}

void Sandbox::update(float deltaTime)
{
    double x, y;
    glfwGetCursorPos(p_window, &x, &y);
    m_camera.processMovements(deltaTime, glm::vec2(x, y));
    m_shader.setMat4x4("view", m_camera.view);
}

void Sandbox::render()
{
    glDrawArrays(GL_TRIANGLES, 0, 6);

    /*
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        ImGui::MenuItem("Load");
        ImGui::MenuItem("Save");
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Functions");

    ImGui::End();

    ImGui::Begin("Render");

    ImGui::End();
    */
}