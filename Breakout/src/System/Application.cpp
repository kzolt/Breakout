#include "bkout.h"

#include "Application.h"

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
		Log::Init();
		LOG_INFO("Log Initialized");

		m_Window = new Window();
		ASSERT(m_Window, "Unable to create window!");

		m_Scene = new Scene();
	}

	void Application::Run()
	{
		while (m_Window->IsRunning())
		{
			m_Window->OnUpdate();

			m_Scene->OnUpdate();
			m_Scene->OnRender();

			m_Window->OnRender();
		}
	}

	void Application::Stop()
	{

	}

}