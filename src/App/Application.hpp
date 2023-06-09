#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Timer.hpp"
#include "Sandbox.hpp"

class Application 
{
private :
	Application();

public:
	static Application* instance() noexcept;

	int run();

private :
	static Application* s_application;
	GLFWwindow* p_window;
	Timer m_deltaTimer;
	Sandbox m_sandbox;
};