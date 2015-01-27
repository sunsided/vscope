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

	Dateiname:		triangle3.inl.h
	Beschreibung:	Triangle-Vektor3 Inline-Funktionen
	Revision:		2
	Erstellt:		MMT, 09. Juli 2002 19:04

	Changelog:
	[2]		13. Juli 2003 13:48, MMT
			GetArea() hinzugefügt
	[1]		09. Juli 2002 19:04

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "triangle3.h"
#include "..\fastmath\fastassort.h"
#include "..\lines\lineseg.h"
#include "..\plane\plane.h"
#include "..\bounding\aabbox.h"
#include "..\enums-math.h"

#include "..\vektoren\vector3.h"
#include "..\vektoren\vector3.inl.h"
#include "..\vektoren\vectormath.inl.h"
#include "..\polygon\polygon.inl.h"

#pragma intrinsic(memcpy, memcmp)

VSINLINE TRIANGLE3::TRIANGLE3() {
}

VSINLINE TRIANGLE3::TRIANGLE3( const VECTOR3 &v0, const VECTOR3 &v1, const VECTOR3 &v2 ) {
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
}

// ==== casting ====
VSINLINE TRIANGLE3::operator PLANE* () const {
	return &PLANE(this->v0, this->v1, this->v2);
}

VSINLINE TRIANGLE3::operator CONST PLANE* () const {
	return &PLANE(this->v0, this->v1, this->v2);
}

VSINLINE TRIANGLE3::operator POLYGON3 () const {
	POLYGON3 Test(3);
	Test.nElem = 3;
	/*
	Test.pList[0] = this->v0;
	Test.pList[1] = this->v1;
	Test.pList[2] = this->v2;
	*/
	memcpy(Test.pList, this, sizeof(TRIANGLE3));
	return Test;
}

VSINLINE TRIANGLE3::operator CONST POLYGON3 () const {
	POLYGON3 Test(3);
	Test.nElem = 3;
	/*
	Test.pList[0] = this->v0;
	Test.pList[1] = this->v1;
	Test.pList[2] = this->v2;
	*/
	memcpy(Test.pList, this, sizeof(TRIANGLE3));
	return Test;
}

VSINLINE TRIANGLE3::operator VECTOR3* () const {
	return &this->GetBaryCentric(VAL1d3, VAL1d3);
}

VSINLINE TRIANGLE3::operator const VECTOR3* () const {
	return &this->GetBaryCentric(VAL1d3, VAL1d3);
}

	// ==== Zugriffe ====
VSINLINE VECTOR3& TRIANGLE3::operator () ( const unsigned long iIndex ) {
	switch(iIndex) {
		case 0:
			return this->v0;
		case 1:
			return this->v1;
		case 2:
			return this->v2;
	}
	return this->v0;
}

VSINLINE VECTOR3 TRIANGLE3::operator () ( const unsigned long iIndex ) const {
	switch(iIndex) {
		case 0:
			return this->v0;
		case 1:
			return this->v1;
		case 2:
			return this->v2;
	}
	return this->v0;
}

// ==== unär ====
VSINLINE TRIANGLE3 TRIANGLE3::operator + () const {
	return *this;
}

VSINLINE TRIANGLE3 __declspec(deprecated) TRIANGLE3::operator - () const {
	//HACK: Unärer Operator - des Dreieck3-Typs muss überprüft werden
	return TRIANGLE3(-this->v0, -this->v1, -this->v2);
}

// ==== binär ====
VSINLINE bool TRIANGLE3::operator == ( const TRIANGLE3& p ) const {
	//return (this->v0==p.v0 && this->v1==p.v1 && this->v2==p.v2);
	return memcmp(this, &p, sizeof(TRIANGLE3))==0;
}

VSINLINE bool TRIANGLE3::operator != ( const TRIANGLE3& p ) const {
	//return !(this->v0==p.v0 && this->v1==p.v1 && this->v2==p.v2);
	return memcmp(this, &p, sizeof(TRIANGLE3))!=0;
}

VSINLINE void TRIANGLE3::operator = ( const TRIANGLE3& p ) {
	memcpy(this, &p, sizeof(TRIANGLE3));
}

