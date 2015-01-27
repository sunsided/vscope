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

	Dateiname:		lineseg.h
	Beschreibung:	Liniensegment Definition
	Revision:		1
	Erstellt:		MMT, 08. Juli 2002 01:28

	Changelog:
	[1]		08. Juli 2002 01:28

===========================================================================*/

#pragma once

#ifndef LINESEG_DEFINED
#define LINESEG_DEFINED
#endif

#include "..\defines.h"
#include "..\vektoren\vector3.h"

/*---------------------------------------------------------------------------
	Struktur für das Liniensegment
---------------------------------------------------------------------------*/
struct LINESEG {
//:: Die Membervariablen ....................................................
public:
	VECTOR3	v0, v1;

//:: Die Konstruktoren ......................................................
public:
							LINESEG();
							LINESEG( const VECTOR3 &a, const VECTOR3 &b );

//:: Das Interface ..........................................................
public:
	// Operatoren: Zugriff ..................................................
	VECTOR3					operator [] ( int x );
	
	float					GetLenght() const;
	float					GetLenghtInv() const;
	float					GetLenghtSquared() const;

	float					GetDistanceLine(VECTOR3& in_Point) const;	// Die Entfernung des Punktes von der Geraden durch Line.v0 und Line.v1
	void					ProjectPoint(VECTOR3* out_Projected, VECTOR3& in_Point) const;
	void					ProjectPointLine(VECTOR3* out_Projected, VECTOR3& in_Point) const;
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef LINESEG					*LPLINESEG;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 LINESEG		LINESEGA16;
typedef _ALIGN_16 LINESEG		*LPLINESEGA16;

typedef _ALIGN_32 LINESEG		LINESEGA32;
typedef _ALIGN_32 LINESEG		*LPLINESEGA32;

typedef _CACHEALIGN LINESEG		LINESEGAC;
typedef _CACHEALIGN LINESEG		*LPLINESEGAC;*/