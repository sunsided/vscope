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

	Dateiname:		aabbox.h
	Beschreibung:	Axis Aligned Bounding Box Definition
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 22:50

	Changelog:
	[1]		09. Juli 2002 22:50

===========================================================================*/

#pragma once

#ifndef AABBOX3_DEFINED
#define AABBOX3_DEFINED
#endif

#include "..\defines.h"
#include "..\vektoren\vector3.h"
#include "..\plane\plane.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct LINESEG;
struct AABSPHERE3;

/*---------------------------------------------------------------------------
	Struktur für den 2D-Vektor
---------------------------------------------------------------------------*/
struct AABBOX3 {
//:: Die Membervariablen ....................................................
public:		
						VECTOR3 min, max;
						PLANE planeList[6];

//:: Die Konstruktoren ......................................................
public:
						AABBOX3();
						AABBOX3( const float x_min, const float y_min, const float z_min, const float x_max, const float y_max, const float z_max );
						AABBOX3( VECTOR3 &p_min, VECTOR3 &p_max );
						AABBOX3( VECTOR3 &center, float Seitenlaenge );

//:: Das Interface ..........................................................
public:
	// Operatoren: Zugriff ..................................................
	const PLANE			operator [] ( int x );

	// Operatoren: Binär ....................................................
	const AABBOX3		operator +	( const AABBOX3 &box );		// Liefert eine BB, die box und this umfasst
	const void			operator +=	( const AABBOX3 &box );		// vergrößert this, so dass this box umfasst

	// Funktionen: Zuweisung ................................................
	void				Create( const float x_min, const float y_min, const float z_min, const float x_max, const float y_max, const float z_max );
	void				Create( VECTOR3 &p_min, VECTOR3 &p_max );
	void				Create( VECTOR3 &center, float Seitenlaenge );	

	// Funktionen: Einfach ..................................................
	void				UpdateBounds( const VECTOR3 &in );
	void				ReCalcPlanes();
	bool				Clip( LINESEG *inLine, VECTOR3 *hitLoc );
	bool				Clip( LINESEG *inLine, LINESEG *clippedLine );

	// Funktionen: Konvertierung ............................................
	void				Convert(AABSPHERE3 &out_BSphere);
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef AABBOX3					*LPAABBOX3;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 AABBOX3		AABBOX3A16;
typedef _ALIGN_16 AABBOX3		*LPAABBOX3A16;

typedef _ALIGN_32 AABBOX3		AABBOX3A32;
typedef _ALIGN_32 AABBOX3		*LPAABBOX3A32;

typedef _CACHEALIGN AABBOX3		AABBOX3AC;
typedef _CACHEALIGN AABBOX3		*LPAABBOX3AC;*/