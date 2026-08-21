// Direct2D.h

#pragma once

#include <windows.h>
#include <d2d1.h>

#define MAIN_WINDOW_CLASS_NAME													"Main Direct2D Window Class"

#define MAIN_WINDOW_CLASS_STYLE													( CS_HREDRAW | CS_VREDRAW )
#define MAIN_WINDOW_CLASS_ICON_NAME												IDI_APPLICATION
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_MENU_NAME												NULL
#define MAIN_WINDOW_CLASS_ICON_SMALL											LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )

#define MAIN_WINDOW_EXTENDED_STYLE												WS_EX_CLIENTEDGE
#define MAIN_WINDOW_TEXT														"Direct2D"
#define MAIN_WINDOW_STYLE														( WS_OVERLAPPEDWINDOW - WS_THICKFRAME )

#define MAIN_WINDOW_MINIMUM_WIDTH												320
#define MAIN_WINDOW_MINIMUM_HEIGHT												200
