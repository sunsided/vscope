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

	Dateiname:		plane.inl.h
	Beschreibung:	Plane Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 07. Juli 2002 19:33

	Changelog:
	[1]		07. Juli 2002 19:33

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\enums-math.h"
#include "..\include-direct3d.h"
#include "..\fastmath\fastassort.h"
#include "plane.h"
#include "..\vektoren\vector3.h"
#include "..\vektoren\vector4.h"
#include "..\lines\lineseg.h"
#include "..\polygon\polygon.h"

#pragma intrinsic(memcpy)
#pragma intrinsic(memcmp)



VSINLINE PLANE::PLANE( const VECTOR3& a, const VECTOR3& b, const VECTOR3& c) {
	VECTOR3 n((b-a) CROSS (c-a));
	n.Normalize();
	this->a = n.x;
	this->b = n.y;
	this->c = n.z;
	this->d = -(n DOT a);
}


VSINLINE PLANE::PLANE( const VECTOR3& norm, const VECTOR3& loc) {
	///*
	a = norm.x;
	b = norm.y;
	c = norm.z;
	//*/
	//memcpy(this, &norm, sizeof(float)*3);
	d = -(norm DOT loc);
}

VSINLINE PLANE::PLANE( const VECTOR4& vec) {
	memcpy(this, &vec, sizeof(float)*4);
}

#ifdef POLYGON3_DEFINED
VSINLINE PLANE::PLANE( const POLYGON3& poly ) {
	VECTOR3 a = poly.pList[0];
	VECTOR3 b = poly.pList[1];
	VECTOR3 c = poly.pList[2];
	VECTOR3 n((b-a) CROSS (c-a));

	n.Normalize();
	this->a = n.x;
	this->b = n.y;
	this->c = n.z;
	this->d = -(n DOT a);
}
#endif

VSINLINE PLANE::PLANE( const VECTOR3& N, float D) {
	///*
	a = N.x;
	b = N.y;
	c = N.z;
	//*/
	//memcpy(this, &N, sizeof(float)*3);
	d = D;
}


VSINLINE PLANE::PLANE( CONST float* pf ) {
	///*
	a = pf[0];
	b = pf[1];
	c = pf[2];
	d = pf[3];
	//*/
	//memcpy(this, pf, sizeof(float)*4);
}

VSINLINE PLANE::PLANE( float fa, float fb, float fc, float fd ) {
	a = fa;
	b = fb;
	c = fc;
	d = fd;
}

VSINLINE void PLANE::Assign( const VECTOR3& N, float D) {
	///*
	a = N.x;
	b = N.y;
	c = N.z;
	//*/
	//memcpy(this, &N, sizeof(float)*3);
	d = D;
}

VSINLINE void PLANE::Assign( const VECTOR3& a, const VECTOR3& b, const VECTOR3& c) {
	VECTOR3 n((b-a) CROSS (c-a));
	n.Normalize();
	this->a = n.x;
	this->b = n.y;
	this->c = n.z;
	this->d = -(n DOT a);
}

VSINLINE void PLANE::Assign( const VECTOR3& norm, const VECTOR3& loc) {
	///*
	a = norm.x;
	b = norm.y;
	c = norm.z;
	//*/
	//memcpy(this, &norm, sizeof(float)*3);
	d = -(norm DOT loc);
}

VSINLINE void PLANE::Assign( const VECTOR4& vec) {
	memcpy(this, &vec, sizeof(float)*4);
}

VSINLINE void PLANE::Assign( const D3DXPLANE& plane) {
	memcpy(this, &plane, sizeof(PLANE));
}

VSINLINE void PLANE::Assign( const POLYGON3& poly ) {
	VECTOR3 a = poly.pList[0];
	VECTOR3 b = poly.pList[1];
	VECTOR3 c = poly.pList[2];
	VECTOR3 n((b-a) CROSS (c-a));

	n.Normalize();
	this->a = n.x;
	this->b = n.y;
	this->c = n.z;
	this->d = -(n DOT a);
}

