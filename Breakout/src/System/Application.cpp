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
		delete m_Window;
	}

	void Application::Start()
	{

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