VSINLINE VECTOR3 TRIANGLE3::GetBaryCentric(const float f, const float g) const {
	VECTOR3 Vec3;
	D3DXVec3BaryCentric((D3DXVECTOR3*)&Vec3, (D3DXVECTOR3*)&this->v0, (D3DXVECTOR3*)&this->v1, (D3DXVECTOR3*)&this->v2, f, g);
	return Vec3;
}

VSINLINE VECTOR3 TRIANGLE3::GetCenter() const {
	return this->GetBaryCentric(VAL1d3, VAL1d3);
}

VSINLINE VECTOR3 TRIANGLE3::GetPoint(const int n) const {
	switch(n) {
		case 0:
			return this->v0;
		case 1:
			return this->v1;
		case 2:
			return this->v2;
	}
	return this->v0;
}

VSINLINE LOCATION TRIANGLE3::GetLocation(const PLANE &plane) const {
	VECTOR3 vec[] = { this->v0, this->v1, this->v2 };
	return plane.GetLocation(vec, 3);
}

VSINLINE LOCATION TRIANGLE3::GetLocation(const LINESEG &line) const {
	// Liegen Start- und Endpunkt der Linie auf der Plane des Dreiecks?
	PLANE Testplane(this->v0, this->v1, this->v2);
	LOCATION Loc = Testplane.GetLocation(line.v0);
	LOCATION Loc2 = Testplane.GetLocation(line.v1);
	VECTOR3 Point;
	if((Loc==LOC_COPLANAR) && (Loc2==LOC_COPLANAR)) {
		// Die Punkte liegen beide auf der Plane.
		if(this->GetIntersection(line, NULL)) return LOC_COPLANAR;
	}
	return LOC_UNDEFINED; // die Linie liegt irgendwie
}

VSINLINE bool TRIANGLE3::TestPointInside(const VECTOR3 &point) const {
	if(!this->TestInsideAABB(point)) return FALSE;
	long sign12 = SIGN3((this->v0-this->v1) CROSS (this->v0-point));
	long sign23 = SIGN3((this->v1-this->v2) CROSS (this->v1-point));
	long sign31 = SIGN3((this->v2-this->v0) CROSS (this->v2-point));
	return ((sign12 == sign23) && (sign23 == sign31));
}

VSINLINE bool TRIANGLE3::TestInsideAABB(const VECTOR3 &point) const {
	if (point.x > MAX3(this->v0.x, this->v1.x, this->v2.x)) return FALSE;
	if (point.y > MAX3(this->v0.y, this->v1.y, this->v2.y)) return FALSE;
	if (point.z > MAX3(this->v0.z, this->v1.z, this->v2.z)) return FALSE;
	if (point.x < MIN3(this->v0.x, this->v1.x, this->v2.x)) return FALSE;
	if (point.y < MIN3(this->v0.y, this->v1.y, this->v2.y)) return FALSE;
	if (point.z < MIN3(this->v0.z, this->v1.z, this->v2.z)) return FALSE;
	return TRUE;
}

VSINLINE bool TRIANGLE3::GetIntersection( const VECTOR3 &a, const VECTOR3 &b, VECTOR3* point ) const {
	PLANE Testplane(this->v0, this->v1, this->v2);
	VECTOR3 planehit = Testplane.GetIntersection(a, b);
	if(point!=NULL) memcpy(point, &planehit, sizeof(VECTOR3));
	return this->TestPointInside(planehit);
}

VSINLINE bool TRIANGLE3::GetIntersection( const LINESEG &line, VECTOR3* point ) const {
	PLANE Testplane(this->v0, this->v1, this->v2);
	VECTOR3 planehit = Testplane.GetIntersection(line);
	if(point!=NULL) memcpy(point, &planehit, sizeof(VECTOR3));
	return this->TestPointInside(planehit);
}

