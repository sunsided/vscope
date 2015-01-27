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

	Dateiname:		aabsphere.h
	Beschreibung:	Axis Aligned Bounding Sphere Definition
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 22:50

	Changelog:
	[1]		09. Juli 2002 22:50

===========================================================================*/

#pragma once

#ifndef AABSPHERE3_DEFINED
#define AABSPHERE3_DEFINED
#endif

#include "..\defines.h"
#include "..\vektoren\vector3.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Struktur für den 2D-Vektor
---------------------------------------------------------------------------*/
struct AABSPHERE3 {
//:: Die Membervariablen ....................................................
public:		
						VECTOR3 m_loc;
						float m_radius;

//:: Die Konstruktoren ......................................................
public:
						AABSPHERE3();
						AABSPHERE3( float radius, VECTOR3 loc );					// Erstellt eine bsphere anhand des Radius
						AABSPHERE3( VECTOR3 loc, int nVerts, VECTOR3* pList );	// Erstellt eine bsphere über eine Anzahl von Vertices

//:: Das Interface ..........................................................
public:
	// Operatoren: Binär ....................................................
	AABSPHERE3&			operator += ( const VECTOR3& in );
	AABSPHERE3&			operator -= ( const VECTOR3& in );

	// Funktionen: Einfach ..................................................
	static bool			Intersect( AABSPHERE3& a, AABSPHERE3& b );
	void				UpdateBounds( const VECTOR3 &in );
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef AABSPHERE3					*LPAABSPHERE3;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 AABSPHERE3		AABSPHERE3A16;
typedef _ALIGN_16 AABSPHERE3		*LPAABSPHERE3A16;

typedef _ALIGN_32 AABSPHERE3		AABSPHERE3A32;
typedef _ALIGN_32 AABSPHERE3		*LPAABSPHERE3A32;

typedef _CACHEALIGN AABSPHERE3		AABSPHERE3AC;
typedef _CACHEALIGN AABSPHERE3		*LPAABSPHERE3AC;*/