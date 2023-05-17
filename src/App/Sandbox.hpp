#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Graphics/Shader.hpp"
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
    Shader m_shader;
    
    glm::mat4x4 m_projection; 
    GLFWwindow* p_window;
};