#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>
#include <gdiplus.h>
#include "Matrix.h"
#include "Rocket.h"
#include "Obstacle.h"
#include "Target.h"
#include <ShObjIdl.h>

using namespace Gdiplus;

struct StateData {
	UINT uWidth;
	UINT uHeight;
	Obstacle obstacle;
	Target target;
	Rocket* rockets;
	int deadCount=0;
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR cmdLine, int show) {
	const wchar_t CLASS_NAME[] = TEXT("Smart Rockets");

	WNDCLASS wnd = {};
	wnd.lpfnWndProc = WindowProc;
	wnd.hInstance = hInstance;
	wnd.lpszClassName = CLASS_NAME;

	StateData stateData = {};
	stateData.uWidth = 800;
	stateData.uHeight = 600;
	
	RegisterClass(&wnd);

	HWND hwnd = CreateWindowEx(0,
		CLASS_NAME,
		L"Smart Rocket",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		&stateData);

	if (hwnd == NULL) {
		return 0;
	}
	
	stateData.obstacle.setPos(Vec2((double)stateData.uWidth / 2.0, (double)stateData.uHeight / 2.0));
	stateData.obstacle.setRadius(50);	
	stateData.target = Target((double)stateData.uWidth, (double)stateData.uHeight / 2.0, 100);

	stateData.rockets = (Rocket*)malloc(sizeof(Rocket) * 3);
	
	ULONG_PTR ULPgpToken;
	GdiplusStartupInput gpStartInp;
	GdiplusStartup(&ULPgpToken, &gpStartInp, NULL);
	
	ShowWindow(hwnd, show);

	MSG msg = {};
	while (GetMessage(&msg, hwnd, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	GdiplusShutdown(ULPgpToken);
	return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	switch (uMsg) {
		case WM_PAINT:
		{
			StateData* stateData = reinterpret_cast<StateData*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			Graphics graphics(hdc);
			SolidBrush blue(Color(0, 0, 255));
			SolidBrush green(Color(0, 255, 0));
			SolidBrush red(Color(255, 0, 0));
			SolidBrush* pCurBrush;
			SolidBrush sbBkg(Color(100, 100, 100));
			graphics.FillRectangle(&sbBkg, 0, 0, stateData->uWidth, stateData->uHeight);
			for (int i = 0; i < 3; i++) {
				auto pos = stateData->rockets[i].getPosition();
				RocketState state = stateData->rockets[i].getState();
				if (state == RocketState::ALIVE) {
					pCurBrush = &green;
				}
				else if (state == RocketState::DONE) {
					Rocket parent = stateData->rockets[i];
					for (int j = 0; j < 3; j++) {
						stateData->rockets[i] = Rocket(Vec2(0.0, stateData->uHeight / 2.0), 
							parent, 
							&stateData->obstacle, 
							&stateData->target);
					}
					break;
				}
				else {
					pCurBrush = &red;
					stateData->deadCount += 1;
				}
				graphics.FillEllipse(pCurBrush, (int)pos.x - 20, (int)pos.y - 20, (int)pos.x + 20, (int)pos.y + 20);
			}
			pCurBrush = &green;
			Vec2 targetPos = stateData->target.getPos();
			int targetRad = stateData->target.getRadius();
			Vec2 obsPos = stateData->obstacle.getPos();
			int obsRad = stateData->obstacle.getRadius();
			graphics.FillEllipse(pCurBrush,
				(int)targetPos.x - targetRad,
				(int)targetPos.y - targetRad,
				(int)targetPos.x + targetRad,
				(int)targetPos.y + targetRad);
			pCurBrush = &red;
			graphics.FillEllipse(pCurBrush,
				(int)obsPos.x - obsRad,
				(int)obsPos.y - obsRad,
				(int)obsPos.x + obsRad,
				(int)obsPos.y + obsRad);
			
			graphics.FillRectangle(&sbBkg, 0, 0, 1920, 1080);
			graphics.DrawLine(&pen, 0, 0, 200, 200);
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
		case WM_CREATE:
		{

		}
	}
	return DefWindowProc(hwnd, uMsg, wparam, lparam);
}
