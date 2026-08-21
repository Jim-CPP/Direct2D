// Direct2D.cpp
//
// Created from code on this page:
// https://ciprianf.hashnode.dev/win32-api-programming-painting-the-window-using-direct2d

#include "Direct2D.h"

// Global variables
Direct2D g_direct2D;

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
			g_direct2D.Init( hWndMain );

			// Break out of switch
			break;

		} // End of a create message
		case WM_PAINT:
		{
			// A paint message

			// Paint direct 2d
			g_direct2D.Paint();

			// Break out of switch
			break;

		} // End of a paint message
		case WM_LBUTTONDOWN:
		{
			// A left button down message

			// Update direct 2d
			g_direct2D.Update( lParam );

			// Break out of switch
			break;;

		} // End of a left button down message
		case WM_DESTROY:
		{
			// A destroy message

			// Close direct 2d
			g_direct2D.Close();

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
