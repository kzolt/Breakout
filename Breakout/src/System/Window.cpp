#include "bkout.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Breakout {

	Window::Window(const WindowProps& windowProps)
		: m_Props(windowProps)
	{
		ASSERT(glfwInit(), "Unable to Initalize GLFW");

		m_Window = glfwCreateWindow(windowProps.Width, windowProps.Height, windowProps.Title.c_str(), NULL, NULL);
		ASSERT(m_Window, "Unable to create GLFW window");

		glfwMakeContextCurrent(m_Window);
		ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize OpenGL Context");

		glfwSwapInterval(1);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	bool Window::IsRunning()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void Window::OnUpdate(Timestep ts)
	{
		glfwPollEvents();
	}

	void Window::OnRender()
	{
		glfwSwapBuffers(m_Window);
	}

	std::pair<double, double> Window::GetMousePos()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window, &xpos, &ypos);

		return { xpos, ypos };
	}

}