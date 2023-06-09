#define _USE_MATH_DEFINES
#include <cmath>

#include "OrbitCamera.hpp"
#include "../App/Application.hpp"
#include "../Config.hpp"

OrbitCamera::OrbitCamera(GLFWwindow* window, glm::vec3 center, float distance)
{
	p_window = window;
	offsetOrigin = glm::vec3(0, BASE_CAMERA_HEIGHT, 0);
	m_up = glm::vec3(0, 1, 0);
	m_center = center;
	this->distance = distance;
	m_rotation.y = -M_PI / 4;

	this->rotate();
	this->view = glm::lookAt(m_position * this->distance, m_center, m_up);
}

void OrbitCamera::processMovements(float deltaTime, glm::vec2 mouse)
{
	if (glfwGetMouseButton(p_window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_rotation += (mouse - m_last) * SENSITIVITY;

		if (m_rotation.y >= M_PI_2)
		{
			m_rotation.y = M_PI_2;
		}

		if (m_rotation.y <= -M_PI_2)
		{
			m_rotation.y = -M_PI_2;
		}

		this->rotate();
	}
	else
	{
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	m_last = mouse;
	this->view = glm::lookAt(m_position * this->distance - offsetOrigin, m_center - offsetOrigin, m_up);
}

void OrbitCamera::rotate()
{
	m_position.x = cos(m_rotation.x) * cos(m_rotation.y);
	m_position.y = sin(m_rotation.y);
	m_position.z = sin(m_rotation.x) * cos(m_rotation.y);
}