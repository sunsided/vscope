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

	Dateiname:		pipedescriptor.h
	Beschreibung:	Pipe-Descriptor Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 22:10

	Changelog:
	[1]		10. Juli 2002 22:10
			Erstellt

===========================================================================*/

#pragma once

#ifndef PIPEDESCRIPTOR_DEFINED
#define PIPEDESCRIPTOR_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

struct PIPEDESC {
	HWND					OutputWindow;
	UINT					ScreenWidth, ScreenHeight;
	//D3DFORMAT				Presentation;
	D3DFORMAT				BackBuffer;
	UINT					BackBufferCount;
	BOOL					Windowed;
	D3DMULTISAMPLE_TYPE		Multisample;
	D3DFORMAT				DepthStencil;

};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PIPEDESC				*LPPIPEDESC;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PIPEDESC		PIPEDESCA16;
typedef _ALIGN_16 PIPEDESC		*LPPIPEDESCA16;

typedef _ALIGN_32 PIPEDESC		PIPEDESCA32;
typedef _ALIGN_32 PIPEDESC		*LPPIPEDESCA32;

typedef _CACHEALIGN PIPEDESC	PIPEDESCAC;
typedef _CACHEALIGN PIPEDESC	*LPPIPEDESCAC;*/