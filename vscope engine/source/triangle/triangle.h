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

	Dateiname:		triangle.h
	Beschreibung:	Triangle (Template) Definition
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 19:04

	Changelog:
	[1]		09. Juli 2002 19:04

===========================================================================*/

#pragma once

#ifndef TTRIANGLE_DEFINED
#define TTRIANGLE_DEFINED
#endif

#include "..\defines.h"

/*---------------------------------------------------------------------------
	Vorwärtsdeklaration
---------------------------------------------------------------------------*/
struct VECTOR3;

/*---------------------------------------------------------------------------
	Struktur für das Dreieck
---------------------------------------------------------------------------*/
template <class type>
struct TTRIANGLE {
//:: Die Membervariablen ....................................................
public:
	union {
		type v[3];
		type _10, _11, _12;
		type v0, v1, v2;
	};

//:: Die Konstruktoren ......................................................
public:
	VSINLINE TTRIANGLE() {}

	VSINLINE TTRIANGLE( type v0, type v1, type v2 ) {
		v[0] = v0;
		v[1] = v1;
		v[2] = v2;
	}
};