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

	Dateiname:		primitives_dome.inl.h
	Beschreibung:	Dome Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 14. Juni 2003 14:01

	Changelog:
	[1]		14. Juni 2003 14:01
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "primitives_dome.h"

#include "..\vertices\vertices.inl.h"

/*
#include "..\vektoren\vector3.h"
#include "..\vertices\vertices.h"
#include "..\viewcone\viewcone.h"
#include "..\vektoren\vector3.inl.h"
#include "..\viewcone\viewcone.inl.h"
#include "..\plane\plane.inl.h"
*/

#pragma intrinsic(memset, memcpy)