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
    
}

void Sandbox::update(float deltaTime)
{
    
}

void Sandbox::render()
{
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