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

	Dateiname:		vscope.cpp
	Beschreibung:	Einbinden aller Header zu Testzwecken (Compilertest)
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:06

	Changelog:
	[1]		04. Juli 2002 23:06
			Einbinden von vscope-version.h, include-windows.h
			include-direct3d.h

===========================================================================*/

#pragma once

/*---------------------------------------------------------------------------
	Einbinden der Header
---------------------------------------------------------------------------*/
#ifndef DONT_LINK_VSCOPE	// wird auch über die Befehlszeile gesetzt!
#define DONT_LINK_VSCOPE
#endif
#include "vscope.h"