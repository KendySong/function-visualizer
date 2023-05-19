#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OrbitCamera
{
public :
    OrbitCamera() = default;
    OrbitCamera(GLFWwindow* window, glm::vec3 center, float distance);
    
    void processMovements(float deltaTime, glm::vec2 mouse);
    void scroll(double offset);

private :
    void rotate();

public :
    glm::mat4x4 view;
    float m_distance;

private :
    

    GLFWwindow* p_window;
    glm::vec3 m_position;
    glm::vec3 m_center;
    glm::vec2 m_rotation;

    
    glm::vec3 m_up;
    glm::vec2 m_last;
};