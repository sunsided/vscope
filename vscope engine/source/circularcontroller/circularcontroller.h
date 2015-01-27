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

	Dateiname:		circularcontroller.h
	Beschreibung:	Circular Controller 2D Definition
	Revision:		1
	Erstellt:		MMT, 16. Oktober 2002 22:12

	Changelog:
	[1]		16. Oktober 2002 22:12

===========================================================================*/

#pragma once

#ifndef CIRCULARCONTROLLER2D_DEFINED
#define CIRCULARCONTROLLER2D_DEFINED
#endif

#include "..\defines.h"
#include "..\vektoren\vector3.h"

/*---------------------------------------------------------------------------
	Vorwärtsdeklaration
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Struktur für das Polygon
---------------------------------------------------------------------------*/
struct CIRCULARCONTROLLER2D {
//:: Die Membervariablen ....................................................
private:
	float					fRadius;		// Der Radius
	VECTOR3					vCenter;		// Der Mittelpunkt
	VECTOR3					vPosition;		// Position des Sattels
	float					fSpeed;			// Geschwindigkeit des Sattels
	float					fAngle;			// Der derzeitige Winkel
	float					fAngleStep;		// Die Schrittweite

public:


//:: Die Konstruktoren ......................................................
public:
	VSINLINE CIRCULARCONTROLLER2D() {
		fAngleStep = 0.01f;
		fAngle = 0.f;
		fSpeed = 1.f;
		vPosition = VECTOR3(0.f, 0.f, 0.f);
		vCenter = VECTOR3(0.f, 0.f, 0.f);
		fRadius = 1.f;
	};


//:: Die Destruktoren .......................................................
public:
	VSINLINE ~CIRCULARCONTROLLER2D() {
	}

//:: Das Interface ..........................................................
private:
	VSINLINE void			CalculatePosition();

public:
	VSINLINE void			Init(const VECTOR3 vCenter, const float fRadius, const float fSpeed);
	VSINLINE void			Update();
	VSINLINE VECTOR3		GetPosition();

};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef CIRCULARCONTROLLER2D				*LPCIRCULARCONTROLLER2D;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 CIRCULARCONTROLLER2D		CIRCULARCONTROLLER2DA16;
typedef _ALIGN_16 CIRCULARCONTROLLER2D		*LPCIRCULARCONTROLLER2DA16;

typedef _ALIGN_32 CIRCULARCONTROLLER2D		CIRCULARCONTROLLER2DA32;
typedef _ALIGN_32 CIRCULARCONTROLLER2D		*LPCIRCULARCONTROLLER2DA32;

typedef _CACHEALIGN CIRCULARCONTROLLER2D	CIRCULARCONTROLLER2DAC;
typedef _CACHEALIGN CIRCULARCONTROLLER2D	*LPCIRCULARCONTROLLER2DAC;*/