#include "bkout.h"

#include "Window.h"
#include "Application.h"

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
	// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		Breakout::Application::GetApp()->SetRunning(false);
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

namespace Breakout {

	Window::Window(const WindowProps& props)
		: m_WindowProps(props)
	{
		HWND hwnd;
		HINSTANCE hInstance = NULL;
		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
		wc.lpszClassName = L"BreakoutWindow";

		RegisterClassEx(&wc);

		hwnd = CreateWindowEx(NULL,
			wc.lpszClassName,
			props.Name.c_str(),
			WS_OVERLAPPEDWINDOW,
			300, 300,
			props.Width, props.Height,
			NULL, NULL,
			hInstance, NULL);

		ShowWindow(hwnd, 1);
	}

	Window::~Window()
	{

	}

	void Window::OnUpdate()
	{
		MSG msg;
		GetMessage(&msg, NULL, 0, 0);
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}