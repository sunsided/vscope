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

	Dateiname:		triangle3.h
	Beschreibung:	Triangle-Vektor3 Definition
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 19:04

	Changelog:
	[1]		09. Juli 2002 19:04

===========================================================================*/

#pragma once

#ifndef TRIANGLE3_DEFINED
#define TRIANGLE3_DEFINED
#endif

#include "..\defines.h"
#include "..\vektoren\vector3.h"
#include "..\enums-math.h"

/*---------------------------------------------------------------------------
	Vorwärtsdeklaration
---------------------------------------------------------------------------*/
//struct VECTOR3;
struct POLYGON3;
struct PLANE;
struct AABBOX3;
struct LINESEG;
//enum LOCATION;

/*---------------------------------------------------------------------------
	Struktur für das Dreieck
---------------------------------------------------------------------------*/
struct TRIANGLE3 {
//:: Die Membervariablen ....................................................
public:
	VECTOR3					v0, v1, v2;

//:: Die Konstruktoren ......................................................
public:
							TRIANGLE3();
							TRIANGLE3( const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2 );

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
							operator PLANE* () const;
							operator const PLANE* () const;
							operator POLYGON3 () const;
							operator const POLYGON3 () const;
							operator VECTOR3* () const;
							operator const VECTOR3* () const;

	// Operatoren: Zugriff ..................................................
							VECTOR3& operator () ( const unsigned long iIndex );
							VECTOR3 operator () ( const unsigned long iIndex ) const;

	// Operatoren: Unär .....................................................
	TRIANGLE3				operator + () const;
	TRIANGLE3				operator - () const;

	// Operatoren: Binär ....................................................
	bool					operator == ( const TRIANGLE3& p ) const;
	bool					operator != ( const TRIANGLE3& p ) const;
	void					operator =  ( const TRIANGLE3& p );

	// Funktionen: Erweiterte ...............................................
	VECTOR3					GetBaryCentric(const float f, const float g) const;
	VECTOR3					GetCenter() const;
	VECTOR3					GetPoint(const int n = 0) const;
	LOCATION				GetLocation(const PLANE &plane) const;
	LOCATION				GetLocation(const LINESEG &line) const;
	bool					TestPointInside(const VECTOR3 &point) const;		// Testet, ob ein Punkt im Dreieck liegt
	bool					TestInsideAABB(const VECTOR3 &point) const;			// Testet, ob ein Punkt innerhalb der Bounding Box des Dreiecks liegt

	bool					GetIntersection( const VECTOR3 &a, const VECTOR3 &b, VECTOR3* point ) const;	// Liefert den Schnittpunkt der Linie a->b mit der Plane
	bool					GetIntersection( const LINESEG &line, VECTOR3* point ) const;

	// TODO: GetBSPHERE einbinden für Tri3
	// TODO: Min und Max Points auslesen für Tri3 - vs_pipe-Enums.h!
	AABBOX3					GetAABB() const;					// Liefert die Axis Aligned Bounding Box
	void					GetAABB(AABBOX3 *Box) const;		// Liefert die Axis Aligned Bounding Box

	float					GetArea() const;

	void					Assign(const VECTOR3 &in_v0, const VECTOR3 &in_v1, const VECTOR3 &in_v2);
	void					Subdivide(TRIANGLE3 *out_Tri1, TRIANGLE3 *out_Tri2, TRIANGLE3 *out_Tri3, TRIANGLE3 *out_Tri4) const;

	void					GetNormal(VECTOR3 *out_Normal) const;
	VECTOR3					GetNormal() const;
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef TRIANGLE3				*LPTRIANGLE3;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 TRIANGLE3		TRIANGLE3A16;
typedef _ALIGN_16 TRIANGLE3		*LPTRIANGLE3A16;

typedef _ALIGN_32 TRIANGLE3		TRIANGLE3A32;
typedef _ALIGN_32 TRIANGLE3		*LPTRIANGLE3A32;

typedef _CACHEALIGN TRIANGLE3	TRIANGLE3AC;
typedef _CACHEALIGN TRIANGLE3	*LPTRIANGLE3AC;*/