VSINLINE AABBOX3 TRIANGLE3::GetAABB() const {
	AABBOX3 Box(MIN3(this->v0.x, this->v1.x, this->v2.x), MIN3(this->v0.y, this->v1.y, this->v2.y), MIN3(this->v0.z, this->v1.z, this->v2.z), MAX3(this->v0.x, this->v1.x, this->v2.x), MAX3(this->v0.y, this->v1.y, this->v2.y), MAX3(this->v0.z, this->v1.z, this->v2.z));
	return Box;
}

VSINLINE void TRIANGLE3::GetAABB(AABBOX3 *Box) const {
	Box->Create(MIN3(this->v0.x, this->v1.x, this->v2.x), MIN3(this->v0.y, this->v1.y, this->v2.y), MIN3(this->v0.z, this->v1.z, this->v2.z), MAX3(this->v0.x, this->v1.x, this->v2.x), MAX3(this->v0.y, this->v1.y, this->v2.y), MAX3(this->v0.z, this->v1.z, this->v2.z));
}


/*------------------------------------------------------------
/|	Funktion:		GetArea()
/|	Beschreibung:	Berechnet die Fläche des Dreiecks
/|	Parameter:		n/a
/|	Rückgabe:		Fläche (float)
/|  2003-07-13 13:46 MMT
/+------------------------------------------------------------*/
VSINLINE float TRIANGLE3::GetArea() const {
	VECTOR3 vEdge1 = v0 - v1;
	VECTOR3 vEdge2 = v2 - v1;
	VECTOR3 vNormal = VecCross(vEdge1, vEdge2);
	return vNormal.GetMag() * 0.5f;
}

/*------------------------------------------------------------
/|	Funktion:		Assign()
/|	Beschreibung:	Werte zuweisen
/|	Parameter:		Punkte 1-3
/|	Rückgabe:		n/a
/|  2003-07-21 07:24 MMT
/+------------------------------------------------------------*/
VSINLINE void TRIANGLE3::Assign(const VECTOR3 &in_v0, const VECTOR3 &in_v1, const VECTOR3 &in_v2) {
	v0 = in_v0;
	v1 = in_v1;
	v2 = in_v2;
}

/*------------------------------------------------------------
/|	Funktion:		Subdivide()
/|	Beschreibung:	Teilt das Dreieck in vier kleinere auf
/|	Parameter:		Ausgabe: Triangle 1-4
/|	Rückgabe:		n/a
/|  2003-07-21 07:24 MMT
/+------------------------------------------------------------*/
VSINLINE void TRIANGLE3::Subdivide(TRIANGLE3 *out_Tri1, TRIANGLE3 *out_Tri2, TRIANGLE3 *out_Tri3, TRIANGLE3 *out_Tri4) const {
	VECTOR3 vA = this->GetBaryCentric(0.5f, 0.f);
	VECTOR3 vB = this->GetBaryCentric(0.5f, 0.5f);
	VECTOR3 vC = this->GetBaryCentric(0.0f, 0.5f);
	out_Tri1->Assign(vA, v1, vB);	// oben
	out_Tri2->Assign(v0, vA, vC);	// links
	out_Tri3->Assign(vC, vA, vB);	// mitte
	out_Tri4->Assign(vC, vB, v2);	// rechts
}

/*------------------------------------------------------------
/|	Funktion:		GetNormal()
/|	Beschreibung:	Teilt das Dreieck in vier kleinere auf
/|	Parameter:		Ausgabe: Normal
/|	Rückgabe:		n/a
/|  2003-07-24 18:02 MMT
/+------------------------------------------------------------*/
VSINLINE void TRIANGLE3::GetNormal(VECTOR3 *out_Normal) const {
	VECTOR3 vEdge1(v1 - v0);
	VECTOR3 vEdge2(v2 - v0);
	VecCross(out_Normal, vEdge1, vEdge2);
}

/*------------------------------------------------------------
/|	Funktion:		GetNormal()
/|	Beschreibung:	Liefert das Normal des Dreiecks
/|	Parameter:		n/a
/|	Rückgabe:		Ausgabe: Normal
/|  2003-07-24 18:02 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 TRIANGLE3::GetNormal() const {
	VECTOR3 vEdge1(v1 - v0);
	VECTOR3 vEdge2(v2 - v0);
	return VecCross(vEdge1, vEdge2);
}