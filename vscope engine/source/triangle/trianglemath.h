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

	Dateiname:		trianglemath.h
	Beschreibung:	Mathematische Funktionen bezüglich Dreiecken
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 21:59

	Changelog:
	[1]		09. Juli 2002 21:59
			Erstellt

===========================================================================*/

#pragma once

#ifndef TRIMATH_DEFINED
#define TRIMATH_DEFINED
#endif

#include <math.h>
#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\enums-math.h"
#include "..\fastmath\fastassort.h"
#include "..\plane\plane.h"
#include "..\lines\lineseg.h"
#include "..\vektoren\vector2.h"
#include "..\vektoren\vector3.h"
#include "..\triangle\triangle3.h"
#include "..\bounding\aabbox.h"

#pragma intrinsic(memcpy)

namespace TRIANGLE {


/*---------------------------------------------------------------------------
	Vorwärtsdeklaration
---------------------------------------------------------------------------*/
VECTOR3		GetBaryCentric(const TRIANGLE3 &Triangle, const float f, const float g);
VECTOR3		GetBaryCentric(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const float f, const float g);
VECTOR2		GetBaryCentric(const VECTOR2 &v0, const VECTOR2 &v1, const VECTOR2 &v2, const float f, const float g);
VECTOR3		GetCenter(const TRIANGLE3 &Triangle);
VECTOR3		GetCenter(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const float f, const float g);
VECTOR2		GetCenter(const VECTOR2 &v0, const VECTOR2 &v1, const VECTOR2 &v2, const float f, const float g);
bool		GetIntersection(const TRIANGLE3 &Triangle, const VECTOR3 &line_a, const VECTOR3 &line_b, VECTOR3* out_point );
bool		GetIntersection(const TRIANGLE3 &Triangle, const LINESEG &line, VECTOR3* point );
bool		GetIntersection(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &line_a, const VECTOR3 &line_b, VECTOR3* out_point );
bool		GetIntersection(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const LINESEG &line, VECTOR3* point );
LOCATION	GetLocation(const TRIANGLE3 &Triangle, const PLANE &plane);
LOCATION	GetLocation(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const PLANE &plane);
LOCATION	GetLocation(const LINESEG &line, const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2);
bool		TestInsideAABB(const TRIANGLE3 &Triangle, const VECTOR3 &point);
bool		TestPointInside(const TRIANGLE3 &Triangle, const VECTOR3 &point);
bool		TestInsideAABB(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &point);
bool		TestPointInside(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &point);

/*---------------------------------------------------------------------------
	Die Funktionen
---------------------------------------------------------------------------*/

/*------------------------------------------------------------
/|	Funktion:		GetBaryCentric()
/|	Beschreibung:	Berechnet die baryzentrischen Koordinaten
/|					des gegebenen Dreiecks
/|	Parameter:		Triangle (TRIANGLE3), f, g (float)
/|	Rückgabe:		VECTOR3
/|  2002-07-09 22:07 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 GetBaryCentric(const TRIANGLE3 &Triangle, const float f, const float g) {
	VECTOR3 Vec3;
	D3DXVec3BaryCentric((D3DXVECTOR3*)&Vec3, (D3DXVECTOR3*)&Triangle.v0, (D3DXVECTOR3*)&Triangle.v1, (D3DXVECTOR3*)&Triangle.v2, f, g);
	return Vec3;
}

/*------------------------------------------------------------
/|	Funktion:		GetBaryCentric()
/|	Beschreibung:	Berechnet die baryzentrischen Koordinaten
/|					des gegebenen Dreiecks
/|	Parameter:		v0, v1, v2 (VECTOR3), f, g (float)
/|	Rückgabe:		VECTOR3
/|  2002-07-09 22:07 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 GetBaryCentric(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const float f, const float g) {
	VECTOR3 Vec3;
	D3DXVec3BaryCentric((D3DXVECTOR3*)&Vec3, (D3DXVECTOR3*)&v0, (D3DXVECTOR3*)&v1, (D3DXVECTOR3*)&v2, f, g);
	return Vec3;
}

/*------------------------------------------------------------
/|	Funktion:		GetBaryCentric()
/|	Beschreibung:	Berechnet die baryzentrischen Koordinaten
/|					des gegebenen 2D-Dreiecks
/|	Parameter:		v0, v1, v2 (VECTOR2), f, g (float)
/|	Rückgabe:		VECTOR2
/|  2002-07-09 22:07 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR2 GetBaryCentric(const VECTOR2 &v0, const VECTOR2 &v1, const VECTOR2 &v2, const float f, const float g) {
	VECTOR2 Vec2;
	D3DXVec2BaryCentric((D3DXVECTOR2*)&Vec2, (D3DXVECTOR2*)&v0, (D3DXVECTOR2*)&v1, (D3DXVECTOR2*)&v2, f, g);
	return Vec2;
}

/*------------------------------------------------------------
/|	Funktion:		GetCenter()
/|	Beschreibung:	Berechnet den Mittelpunkt des gegebenen Dreiecks
/|	Parameter:		Triangle (TRIANGLE3)
/|	Rückgabe:		VECTOR3
/|  2002-07-09 22:07 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 GetCenter(const TRIANGLE3 &Triangle) {
	return GetBaryCentric(Triangle, VAL1d3, VAL1d3);
}

/*------------------------------------------------------------
/|	Funktion:		GetCenter()
/|	Beschreibung:	Berechnet den Mittelpunkt des gegebenen Dreiecks
/|	Parameter:		v0, v1, v2 (VECTOR3)
/|	Rückgabe:		VECTOR3
/|  2002-07-09 22:07 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 GetCenter(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2) {
	return GetBaryCentric(v0, v1, v2, VAL1d3, VAL1d3);
}

/*------------------------------------------------------------
/|	Funktion:		GetCenter()
/|	Beschreibung:	Berechnet den Mittelpunkt des gegebenen 2D-Dreiecks
/|	Parameter:		v0, v1, v2 (VECTOR2)
/|	Rückgabe:		VECTOR2
/|  2002-07-09 22:07 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR2 GetCenter(const VECTOR2 &v0, const VECTOR2 &v1, const VECTOR2 &v2) {
	return GetBaryCentric(v0, v1, v2, VAL1d3, VAL1d3);
}

/*------------------------------------------------------------
/|	Funktion:		GetIntersection()
/|	Beschreibung:	Überprüft, ob (und wo) eine Linie das
/|					Dreieck schneidet
/|	Parameter:		Triangle (TRIANGLE3) line_a, line_b (VECTOR3), *out_point (VECTOR3)
/|	Rückgabe:		bool, point (über Parameterliste)
/|  2002-07-09 22:23 MMT
/+------------------------------------------------------------*/
VSINLINE bool GetIntersection(const TRIANGLE3 &Triangle, const VECTOR3 &line_a, const VECTOR3 &line_b, VECTOR3* out_point ) {
	PLANE Testplane(Triangle.v0, Triangle.v1, Triangle.v2);
	VECTOR3 planehit = Testplane.GetIntersection(line_a, line_b);
	if(out_point!=NULL) memcpy(out_point, &planehit, sizeof(VECTOR3));
	return TestPointInside(Triangle, planehit);
}

/*------------------------------------------------------------
/|	Funktion:		GetIntersection()
/|	Beschreibung:	Überprüft, ob (und wo) eine Linie das
/|					Dreieck schneidet
/|	Parameter:		Triangle (TRIANGLE3) line (LINESEG), *out_point (VECTOR3)
/|	Rückgabe:		bool, point (über Parameterliste)
/|  2002-07-09 22:23 MMT
/+------------------------------------------------------------*/
VSINLINE bool GetIntersection(const TRIANGLE3 &Triangle, const LINESEG &line, VECTOR3* out_point ) {
	PLANE Testplane(Triangle.v0, Triangle.v1, Triangle.v2);
	VECTOR3 planehit = Testplane.GetIntersection(line);
	if(out_point!=NULL) memcpy(out_point, &planehit, sizeof(VECTOR3));
	return TestPointInside(Triangle, planehit);
}

/*------------------------------------------------------------
/|	Funktion:		GetIntersection()
/|	Beschreibung:	Überprüft, ob (und wo) eine Linie das
/|					Dreieck schneidet
/|	Parameter:		v0, v1, v2 (VECTOR3) line_a, line_b (VECTOR3), *out_point (VECTOR3)
/|	Rückgabe:		bool, point (über Parameterliste)
/|  2002-07-09 22:27 MMT
/+------------------------------------------------------------*/
VSINLINE bool GetIntersection(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &line_a, const VECTOR3 &line_b, VECTOR3* out_point ) {
	PLANE Testplane(v0, v1, v2);
	VECTOR3 planehit = Testplane.GetIntersection(line_a, line_b);
	if(out_point!=NULL) memcpy(out_point, &planehit, sizeof(VECTOR3));
	return TestPointInside(v0, v1, v2, planehit);
}

/*------------------------------------------------------------
/|	Funktion:		GetIntersection()
/|	Beschreibung:	Überprüft, ob (und wo) eine Linie das
/|					Dreieck schneidet
/|	Parameter:		v0, v1, v2 (VECTOR3) line (LINESEG), *out_point (VECTOR3)
/|	Rückgabe:		bool, point (über Parameterliste)
/|  2002-07-09 22:27 MMT
/+------------------------------------------------------------*/
VSINLINE bool GetIntersection(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const LINESEG &line, VECTOR3* out_point ) {
	PLANE Testplane(v0, v1, v2);
	VECTOR3 planehit = Testplane.GetIntersection(line);
	if(out_point!=NULL) memcpy(out_point, &planehit, sizeof(VECTOR3));
	return TestPointInside(v0, v1, v2, planehit);
}

/*------------------------------------------------------------
/|	Funktion:		GetLocation()
/|	Beschreibung:	Liefert eine Positionsangabe des Dreiecks 
/|					in Bezug auf eine Ebene
/|	Parameter:		Triangle (TRIANGLE3), plane (PLANE)
/|	Rückgabe:		LOCATION
/|  2002-07-09 22:08 MMT
/+------------------------------------------------------------*/
VSINLINE LOCATION GetLocation(const TRIANGLE3 &Triangle, const PLANE &plane) {
	VECTOR3 vec[] = { Triangle.v0, Triangle.v1, Triangle.v2 };
	return plane.GetLocation(vec, 3);
}

/*------------------------------------------------------------
/|	Funktion:		GetLocation()
/|	Beschreibung:	Liefert eine Positionsangabe des Dreiecks 
/|					in Bezug auf eine Ebene
/|	Parameter:		v0, v1, v2 (VECTOR3), plane (PLANE)
/|	Rückgabe:		LOCATION
/|  2002-07-09 22:08 MMT
/+------------------------------------------------------------*/
VSINLINE LOCATION GetLocation(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const PLANE &plane) {
	VECTOR3 vec[] = { v0, v1, v2 };
	return plane.GetLocation(vec, 3);
}

/*------------------------------------------------------------
/|	Funktion:		GetLocation()
/|	Beschreibung:	Liefert eine Positionsangabe einer Linie
/|					in Bezug auf ein Dreieck
/|	Parameter:		line (LINESEG), v0, v1, v2 (VECTOR3)
/|	Rückgabe:		LOCATION
/|  2002-07-09 22:09 MMT
/+------------------------------------------------------------*/
VSINLINE LOCATION GetLocation(const LINESEG &line, const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2) {
	// Liegen Start- und Endpunkt der Linie auf der Plane des Dreiecks?
	PLANE Testplane(v0, v1, v2);
	LOCATION Loc = Testplane.GetLocation(line.v0);
	LOCATION Loc2 = Testplane.GetLocation(line.v1);
	VECTOR3 Point;
	if((Loc==LOC_COPLANAR) && (Loc2==LOC_COPLANAR)) {
		// Die Punkte liegen beide auf der Plane.
		if(GetIntersection(v0, v1, v2, line, NULL)) return LOC_COPLANAR;
	}
	return LOC_UNDEFINED; // die Linie liegt irgendwie
}

/*------------------------------------------------------------
/|	Funktion:		TestInsideAABB()
/|	Beschreibung:	Liefert eine booleesche Aussage darüber ob 
/|					ein Punkt in der AABB eines Dreiecks liegt
/|	Parameter:		Triangle (TRIANGLE3), point (VECTOR3)
/|	Rückgabe:		bool
/|  2002-07-09 22:14 MMT
/+------------------------------------------------------------*/
VSINLINE bool TestInsideAABB(const TRIANGLE3 &Triangle, const VECTOR3 &point) {
	if (point.x > MAX3(Triangle.v0.x, Triangle.v1.x, Triangle.v2.x)) return false;
	if (point.y > MAX3(Triangle.v0.y, Triangle.v1.y, Triangle.v2.y)) return false;
	if (point.z > MAX3(Triangle.v0.z, Triangle.v1.z, Triangle.v2.z)) return false;
	if (point.x < MIN3(Triangle.v0.x, Triangle.v1.x, Triangle.v2.x)) return false;
	if (point.y < MIN3(Triangle.v0.y, Triangle.v1.y, Triangle.v2.y)) return false;
	if (point.z < MIN3(Triangle.v0.z, Triangle.v1.z, Triangle.v2.z)) return false;
	return true;
}

/*------------------------------------------------------------
/|	Funktion:		TestPointInside()
/|	Beschreibung:	Liefert eine booleesche Aussage darüber ob 
/|					ein Punkt in einem Dreieck liegt
/|	Parameter:		Triangle (TRIANGLE3), point (VECTOR3)
/|	Rückgabe:		bool
/|  2002-07-09 22:12 MMT
/+------------------------------------------------------------*/
VSINLINE bool TestPointInside(const TRIANGLE3 &Triangle, const VECTOR3 &point) {
	if(!TestInsideAABB(Triangle, point)) return false;
	long sign12 = SIGN3((Triangle.v0-Triangle.v1) CROSS (Triangle.v0-point));
	long sign23 = SIGN3((Triangle.v1-Triangle.v2) CROSS (Triangle.v1-point));
	long sign31 = SIGN3((Triangle.v2-Triangle.v0) CROSS (Triangle.v2-point));
	return ((sign12 == sign23) && (sign23 == sign31));
}

/*------------------------------------------------------------
/|	Funktion:		TestInsideAABB()
/|	Beschreibung:	Liefert eine booleesche Aussage darüber ob 
/|					ein Punkt in der AABB eines Dreiecks liegt
/|	Parameter:		v0, v1, v2 (VECTOR3)), point (VECTOR3)
/|	Rückgabe:		bool
/|  2002-07-09 22:14 MMT
/+------------------------------------------------------------*/
VSINLINE bool TestInsideAABB(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &point) {
	if (point.x > MAX3(v0.x, v1.x, v2.x)) return false;
	if (point.y > MAX3(v0.y, v1.y, v2.y)) return false;
	if (point.z > MAX3(v0.z, v1.z, v2.z)) return false;
	if (point.x < MIN3(v0.x, v1.x, v2.x)) return false;
	if (point.y < MIN3(v0.y, v1.y, v2.y)) return false;
	if (point.z < MIN3(v0.z, v1.z, v2.z)) return false;
	return true;
}

/*------------------------------------------------------------
/|	Funktion:		TestPointInside()
/|	Beschreibung:	Liefert eine booleesche Aussage darüber ob 
/|					ein Punkt in einem Dreieck liegt
/|	Parameter:		v0, v1, v2 (VECTOR3), point (VECTOR3)
/|	Rückgabe:		bool
/|  2002-07-09 22:12 MMT
/+------------------------------------------------------------*/
VSINLINE bool TestPointInside(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &point) {
	if(!TestInsideAABB(v0, v1, v2, point)) return false;
	long sign12 = SIGN3((v0-v1) CROSS (v0-point));
	long sign23 = SIGN3((v1-v2) CROSS (v1-point));
	long sign31 = SIGN3((v2-v0) CROSS (v2-point));
	return ((sign12 == sign23) && (sign23 == sign31));
}

/*------------------------------------------------------------
/|	Funktion:		GetAABB()
/|	Beschreibung:	Liefert die AABB des Dreiecks
/|	Parameter:		Triangle (TRIANGLE3), *out_min, *out_max (VECTOR3)
/|	Rückgabe:		*out_min, *out_max (über Parameter)
/|  2002-07-09 22:36 MMT
/+------------------------------------------------------------*/
VSINLINE void GetAABB(const TRIANGLE3 &Triangle, VECTOR3 *out_min, VECTOR3 *out_max) {
	VECTOR3 min, max;
	min.x = MIN3(Triangle.v0.x, Triangle.v1.x, Triangle.v2.x);
	min.y = MIN3(Triangle.v0.y, Triangle.v1.y, Triangle.v2.y);
	min.z = MIN3(Triangle.v0.z, Triangle.v1.z, Triangle.v2.z);
	max.x = MAX3(Triangle.v0.x, Triangle.v1.x, Triangle.v2.x);
	max.y = MAX3(Triangle.v0.y, Triangle.v1.y, Triangle.v2.y);
	max.z = MAX3(Triangle.v0.z, Triangle.v1.z, Triangle.v2.z);
	memcpy(out_min, &min, sizeof(VECTOR3));
	memcpy(out_max, &max, sizeof(VECTOR3));
}

/*------------------------------------------------------------
/|	Funktion:		GetAABB()
/|	Beschreibung:	Liefert die AABB des Dreiecks
/|	Parameter:		v0, v1, v2 (VECTOR3), *out_min, *out_max (VECTOR3)
/|	Rückgabe:		*out_min, *out_max (über Parameter)
/|  2002-07-09 22:36 MMT
/+------------------------------------------------------------*/
VSINLINE void GetAABB(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, VECTOR3 *out_min, VECTOR3 *out_max) {
	VECTOR3 min, max;
	min.x = MIN3(v0.x, v1.x, v2.x);
	min.y = MIN3(v0.y, v1.y, v2.y);
	min.z = MIN3(v0.z, v1.z, v2.z);
	max.x = MAX3(v0.x, v1.x, v2.x);
	max.y = MAX3(v0.y, v1.y, v2.y);
	max.z = MAX3(v0.z, v1.z, v2.z);
	memcpy(out_min, &min, sizeof(VECTOR3));
	memcpy(out_max, &max, sizeof(VECTOR3));
}


#ifdef AABBOX3_DEFINED
/*------------------------------------------------------------
/|	Funktion:		GetAABB()
/|	Beschreibung:	Liefert die AABB des Dreiecks
/|	Parameter:		v0, v1, v2 (VECTOR3), *Box (AABBOX3)
/|	Rückgabe:		*Box (über Parameter)
/|  2002-07-09 22:37 MMT
/+------------------------------------------------------------*/
VSINLINE void GetAABB(const TRIANGLE3 &Triangle, AABBOX3 *Box) {
	Box->Create(MIN3(Triangle.v0.x, Triangle.v1.x, Triangle.v2.x), MIN3(Triangle.v0.y, Triangle.v1.y, Triangle.v2.y), MIN3(Triangle.v0.z, Triangle.v1.z, Triangle.v2.z), MAX3(Triangle.v0.x, Triangle.v1.x, Triangle.v2.x), MAX3(Triangle.v0.y, Triangle.v1.y, Triangle.v2.y), MAX3(Triangle.v0.z, Triangle.v1.z, Triangle.v2.z));
}

/*------------------------------------------------------------
/|	Funktion:		GetAABB()
/|	Beschreibung:	Liefert die AABB des Dreiecks
/|	Parameter:		v0, v1, v2 (VECTOR3), *Box (AABBOX3)
/|	Rückgabe:		*Box (über Parameter)
/|  2002-07-09 22:37 MMT
/+------------------------------------------------------------*/
VSINLINE void GetAABB(const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2, AABBOX3 *Box) {
	Box->Create(MIN3(v0.x, v1.x, v2.x), MIN3(v0.y, v1.y, v2.y), MIN3(v0.z, v1.z, v2.z), MAX3(v0.x, v1.x, v2.x), MAX3(v0.y, v1.y, v2.y), MAX3(v0.z, v1.z, v2.z));
}

} // namespace
using namespace TRIANGLE;

#endif