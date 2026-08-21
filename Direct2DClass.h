// Direct2DClass.h

#pragma once

#include <windows.h>
#include <d2d1.h>

class Direct2D
{
public:
	Direct2D();
	~Direct2D();

	void Close();
	BOOL Init( HWND hWndMain );
	void Paint();
	BOOL Update( LPARAM lParam );

protected:
	ID2D1Factory *m_lpFactory;
	ID2D1HwndRenderTarget *m_lpRenderTarget;

}; // End of class Direct2D
