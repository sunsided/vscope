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

	Dateiname:		window.h
	Beschreibung:	Window-Helper Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 21:19

	Changelog:
	[1]		10. Juli 2002 21:19
			Erstellt

===========================================================================*/

#pragma once

#ifndef WINDOW_DEFINED
#define WINDOW_DEFINED
#endif

#include "..\defines.h"
#include "..\include-windows.h"
#include <stdio.h>
#include <stdarg.h>

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
#ifndef VS_WINDOWCLASS_BLANK
#define VS_WINDOWCLASS_BLANK "VSCOPEEngineBlankWindow"
#endif

/*---------------------------------------------------------------------------
	Strukturen für die Vertices
---------------------------------------------------------------------------*/
class WINDOW {
//:: Die Membervariablen ....................................................
protected:
	HWND			hWnd;
	MSG				msg;

//:: Die Konstruktoren ......................................................
public:
				WINDOW();
				WINDOW(LPCSTR title, int width, int height, HINSTANCE hInstance, WNDPROC CallbackProc, BOOL visible = TRUE, int color = BLACK_BRUSH);
				WINDOW(WNDCLASSEX wc, LPCSTR title, UINT width, UINT height, BOOL visible = TRUE);

//:: Die Destruktoren .......................................................
public:
	virtual		~WINDOW();

//:: Das Interface ..........................................................
public:
	//:: Operatoren: Casting ....................................................
				operator HWND () const;
				operator HWND* () const;

	//:: Funktionen: Einfache ...................................................
	HWND		Create(LPCSTR title, int width, int height, HINSTANCE hInstance, WNDPROC CallbackProc, BOOL visible = TRUE, int color = BLACK_BRUSH);
	HWND		Create(WNDCLASSEX wc, LPCSTR title, UINT width, UINT height, BOOL visible = TRUE);
	BOOL		Release();
	BOOL		Release(HWND hWnd);
	BOOL		CheckMessageQeue();
	BOOL		CheckMessageQeue(MSG* msg);
	BOOL		SetVisibility(BOOL visible = TRUE);
	BOOL		SetVisibility(HWND hWnd, BOOL visible = TRUE);
	HWND		GetHWnd();
	HWND*		GetHWnd() const;
	BOOL		SetTitle(const char* pszOutput, ...);
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef WINDOW				*LPWINDOW;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 WINDOW	WINDOWA16;
typedef _ALIGN_16 WINDOW	*LPWINDOWA16;

typedef _ALIGN_32 WINDOW	WINDOWA32;
typedef _ALIGN_32 WINDOW	*LPWINDOWA32;

typedef _CACHEALIGN WINDOW	WINDOWAC;
typedef _CACHEALIGN WINDOW	*LPWINDOWAC;*/