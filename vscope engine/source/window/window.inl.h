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

	Dateiname:		window.inl.h
	Beschreibung:	Window-Helper Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 21:19

	Changelog:
	[1]		10. Juli 2002 21:19
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-windows.h"
#include "window.h"
#include "..\debug\debug.h"

/*------------------------------------------------------------
/|	Funktion:		Release()
/|	Beschreibung:	Gibt das Fenster frei
/|	Parameter:		n/a
/|	Rückgabe:		BOOL
/|  2002-07-10 21:24 MMT
/+------------------------------------------------------------*/
VSINLINE BOOL WINDOW::Release() {
	if(this->hWnd){
		if(!DestroyWindow(this->hWnd)) {
			return FALSE;
		}
		else {
			MSG msg;
			while(PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
				DispatchMessage(&msg);
		}
		this->hWnd=NULL;
	}

	return TRUE;
}


/*------------------------------------------------------------
/|	Funktion:		Release()
/|	Beschreibung:	Gibt ein Fenster frei
/|	Parameter:		hWnd (HWND)
/|	Rückgabe:		BOOL
/|  2002-07-10 21:24 MMT
/+------------------------------------------------------------*/
VSINLINE BOOL WINDOW::Release(HWND hWnd) {
	if(hWnd){
		if(!DestroyWindow(hWnd)) {
			return FALSE;
		}
		else {
			MSG msg;
			while(PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
				DispatchMessage(&msg);
		}
		hWnd=NULL;
	}

	return TRUE;
}


/*------------------------------------------------------------
/|	Funktion:		CheckMessageQeue()
/|	Beschreibung:	Überprüft und behandelt den Nachrichtenqeue
/|	Parameter:		n/a
/|	Rückgabe:		BOOL
/|  2002-07-10 21:24 MMT
/+------------------------------------------------------------*/
VSINLINE BOOL WINDOW::CheckMessageQeue() {
	if(PeekMessage(&this->msg, this->hWnd, 0, 0,PM_REMOVE)) {
		TranslateMessage(&this->msg);
		DispatchMessage(&this->msg);
		return TRUE;
	}
	return FALSE;
}

/*------------------------------------------------------------
/|	Funktion:		CheckMessageQeue()
/|	Beschreibung:	Überprüft und behandelt den Nachrichtenqeue
/|	Parameter:		*msg (MSG)
/|	Rückgabe:		BOOL, MSG (in Parameterliste)
/|  2002-07-10 21:25 MMT
/+------------------------------------------------------------*/
VSINLINE BOOL WINDOW::CheckMessageQeue(MSG* msg) {
	if(PeekMessage(msg, this->hWnd, 0, 0,PM_REMOVE)) {
		TranslateMessage(msg);
		DispatchMessage(msg);
		return TRUE;
	}
	return FALSE;
}


/*------------------------------------------------------------
/|	Funktion:		SetVisibility()
/|	Beschreibung:	Setzt die Sichtbarkeit des Fensters
/|	Parameter:		visible (BOOL)
/|	Rückgabe:		BOOL
/|  2002-07-10 21:26 MMT
/+------------------------------------------------------------*/
VSINLINE BOOL WINDOW::SetVisibility(BOOL visible) {
	return ShowWindow(this->hWnd, visible==TRUE?SW_SHOW:SW_HIDE);
}

/*------------------------------------------------------------
/|	Funktion:		SetVisibility()
/|	Beschreibung:	Setzt die Sichtbarkeit eines Fensters
/|	Parameter:		hWnd (HWND), visible (BOOL)
/|	Rückgabe:		BOOL
/|  2002-07-10 21:26 MMT
/+------------------------------------------------------------*/
VSINLINE BOOL WINDOW::SetVisibility(HWND hWnd, BOOL visible) {
	return ShowWindow(hWnd, visible==TRUE?SW_SHOW:SW_HIDE);
}

/*------------------------------------------------------------
/|	Funktion:		WINDOW()
/|	Beschreibung:	Konstruktor
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2002-07-10 21:28 MMT
/+------------------------------------------------------------*/
VSINLINE WINDOW::WINDOW() {
}

/*------------------------------------------------------------
/|	Funktion:		WINDOW()
/|	Beschreibung:	Konstruktor
/|	Parameter:		a couple ... ;)
/|	Rückgabe:		n/a
/|  2002-07-10 21:28 MMT
/+------------------------------------------------------------*/
VSINLINE WINDOW::WINDOW(LPCSTR title, int width, int height, HINSTANCE hInstance, WNDPROC CallbackProc, BOOL visible, int color) {
	this->Create(title, width, height, hInstance, CallbackProc, visible, color);
}

/*------------------------------------------------------------
/|	Funktion:		WINDOW()
/|	Beschreibung:	Konstruktor
/|	Parameter:		a couple ... ;)
/|	Rückgabe:		n/a
/|  2002-07-10 21:28 MMT
/+------------------------------------------------------------*/
VSINLINE WINDOW::WINDOW(WNDCLASSEX wc, LPCSTR title, UINT width, UINT height, BOOL visible) {
	this->Create(wc, title, width, height, visible);
}

/*------------------------------------------------------------
/|	Funktion:		~WINDOW()
/|	Beschreibung:	Destruktor
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2002-07-10 21:28 MMT
/+------------------------------------------------------------*/
VSINLINE WINDOW::~WINDOW() {
	if(this->hWnd){
		if(DestroyWindow(this->hWnd)) {
			MSG msg;
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				DispatchMessage(&msg);
		}
		this->hWnd=NULL;
	}
}

/*------------------------------------------------------------
/|	Funktion:		GetHWnd()
/|	Beschreibung:	Liefert das HWND des Fensters
/|	Parameter:		n/a
/|	Rückgabe:		HWND
/|  2002-07-10 21:28 MMT
/+------------------------------------------------------------*/
VSINLINE HWND WINDOW::GetHWnd() {
	return this->hWnd;
}

VSINLINE HWND* WINDOW::GetHWnd() const {
	return (HWND*)this->hWnd;
}

/*------------------------------------------------------------
/|	Funktion:		operator HWND()
/|	Beschreibung:	Liefert das HWND des Fensters
/|	Parameter:		n/a
/|	Rückgabe:		HWND
/|  2002-07-10 21:28 MMT
/+------------------------------------------------------------*/
VSINLINE WINDOW::operator HWND () const {
	return this->hWnd;
}

VSINLINE WINDOW::operator HWND* () const {
	return (HWND*)this->hWnd;
}

/*------------------------------------------------------------
/|	Funktion:		SetTitle()
/|	Beschreibung:	Setzt den Titel des Fensters
/|	Parameter:		n/a
/|	Rückgabe:		BOOL
/|  2002-07-10 21:28 MMT
/+------------------------------------------------------------*/
VSINLINE BOOL WINDOW::SetTitle(const char* pszOutput, ...) {
	char	szBuffer[1024];
	va_list	arglist;

	va_start(arglist, pszOutput);
	vsprintf(szBuffer, pszOutput, arglist);
	va_end(arglist);

	if(!SetWindowText(this->hWnd, szBuffer)) {
		dprintf("WINDOW::SetTitle - failed setting. Errno: %d.\n", GetLastError());
	}
	return TRUE;
}