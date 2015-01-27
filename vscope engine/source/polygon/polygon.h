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

	Dateiname:		polygon.h
	Beschreibung:	Polygon (Template) Definition
	Revision:		2
	Erstellt:		MMT, 08. Juli 2002 01:43

	Changelog:
	[2]		10. Juli 2003 20:24, MMT
			Umgestellt auf VECTOR3
	[1]		08. Juli 2002 01:43

===========================================================================*/

#pragma once

#ifndef POLYGON3_DEFINED
#define POLYGON3_DEFINED

#include "..\defines.h"
#include "..\vektoren\vector3.h"
#include "..\triangle\triangle3.h"

// MMT-FAN Triangulation
#define TRIANGULATE_MMTFAN


/*---------------------------------------------------------------------------
	Vorwärtsdeklaration
---------------------------------------------------------------------------*/
//struct VECTOR3;
struct PLANE;
struct AABBOX3;

/*---------------------------------------------------------------------------
	Struktur für das Polygon
---------------------------------------------------------------------------*/
struct POLYGON3 {
//:: Die Membervariablen ....................................................
public:
	VECTOR3					vCenter;
	VECTOR3					*pList;
	union {
		unsigned long		nElem; // number of elements in the polygon
		unsigned long		m_iElementCount; // number of elements in the polygon
	};
	union {
		unsigned long		maxElem;
		unsigned long		m_iMaxElementCount;
	};
	

//:: Die Konstruktoren ......................................................
public:
							VSINLINE POLYGON3();
							VSINLINE POLYGON3( int maxSize );
							VSINLINE POLYGON3( const POLYGON3 &in );

//:: Die Destruktoren .......................................................
public:
							VSINLINE ~POLYGON3();

//:: Das Interface ..........................................................
public:
	// Operatoren: Kopie ....................................................
	VSINLINE POLYGON3&		operator=( const POLYGON3 &in );

	// Operatoren: Erweiterte Funktionen ....................................
	VSINLINE void			CloneData( const POLYGON3 &in );
	VSINLINE void			DestroyData( );

	VSINLINE bool			Clip( const PLANE &in_Plane, POLYGON3 *out ) const;			// Liefert ein geclipptes Polygon zurück, das sich vor der Plane befindet

	VSINLINE float			GetArea() const;

	void					GetCenterFresh(VECTOR3 *out_vCenter);						// Berechnet den Mittelpunkt des Polygons
	VECTOR3					GetCenterFresh();											// Berechnet den Mittelpunkt des Polygons
	void					GetCenter(VECTOR3 *out_vCenter) const;						// Liefert den Mittelpunkt des Polygons
	VECTOR3					GetCenter() const;											// Liefert den Mittelpunkt des Polygons	
	void					CalculateCenter();											// Berechnet und setzt den Polygonmittelpunkt

	void					GetAABBCalcCenter(AABBOX3 *out_AABB);						// Liefert die AABB des Polygons
	void					GetAABB(AABBOX3 *out_AABB);									// Liefert die AABB des Polygons - Berechnet das Zentrum des Polygons nicht neu!

	void VSFASTCALL 		Optimize();

							// Achtung! Triangulate erwartet ein allokiertes, ausreichend großes Array!
	VSINLINE void			Triangulate(TRIANGLE3 *out_TriangleList) const;
	VSINLINE unsigned int	TriangulationCost() const;	// Liefert die Anzahl der entstehenden Dreiecke

private:
	VSINLINE void			TriangulateMMTFan(TRIANGLE3 *out_TriangleList) const;
	VSINLINE unsigned int	TriangulationCostMMTFan() const;	
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef POLYGON3						*LPPOLYGON3;


#endif