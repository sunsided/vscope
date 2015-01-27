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

	Dateiname:		enums-math.h
	Beschreibung:	Enumerationen
	Revision:		2
	Erstellt:		MMT, 07. Juli 2002 19:43

	Changelog:
	[2]		12. Juli 2003 15:55, MMT
			Orientation-Typ hinzugefügt
			Location zu Typ geändert
	[1]		07. Juli 2002 19:43

===========================================================================*/

#pragma once

#ifndef MATHENUMS_DEFINED
#define MATHENUMS_DEFINED


/*---------------------------------------------------------------------------
	LOCATION-Enumeration (Objekte in Bezug aufeinander)
---------------------------------------------------------------------------*/
typedef enum LOCATION {
	LOC_FRONT		= 0,		// davor
	LOC_BACK		= 1,		// dahinter
	LOC_SPLIT		= 2,		// durch
	LOC_COPLANAR	= 3,		// darauf
	LOC_UNDEFINED	= 4,		// weder/noch
	LOC_INSIDE		= 5,		// darinnen (Bounding Box)
	LOC_OUTSIDE  	= 6,		// ausserhalb (Bounding Box)
	
	LOC_FORCE_DWORD = 0x7fffffff	// Unbenutzt, Wert als 32bit kompilieren
};
typedef LOCATION	VSLOCATION;

/*---------------------------------------------------------------------------
	ORIENTATION-Enumeration (Objekte in Bezug aufeinander)
---------------------------------------------------------------------------*/
typedef enum ORIENTATION {
	OR_CCW			= -1,		// liegen entgegen dem Uhrzeigersinn
	OR_COLINEAR		= 0,		// liegen auf einer Linie (kolinear)
	OR_CW			= 1,		// liegen im Uhrzeigersinn

	OR_FORCE_DWORD = 0x7fffffff	// Unbenutzt, Wert als 32bit kompilieren
};
typedef ORIENTATION	VSORIENTATION;


#endif