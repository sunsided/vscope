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

	Dateiname:		materialman.inl.h
	Beschreibung:	Material-Manager Inline
	Revision:		1
	Erstellt:		MMT, 26. Juni 2003 08:35

	Changelog:
	[1]		26. Juni 2003 08:35
			Erstellt

===========================================================================*/

#pragma once

#include "..\include-direct3d.h"
#include "..\piped3d2\piped3d2.h"
#include "..\piped3d2\piped3d2.inl.h"
#include "..\color\color4.h"
#include "..\color\color4.inl.h"
#include "materialman.h"

#pragma intrinsic(memset, memcpy)

// Konstruktion und Destruktion bei garnichts ....
VSINLINE MATERIALMAN::MATERIALMAN() {
	memset(this, 0, sizeof(MATERIALMAN));
}
VSINLINE MATERIALMAN::~MATERIALMAN() {
}