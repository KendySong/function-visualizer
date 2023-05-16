#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "Sandbox.hpp"
#include "../Config.hpp"
#include "Application.hpp"

#include "Log.hpp"

Sandbox::Sandbox()
{
    Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    glUseProgram(shader.getProgram());
    
    float vertices[]
    {
        -0.5, -0.5,
        0.0, 0.5,
        0.5, -0.5
    };

    std::uint32_t vao = 0;
    std::uint32_t vbo = 0;
    
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_VERTEX_ARRAY, vbo);
    glBufferData(GL_VERTEX_ARRAY, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Sandbox::update(float deltaTime)
{
    
}

void Sandbox::render()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
 
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
}