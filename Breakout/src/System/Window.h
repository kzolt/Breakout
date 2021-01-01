#pragma once

struct GLFWwindow;

namespace Breakout {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;

		WindowProps(const std::string& title = "Breakout", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		Window(const WindowProps& windowProps = WindowProps());
		~Window();

		bool IsRunning();

		void OnUpdate();
		void OnRender();

	private:
		GLFWwindow* m_Window;

	};

}