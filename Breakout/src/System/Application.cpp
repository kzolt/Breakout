#include "bkout.h"

#include "Application.h"
#include "Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Breakout {

	Application* Application::s_App = nullptr;

	Application::Application()
	{
		s_App = this;
	}

	Application::~Application()
	{
		delete m_Scene;
		delete m_Window;
	}

	void Application::Start()
	{
		Random::Init();

		Log::Init();
		LOG_INFO("Log Initialized");

		m_Window = new Window();
		ASSERT(m_Window, "Unable to create window!");

		Renderer::Init();

		m_Scene = new Scene();
	}

	void Application::Run()
	{
		while (m_Window->IsRunning())
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_Window->OnUpdate(timestep);

			if (!m_Window->IsMinimized())
			{
				m_Scene->OnUpdate(timestep);
				m_Scene->OnRender();

				m_Window->OnRender();
			}
		}
	}

	void Application::Stop()
	{
		Renderer::Shutdown();
	}

}