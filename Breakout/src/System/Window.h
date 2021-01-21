#pragma once

struct GLFWwindow;

namespace Breakout {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;
		bool Minimized;

		WindowProps(const std::string& title = "Breakout", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height), Minimized(false) {}
	};

	class Window
	{
	public:
		Window(const WindowProps& windowProps = WindowProps());
		~Window();

		inline const WindowProps& GetWindowProps() const { return m_Props; }

		bool IsRunning() const;
		bool IsMinimized() const { return m_Props.Minimized; }

		void OnUpdate(Timestep ts);
		void OnRender();

		std::pair<double, double> GetMousePos();

	private:
		GLFWwindow* m_Window;
		WindowProps m_Props;

	};

}