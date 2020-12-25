#pragma once

#include "Window.h"

namespace Breakout {

	class Application
	{
	public:
		Application();
		~Application();

		void Start();
		void Run();
		void Stop();

		void SetRunning(bool value) { m_Running = value; }

	public:
		inline static Application* GetApp() { return s_App; }

	private:
		Window* m_Window;

		bool m_Running = true;

	private:
		static Application* s_App;
	};

}