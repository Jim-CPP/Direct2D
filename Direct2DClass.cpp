// Direct2DClass.cpp

#include "Direct2DClass.h"

Direct2D::Direct2D()
{
} // End of function Direct2D::Direct2D

Direct2D::~Direct2D()
{
} // End of function Direct2D::~Direct2D

void Direct2D::Close()
{
	// See if factory is valid
	if( m_lpFactory )
	{
		// Factory is valid

		// Release factory
		m_lpFactory->Release();

	} // End of factory is valid

	// See if render target is valid
	if( m_lpRenderTarget )
	{
		// Render target is valid

		// Release render target
		m_lpRenderTarget->Release();

	} // End of render target is valid

} // End of function Direct2D::Close

BOOL Direct2D::Init( HWND hWndMain )
{
	BOOL bResult = FALSE;

	// Create factory
	if( D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_lpFactory ) == S_OK )
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
		if ( m_lpFactory->CreateHwndRenderTarget( D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties( hWndMain, size ), &m_lpRenderTarget ) == S_OK)
		{
			// Successfully created render target

			// Begin drawing
			m_lpRenderTarget->BeginDraw();

			// Clear render target
			m_lpRenderTarget->Clear( D2D1::ColorF( D2D1::ColorF::White ) );

			// End drawing
			m_lpRenderTarget->EndDraw();

			// Update return value
			bResult = TRUE;

		} // End of successfully created render target

	} // End of successfully created factory

	return bResult;

} // End of function Direct2D::Init

void Direct2D::Paint()
{
	// Begin drawing
	m_lpRenderTarget->BeginDraw();

	// No actual drawing in here, just copy the render target to the window

	// End drawing
	m_lpRenderTarget->EndDraw();

} // End of function Direct2D::Paint

BOOL Direct2D::Update( LPARAM lParam )
{
	BOOL bResult = FALSE;

	ID2D1SolidColorBrush *lpBrush;

	// Create brush
	if( m_lpRenderTarget->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Red ), &lpBrush ) == S_OK )
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
		m_lpRenderTarget->BeginDraw();

		// Create rectangle
		D2D1_RECT_F rect = D2D1::RectF( nMouseX, nMouseY, nRight, nBottom );

		// Create rounder rectangle
		D2D1_ROUNDED_RECT roundedRect = D2D1::RoundedRect( rect, 10.f, 10.f );

		// Draw rounded rectangle
		m_lpRenderTarget->DrawRoundedRectangle( roundedRect, lpBrush, 5.0f, NULL );

		// End drawing
		m_lpRenderTarget->EndDraw();

		// Release brush
		lpBrush->Release();

		// Update return value
		bResult = TRUE;

	} // End of successfully created brush

	return bResult;

} // End of function Direct2D::Update

/*
Direct2D::
{
} // End of function Direct2D::
*/
