#define _USE_MATH_DEFINES
#define HALF_PI M_PI / 2
#include <cmath>

#include "OrbitCamera.hpp"
#include "../App/Application.hpp"
#include "../Config.hpp"

OrbitCamera::OrbitCamera(GLFWwindow* window, glm::vec3 center, float distance)
{
	p_window = window;
	m_up = glm::vec3(0, 1, 0);
	m_center = center;
	m_distance = distance;
	m_rotation.y = -M_PI / 4;

	this->rotate();
	this->view = glm::lookAt(m_position * m_distance, m_center, m_up);
}

void OrbitCamera::processMovements(float deltaTime, glm::vec2 mouse)
{
	if (glfwGetMouseButton(p_window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_rotation += (mouse - m_last) * SENSITIVITY;

		if (m_rotation.y >= HALF_PI)
		{
			m_rotation.y = HALF_PI;
		}

		if (m_rotation.y <= -HALF_PI)
		{
			m_rotation.y = -HALF_PI;
		}

		this->rotate();
	}
	else
	{
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	m_last = mouse;
	this->view = glm::lookAt(m_position * m_distance, m_center, m_up);
}

void OrbitCamera::rotate()
{
	m_position.x = cos(m_rotation.x) * cos(m_rotation.y);
	m_position.y = sin(m_rotation.y);
	m_position.z = sin(m_rotation.x) * cos(m_rotation.y);
}