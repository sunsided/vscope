/*==========================================================================*
    v-scope: the vision's scope realtime 3D engine
    Copyright (C) 2002, Markus Mayer, Alle Rechte vorbehalten.

	Dieser Quellcode wird "WIE ER IST" vertrieben, ohne jegliche Garantie
	auf Stabilität, Vollständigkeit oder Nützlichkeit für einen bestimmten
	Zweck. Sie sind berechtigt, ihn für jeden beliebigen unkommerziellen 
	Zweck zu nutzen, verändern oder weiter zu vertreiben, solange die
	Copyrightinformation (oben) als Teil dieser Datei erhalten bleibt.
	Der Autor möchte ebenfalls freundlich darum bitten, dass ihm alle 
	signifikanten Änderungen an diesem Quellcode zugeschickt werden.

	Dateiname:		window.cpp
	Beschreibung:	Window-Helper
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 21:19

	Changelog:
	[1]		10. Juli 2002 21:19
			Erstellt

===========================================================================*/

#include "window.h"
#include "window.inl.h"

/*------------------------------------------------------------
/|	Funktion:		Create()
/|	Beschreibung:	Erstellt ein Fenster
/|	Parameter:		a couple ... ;)
/|	Rückgabe:		HWND
/|  2002-07-10 21:24 MMT
/+------------------------------------------------------------*/
HWND WINDOW::Create(LPCSTR title, int width, int height, HINSTANCE hInstance, WNDPROC CallbackProc, BOOL visible, int color) {
	WNDCLASSEX wc;
	HWND hWnd;

	wc.cbSize         = sizeof(WNDCLASSEX);
	wc.style          = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc    = CallbackProc;
	wc.cbClsExtra     = 0;
	wc.cbWndExtra     = 0;
	wc.hInstance      = hInstance;
	wc.hIcon          = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor        = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground  = (HBRUSH)GetStockObject(color);
	wc.lpszMenuName   = NULL;
	wc.lpszClassName  = VS_WINDOWCLASS_BLANK;
	wc.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	//Registriere die Windows Klasse
	if(!RegisterClassEx(&wc)) 
		return NULL;

	hWnd=CreateWindowEx(NULL, VS_WINDOWCLASS_BLANK, title, visible==TRUE?WS_VISIBLE:NULL, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);
	if(!hWnd)
		return NULL;

	if(visible) {
		ShowWindow(hWnd,SW_SHOW);
		UpdateWindow(hWnd);
		SetFocus(hWnd);
	}

	this->hWnd = hWnd;
	return hWnd;
}


/*------------------------------------------------------------
/|	Funktion:		Create()
/|	Beschreibung:	Erstellt ein Fenster
/|	Parameter:		a couple ... ;)
/|	Rückgabe:		HWND
/|  2002-07-10 21:24 MMT
/+------------------------------------------------------------*/
HWND WINDOW::Create(WNDCLASSEX wc, LPCSTR title, UINT width, UINT height, BOOL visible) {
	HWND hWnd;

	//Registriere die Windows Klasse
	if(!RegisterClassEx(&wc))
		return NULL;

	hWnd=CreateWindowEx(NULL, wc.lpszClassName, title, visible==TRUE?WS_VISIBLE:NULL, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, wc.hInstance, NULL);
	if(!hWnd)
		return NULL;

	if(visible) {
		ShowWindow(hWnd,SW_SHOW);
		UpdateWindow(hWnd);
		SetFocus(hWnd);
	}

	this->hWnd = hWnd;
	return hWnd;
}
