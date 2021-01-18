#pragma once

#include "Window.h"
#include "Scene/Scene.h"

namespace Breakout {

	class Application
	{
	public:
		Application();
		~Application();

		void Start();
		void Run();
		void Stop();

	public:
		inline static Application* GetApp() { return s_App; }
		inline static Window* GetWindow() { return Application::GetApp()->m_Window; }

	private:
		Window* m_Window;
		Scene* m_Scene;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_App;
	};

}