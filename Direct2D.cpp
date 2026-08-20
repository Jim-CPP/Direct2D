// Direct2D.cpp
//
// Created from code on this page:
// https://ciprianf.hashnode.dev/win32-api-programming-painting-the-window-using-direct2d

#include "Direct2D.h"

// Global variables
ID2D1Factory *g_lpFactory = NULL;
ID2D1HwndRenderTarget *g_lpRenderTarget = NULL;

BOOL InitDirect2D( HWND hWndMain )
{
	BOOL bResult = FALSE;

	// Create factory
	if( D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_lpFactory ) == S_OK )
	{
		// Successfully created factory
		RECT rcClient;
		int nClientWidth;
		int nClientHeight;

		// Get client rext
		GetClientRect( hWndMain, &rcClient );

		// Calculate client size
		nClientWidth	= ( rcClient.right - rcClient.left );
		nClientHeight	= ( rcClient.bottom - rcClient.top );

		// Store size
		D2D1_SIZE_U size = D2D1::SizeU( nClientWidth, nClientHeight );

		// Create render target
		if ( g_lpFactory->CreateHwndRenderTarget( D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties( hWndMain, size ), &g_lpRenderTarget ) == S_OK)
		{
			// Successfully created render target

			// Begin drawing
			g_lpRenderTarget->BeginDraw();

			// Clear render target
			g_lpRenderTarget->Clear( D2D1::ColorF( D2D1::ColorF::White ) );

			// End drawing
			g_lpRenderTarget->EndDraw();

		} // End of successfully created render target

	} // End of successfully created factory

	return bResult;

} // End of function InitDirect2D

void CleanUpDirect2D()
{
	// See if factory is valid
	if( g_lpFactory )
	{
		// Factory is valid

		// Release factory
		g_lpFactory->Release();

	} // End of factory is valid

	// See if render target is valid
	if( g_lpRenderTarget )
	{
		// Render target is valid

		// Release render target
		g_lpRenderTarget->Release();

	} // End of render target is valid

} // End of function CleanUpDirect2D

LRESULT CALLBACK MainWindowProcedure( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message

			// Initialise direct 2d
			InitDirect2D( hWndMain );

			// Break out of switch
			break;

		} // End of a create message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_PAINT:
		{
			// A paint message

			// Begin drawing
			g_lpRenderTarget->BeginDraw();

			// No actual drawing in here, just copy the render target to the window

			// End drawing
			g_lpRenderTarget->EndDraw();

			// Break out of switch
			break;

		} // End of a paint message
		case WM_LBUTTONDOWN:
		{
			// A left button down message
			ID2D1SolidColorBrush *lpBrush;

			// Create brush
			if( g_lpRenderTarget->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Red ), &lpBrush ) == S_OK )
			{
				// Successfully created brush
				int nMouseX;
				int nMouseY;
				int nRight;
				int nBottom;

				// Store mouse position
				nMouseX = LOWORD( lParam );
				nMouseY = HIWORD( lParam );

				// Calculate rectangle position
				nRight	= ( nMouseX + 100 );
				nBottom	= ( nMouseY + 100 );

				// Begin drawing
				g_lpRenderTarget->BeginDraw();

				// Create rectangle
				D2D1_RECT_F rect = D2D1::RectF( nMouseX, nMouseY, nRight, nBottom );

				// Create rounder rectangle
				D2D1_ROUNDED_RECT roundedRect = D2D1::RoundedRect( rect, 10.f, 10.f );

				// Draw rounded rectangle
				g_lpRenderTarget->DrawRoundedRectangle( roundedRect, lpBrush, 5.0f, NULL );

				// End drawing
				g_lpRenderTarget->EndDraw();

				// Release brush
				lpBrush->Release();

			} // End of successfully created brush

			// Break out of switch
			break;

		} // End of a left button down message
		case WM_DESTROY:
		{
			// A destroy message

			// Clean up direct 2d
			CleanUpDirect2D();

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lResult = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lResult;

} // End of function MainWindowProcedure

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
	RegisterClassEx( &wcMain );

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
