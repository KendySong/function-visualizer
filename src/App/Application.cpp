#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Application.hpp"
#include "../Config.hpp"
#include "Log.hpp"

Application* Application::s_application = nullptr;

Application::Application() 
{
	glfwInit();
	p_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Function Visualizer", NULL, NULL);
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(p_window);

	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(p_window, (videoMode->width / 2) - WIN_WIDTH / 2, (videoMode->height / 2) - WIN_HEIGHT / 2);
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glClearColor(0, 0, 0, 1);

#ifdef DEBUG
	const GLubyte* gpu = glGetString(GL_VERSION);
	const GLubyte* version = glGetString(GL_VERSION);
	std::string gpuName;
	std::string versionName;

	for (size_t i = 0; i < strlen((char*)gpu); i++)
	{
		gpuName += gpu[i];
	}

	for (size_t i = 0; i < strlen((char*)version); i++)
	{
		versionName += version[i];
	}

	Log::instance()->log("[INFO] OpenGL version : " + versionName + "\n", GREEN);
	Log::instance()->log("[INFO] GPU : " + gpuName, GREEN);
#endif

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	m_sandbox = Sandbox(p_window);
}

Application* Application::instance() noexcept
{
	if (s_application == nullptr)
	{
		s_application = new Application();
	}
	return s_application;
}

int Application::run()
{
	while (!glfwWindowShouldClose(p_window))
	{
		glfwPollEvents();

		float deltaTime = m_deltaTimer.getElapsedTime();	
		m_deltaTimer.restart();

		m_sandbox.update(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();	

		m_sandbox.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(p_window);
	}

	return 0;
}