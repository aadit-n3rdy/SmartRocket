#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>
#include "Matrix.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR cmdLine, int show) {
	const wchar_t CLASS_NAME[] = TEXT("Smart Rockets");

	WNDCLASS wnd = {};
	wnd.lpfnWndProc = WindowProc;
	wnd.hInstance = hInstance;
	wnd.lpszClassName = CLASS_NAME;

	RegisterClass(&wnd);

	HWND hwnd = CreateWindowEx(0,
		CLASS_NAME,
		L"Smart Rocket",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, show);

	MSG msg = {};
	while (GetMessage(&msg, hwnd, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}


	return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	switch (uMsg) {
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_CLOSE:
		{
			if (MessageBox(hwnd, L"Are u sure u wanna close the window?", L"Smart Rocket", MB_OKCANCEL) == IDOK) {
				DestroyWindow(hwnd);
				return 0;
			}
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wparam, lparam);
}
