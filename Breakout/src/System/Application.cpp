#include "bkout.h"

#include "Application.h"

namespace Breakout {

	Application* Application::s_App = nullptr;

	Application::Application()
	{
		s_App = this;

		m_Window = new Window();
	}

	Application::~Application()
	{
		delete m_Context;
		delete m_Window;
	}

	void Application::Start()
	{
		Log::Init();
		LOG_INFO("Log Initialized");

		ASSERT(m_Window, "Unable to create window!");

		m_Context = new VulkanContext(m_Window);
		ASSERT(m_Context, "Could not create Context");
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::Stop()
	{

	}

}