#pragma once
#include <ImGui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Graphics/Shader.hpp"
#include "../Graphics/Plane.hpp"
#include "../Graphics/OrbitCamera.hpp"

class Sandbox
{
public :
    Sandbox() = default;
    Sandbox(GLFWwindow* window);

    void update(float deltaTime);
    void render();
    
private :
    OrbitCamera m_camera;
    Plane m_plane;
    Shader m_shader;

    std::uint32_t m_fbo;
    std::uint32_t m_rbo;
    std::uint32_t m_frameTexture;
    ImVec2 m_imageCorner;
   
    GLFWwindow* p_window;
};