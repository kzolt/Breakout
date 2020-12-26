#pragma once

#include <string>

namespace Breakout {

	struct WindowProps
	{
		std::wstring Name;
		uint32_t Width, Height;
		bool VSync;

		WindowProps(const std::wstring& name, uint32_t width = 1280, uint32_t height = 720, bool vsync = true)
			: Name(name), Width(width), Height(height), VSync(vsync) {}
	};

	class Window
	{
	public:
		Window(const WindowProps& props = WindowProps(L"Breakout"));
		~Window();

		void OnUpdate();

		inline const HWND& GetHandle() const { return m_HWND; }

	private:
		WindowProps m_WindowProps;
		HWND m_HWND;
	};

}