VSINLINE void PLANE::Assign( CONST float* pf ) {
	///*
	a = pf[0];
	b = pf[1];
	c = pf[2];
	d = pf[3];
	//*/
	//memcpy(this, pf, sizeof(float)*4);
}

VSINLINE void PLANE::Assign( float fa, float fb, float fc, float fd ) {
	a = fa;
	b = fb;
	c = fc;
	d = fd;
}



// we're inlineing this because we do it constantly
VSINLINE LOCATION PLANE::GetLocation( VECTOR3 const &point ) const {
	VECTOR3 n(a, b, c);
	float dp = (point DOT n) + d;

	if(dp > EPSILON) {
		return LOC_FRONT;
	}
	if(dp < -EPSILON ) {
		return LOC_BACK;
	}
	return LOC_COPLANAR; // it was between EP and -EP
}


VSINLINE const VECTOR3 PLANE::GetIntersection( const VECTOR3 &a, const VECTOR3 &b ) const {
	VECTOR3 n(this->a, this->b, this->c);
	float aDot = (a DOT n);
	float bDot = (b DOT n);
	float scale = ( -d - aDot ) / ( bDot - aDot );
	return a + (scale * (b - a));
}

#ifdef LINESEG_DEFINED
VSINLINE const VECTOR3 PLANE::GetIntersection( const LINESEG &line ) const {
	VECTOR3 n(this->a, this->b, this->c);
	float aDot = (line.v0 DOT n);
	float bDot = (line.v1 DOT n);
	float scale = ( -d - aDot ) / ( bDot - aDot );
	return line.v0 + (scale * (line.v1 - line.v0));
}
#endif

VSINLINE const VECTOR3 PLANE::BringToPlane( const VECTOR3& pt ) {
	VECTOR3 n(a, b, c);
	float distToPlane = (pt DOT n);
	return VECTOR3( pt - (d + distToPlane)*n );
}


void VSINLINE PLANE::Flip() {
	a = -a;
	b = -b;
	c = -c;
	d = -d;
}


//returns true if VECTOR3==VECTOR3
VSINLINE bool operator==(PLANE const &a, PLANE const &b) {
	if((a.a==b.a) && (a.b==b.b) && (a.c==b.c) && (a.d==b.d))
		return true;
	return false;
};

#ifdef POLYGON3_DEFINED
VSINLINE LOCATION PLANE::GetLocation( const POLYGON3 &poly ) const {
	return GetLocation( poly.pList, poly.nElem );
}
#endif


// **************************************************************************

// casting
VSINLINE PLANE::operator float* () {
	return (float *) &a;
}

VSINLINE PLANE::operator const float* () const {
	return (CONST float *) &a;
}

VSINLINE PLANE::operator VECTOR3 () {
	return VECTOR3(a, b, c);
}

VSINLINE PLANE::operator const VECTOR3 () const {
	return VECTOR3(a, b, c);
}

VSINLINE PLANE::operator VECTOR4 () {
	return VECTOR4(a, b, c, d);
}

VSINLINE PLANE::operator const VECTOR4 () const {
	return VECTOR4(a, b, c, d);
}

VSINLINE PLANE::operator D3DXPLANE () {
	return (D3DXPLANE)*this;
}

/*VSINLINE PLANE::operator const D3DXPLANE () const {
	return (D3DXPLANE)*this;
}*/

// unary operators
VSINLINE PLANE PLANE::operator + () const {
	return *this;
}

VSINLINE PLANE PLANE::operator - () const {
	return PLANE(-a, -b, -c, -d);
}


// binary operators
VSINLINE bool PLANE::operator == ( CONST PLANE& p ) const {
	return a == p.a && b == p.b && c == p.c && d == p.d;
}

VSINLINE bool PLANE::operator != ( CONST PLANE& p ) const {
	return a != p.a || b != p.b || c != p.c || d != p.d;
}

VSINLINE VECTOR3 PLANE::GetNormal() const {
	return VECTOR3(this->a, this->b, this->c);
}

VSINLINE float PLANE::GetDistance() const {
	return this->d;
}

VSINLINE const PLANE& PLANE::operator = ( CONST PLANE& Plane ) {
	memcpy(this, &Plane, sizeof(PLANE));
	return *this;
}