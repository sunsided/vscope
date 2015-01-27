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

	Dateiname:		aabsphere.inl.h
	Beschreibung:	Axis Aligned Bounding Sphere Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 22:50

	Changelog:
	[1]		09. Juli 2002 22:50

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "aabsphere.h"

VSINLINE AABSPHERE3::AABSPHERE3() {
}

VSINLINE AABSPHERE3::AABSPHERE3( float radius, VECTOR3 loc ) :
	m_radius( radius ), m_loc( loc )
{
}

VSINLINE AABSPHERE3::AABSPHERE3( VECTOR3 loc, int nVerts, VECTOR3* pList ) {
	m_loc = loc;
	m_radius = 0.f;
	float currRad;
	for( int i=0; i< nVerts; i++ ) {
		currRad = pList[i].GetMag();
		if( currRad > m_radius ) {
			m_radius = currRad;
		}
	}
}

VSINLINE bool AABSPHERE3::Intersect( AABSPHERE3& a, AABSPHERE3& b ) {
	// avoid a square root by squaring both sides of the equation
	float magSqrd = a.m_radius * a.m_radius + b.m_radius * b.m_radius;
	if( (b.m_loc - a.m_loc).GetMagSquared() > magSqrd ) {
		return false;
	}
	return true;
}

VSINLINE  AABSPHERE3& AABSPHERE3::operator += ( const VECTOR3& in ) {
	m_loc += in;
	return *this;
}


VSINLINE  AABSPHERE3& AABSPHERE3::operator -= ( const VECTOR3& in ) {
	m_loc -= in;
	return *this;
}


VSINLINE  const AABSPHERE3 operator+(AABSPHERE3 const &a, VECTOR3 const &b) {
	return AABSPHERE3( a.m_radius, b+a.m_loc ); 
}


VSINLINE  const AABSPHERE3 operator-(AABSPHERE3 const &a, VECTOR3 const &b) {
	return AABSPHERE3( a.m_radius, b-a.m_loc ); 
}


VSINLINE void AABSPHERE3::UpdateBounds( const VECTOR3 &in ) {
	VECTOR3 vPoint(in - this->m_loc);
	float fLength = vPoint.GetLength();
	if(fLength > this->m_radius) this->m_radius = fLength;
}