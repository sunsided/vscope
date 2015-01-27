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

	Dateiname:		define-vectorops.h
	Beschreibung:	Defines für Vektoroperationen (DOT, CROSS, ...)
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 16:50

	Changelog:
	[1]		05. Juli 2002 16:50

===========================================================================*/

#pragma once

#ifndef DOT
#define DOT			%
#endif

#ifndef CROSS
#define CROSS		^
#endif

#ifndef NORMALIZE
#define NORMALIZE	|
#endif

#ifndef PUNKT
#define PUNKT		DOT
#endif

#ifndef KREUZ
#define KREUZ		CROSS
#endif