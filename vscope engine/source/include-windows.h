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

	Dateiname:		include-windows.h
	Beschreibung:	Einbinden der Windows-API
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:04

	Changelog:
	[1]		04. Juli 2002 23:04
			Defines für API-Ausschlüsse und Einbinden des Windows-Headers

===========================================================================*/

#pragma once

/*---------------------------------------------------------------------------
	Linker benachrichtigen:
---------------------------------------------------------------------------*/
#pragma comment(lib, "winmm")

/*---------------------------------------------------------------------------
	Ausschließen von unbenötigten API-Elementen:
---------------------------------------------------------------------------*/

//#define STRICT
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
/*
#define NOSERVICE
#define NOMCX
#define NOIME
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
*/

/*---------------------------------------------------------------------------
	Einbinden der API-Header
---------------------------------------------------------------------------*/

#include <windows.h>
#include <mmsystem.h>