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

	Dateiname:		plane.h
	Beschreibung:	Ebene Definition
	Revision:		1
	Erstellt:		MMT, 07. Juli 2002 19:33

	Changelog:
	[1]		07. Juli 2002 19:33

===========================================================================*/

#pragma once

#ifndef PLANE_DEFINED
#define PLANE_DEFINED
#endif

#include "..\defines.h"
#include "..\enums-math.h"
#include "..\include-direct3d.h"
#include "..\vektoren\define-vectorops.h"
//#include "..\polygon\polygon.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct VECTOR3;
struct VECTOR4;
struct LINESEG;
struct AABSPHERE3;
struct POLYGON3;

/*---------------------------------------------------------------------------
	Struktur für die Plane
---------------------------------------------------------------------------*/
struct PLANE {
//:: Die Membervariablen ....................................................
public:
	union {
					struct {float a, b, c, d; };
					struct {float x, y, z, w; };
	};

//:: Die Konstruktoren ......................................................
public:
							PLANE( const VECTOR3& N, float D);
							PLANE( const VECTOR3& a, const VECTOR3& b, const VECTOR3& c);
							PLANE( const VECTOR3& norm, const VECTOR3& loc);
							PLANE( const VECTOR4& vec);
							PLANE( const POLYGON3& poly );
							PLANE() { }
							PLANE( CONST float* pf );
							PLANE( float fa, float fb, float fc, float fd );

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
							operator float* ();
							operator const float* () const;
							operator VECTOR3 ();
							operator const VECTOR3 () const;
							operator VECTOR4 ();
							operator const VECTOR4 () const;
							operator D3DXPLANE ();
							operator const D3DXPLANE () const;

	// Operatoren: Unär .....................................................
	PLANE					operator + () const;
	PLANE					operator - () const;

	// Operatoren: Vergleich ................................................
	bool					operator == ( CONST PLANE& p ) const;
	bool					operator != ( CONST PLANE& p ) const;
	
	// Operatoren: Kopie ....................................................
	const PLANE&			operator = (const PLANE& Plane);

	// Operatoren: Zuweisung ................................................
	void					Assign( const VECTOR3& N, float D);
	void					Assign( const VECTOR3& a, const VECTOR3& b, const VECTOR3& c);
	void					Assign( const VECTOR3& norm, const VECTOR3& loc);
	void					Assign( const VECTOR4& vec);
	void					Assign( const POLYGON3& poly );
	void					Assign( CONST float* pf );
	void					Assign( float fa, float fb, float fc, float fd );
	void					Assign( const D3DXPLANE& plane);

	// Funktionen: Einfache .................................................
	LOCATION				GetLocation( const VECTOR3& point ) const;				// Ist ein Punkt vor, hinter oder auf der Plane?
	LOCATION				GetLocation( const POLYGON3 &poly ) const;				// Ist eine Punktliste (in Form des Polygons) vor, auf, durch oder hinter?
	LOCATION				GetLocation( VECTOR3 *list, int num ) const;			// Ist eine Punktliste vor, auf, durch oder hinter?
	LOCATION				GetLocation( const AABSPHERE3& sphere ) const;				// Ist eine Bounding Sphere vor, durch oder hinter?
	const VECTOR3			GetIntersection( const VECTOR3 &a, const VECTOR3 &b ) const;	// Liefert den Schnittpunkt der Linie a->b mit der Plane
	const VECTOR3			GetIntersection( const LINESEG &line ) const;
	bool					Split( const POLYGON3& in, POLYGON3 *front, POLYGON3 *back ) const;	// Liefert zwei Polygone zurück: eines vor und eines hinter der Plane
	bool					Split( const LINESEG& in, LINESEG *front, LINESEG *back ) const;		// Liefert zwei Linienteile zurück: eines vor und eines dahinter
	const VECTOR3			BringToPlane( const VECTOR3& pt );
	bool					Clip( const POLYGON3& in, POLYGON3 *out ) const;			// Liefert ein geclipptes Polygon zurück, das sich vor der Plane befindet
	void					Flip();													// Dreht die Plane um (front/back)

	VECTOR3					GetNormal() const;
	float					GetDistance() const;
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PLANE				*LPPLANE;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PLANE		PLANEA16;
typedef _ALIGN_16 PLANE		*LPPLANEA16;

typedef _ALIGN_32 PLANE		PLANEA32;
typedef _ALIGN_32 PLANE		*LPPLANEA32;

typedef _CACHEALIGN PLANE	PLANEAC;
typedef _CACHEALIGN PLANE	*LPPLANEAC;*/