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

	Dateiname:		include-direct3d.h
	Beschreibung:	Einbinden der DirectGraphics8-API
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:15

	Changelog:
	[1]		04. Juli 2002 23:15
			Einbinden der Header D3D8 und D3DX8

===========================================================================*/

#pragma once

/*---------------------------------------------------------------------------
	Defines
---------------------------------------------------------------------------*/
#define INITGUID

/*---------------------------------------------------------------------------
	Linker benachrichtigen:
---------------------------------------------------------------------------*/

#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3d9")
#pragma comment(lib, "dxerr9")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9dt")
#else
#pragma comment(lib, "d3dx9")
#endif

/*---------------------------------------------------------------------------
	Einbinden des API-Headers
---------------------------------------------------------------------------*/

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>