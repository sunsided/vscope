/*==========================================================================*
    v-scope: the vision's scope realtime 3D engine
    Copyright (C) 2003, Markus Mayer, Alle Rechte vorbehalten.

	Dieser Quellcode wird "WIE ER IST" vertrieben, ohne jegliche Garantie
	auf Stabilität, Vollständigkeit oder Nützlichkeit für einen bestimmten
	Zweck. Sie sind berechtigt, ihn für jeden beliebigen unkommerziellen 
	Zweck zu nutzen, verändern oder weiter zu vertreiben, solange die
	Copyrightinformation (oben) als Teil dieser Datei erhalten bleibt.
	Der Autor möchte ebenfalls freundlich darum bitten, dass ihm alle 
	signifikanten Änderungen an diesem Quellcode zugeschickt werden.

	Dateiname:		versionstruct.h
	Beschreibung:	v-scope Versionsinformationen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2003 13:58

	Changelog:
	[1]		10. Juli 2003 13:58

===========================================================================*/

#pragma once

#ifndef VSCOPEVERSIONINFO_DEFINED
#define VSCOPEVERSIONINFO_DEFINED

#include "vscope-version.h"

typedef struct VSVERSIONINFO {
public:
	static const unsigned short int		Major = VSCOPE_VER_MAJOR;
	static const unsigned short int		Minor = VSCOPE_VER_MINOR;
	static const unsigned long  int		Build = VSCOPE_VER_BUILD;
} VSVERSIONINFO;



#endif