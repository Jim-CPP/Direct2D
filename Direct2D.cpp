// Direct2D.cpp
//
// Created from code on this page:
// https://ciprianf.hashnode.dev/win32-api-programming-painting-the-window-using-direct2d

#include "Direct2D.h"

// Global variables
ID2D1Factory* g_lpFactory = NULL;
ID2D1HwndRenderTarget* g_lpRenderTarget = NULL;
ID2D1SolidColorBrush* g_lpBrush = NULL;

// Forward declarations of functions
LRESULT CALLBACK MainWindowProcedure(HWND hWndMain, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT InitDirect2D(HWND hWndMain );
void CleanUp();

int WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow )
{
	MSG msg;
	WNDCLASSEX wcMain;

	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Clear main window class structure
	ZeroMemory( &wcMain, sizeof( wcMain ) );

	// Initialise main window class structure
	wcMain.cbSize			= sizeof( WNDCLASSEX );
	wcMain.style			= MAIN_WINDOW_CLASS_STYLE;
	wcMain.lpfnWndProc		= MainWindowProcedure;
	wcMain.hInstance		= hInstance;
	wcMain.hIcon			= MAIN_WINDOW_CLASS_ICON;
	wcMain.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
	wcMain.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
	wcMain.lpszMenuName		= MAIN_WINDOW_CLASS_MENU_NAME;
	wcMain.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
	wcMain.hIconSm			= MAIN_WINDOW_CLASS_ICON_SMALL;

	// Register main window class
	RegisterClassEx(&wcMain);

	// Create main window
	HWND hWndMain = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT, MAIN_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL );

	// Ensure that main window was created
	if( hWndMain )
	{
		// Successfully created main window

		// Show main window
		ShowWindow( hWndMain, nCmdShow );

		// Update main window
		UpdateWindow( hWndMain );

		// Main message loop
		while( GetMessage( &msg, NULL, 0, 0 ) )
		{
			// Translate message
			TranslateMessage( &msg );

			// Dispatch message
			DispatchMessage( &msg );

		}; // End of main message loop

	} // End of successfully created main window

	return msg.wParam;

} // End of function WinMain

LRESULT CALLBACK MainWindowProcedure(HWND hWndMain, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT:
		{
			// A paint command
            if (!g_lpRenderTarget ) {
                InitDirect2D( hWndMain );
            }
            g_lpRenderTarget->BeginDraw();
            g_lpRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

            D2D1_RECT_F rect = D2D1::RectF(250, 100, 450, 300);
            D2D1_ROUNDED_RECT roundedRect = D2D1::RoundedRect(rect, 10.f, 10.f);
            g_lpRenderTarget->DrawRoundedRectangle(roundedRect, g_lpBrush, 5.0f, NULL);

            g_lpRenderTarget->EndDraw();

            // Break out of switch
            break;

		} // End of a paint command
        case WM_DESTROY:
		{
			// A destroy command
            CleanUp();
            PostQuitMessage(0);

            // Break out of switch
            break;

		} // End of a destroy command
        default:
		{
			// Default command
            return DefWindowProc( hWndMain, uMsg, wParam, lParam);

            // Break out of switch
            break;

		} // End of default command
        }
    return 0;

} // End of function MainWindowProcedure

HRESULT InitDirect2D(HWND hWndMain )
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_lpFactory );
    if (SUCCEEDED(hr)) {
        RECT rc;
        GetClientRect( hWndMain, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

        hr = g_lpFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties( hWndMain, size),
            &g_lpRenderTarget );

        if (SUCCEEDED(hr)) {
            g_lpRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Blue), &g_lpBrush );
        }
    }
    return hr;

} // End of function InitDirect2D

void CleanUp()
{
    if ( g_lpRenderTarget ) g_lpRenderTarget->Release();
    if ( g_lpFactory ) g_lpFactory->Release();
    if ( g_lpBrush ) g_lpBrush->Release();

} // End of function CleanUp
