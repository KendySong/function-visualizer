#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OrbitCamera
{
public :
    OrbitCamera() = default;
    OrbitCamera(float speed);
    
    void processMovements(float deltaTime);
    void rotate(glm::vec2 mousePos);

    glm::mat4x4& getView() noexcept;
    glm::vec3& getPosition() noexcept;

private :
    bool m_canRotate;
    float m_speed;
    glm::vec3 m_direction;
    glm::vec3 m_position;
    glm::vec2 m_rotation;

    glm::vec3 m_up;
    glm::mat4x4 m_view;

    bool m_firstMove;
    glm::vec2 m_lastMouse;   
};