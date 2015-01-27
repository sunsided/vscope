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

	Dateiname:		aabbox.cpp
	Beschreibung:	Axis Aligned Bounding Box
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 22:50

	Changelog:
	[1]		09. Juli 2002 22:50

===========================================================================*/

#include "aabbox.h"
#include "aabbox.inl.h"

#include "..\fastmath\fastassort.h"
#include "..\enums-math.h"
#include "..\plane\plane.h"
#include "..\lines\lineseg.h"
#include "..\vektoren\vector3.h"

AABBOX3::AABBOX3() {
	max = VECTOR3( 50000, 50000, 50000 );
	min = VECTOR3( -50000, -50000, -50000 );

	// top, bottom, back, front, right, left
	planeList[0] = PLANE( VECTOR3( 0.f, 1.f, 0.f ), max );
	planeList[1] = PLANE( VECTOR3( 0.f,-1.f, 0.f ), min );
	planeList[2] = PLANE( VECTOR3( 0.f, 0.f, 1.f ), max );
	planeList[3] = PLANE( VECTOR3( 0.f, 0.f,-1.f ), min );
	planeList[4] = PLANE( VECTOR3( 1.f, 0.f, 0.f ), max );
	planeList[5] = PLANE( VECTOR3(-1.f, 0.f, 0.f ), min );
}

AABBOX3::AABBOX3( VECTOR3 &p_min, VECTOR3 &p_max ) {
	// top, bottom, back, front, right, left
	max = p_max;
	min = p_min;
	planeList[0] = PLANE( VECTOR3( 0.f, 1.f, 0.f ), p_max );
	planeList[1] = PLANE( VECTOR3( 0.f,-1.f, 0.f ), p_min );
	planeList[2] = PLANE( VECTOR3( 0.f, 0.f, 1.f ), p_max );
	planeList[3] = PLANE( VECTOR3( 0.f, 0.f,-1.f ), p_min );
	planeList[4] = PLANE( VECTOR3( 1.f, 0.f, 0.f ), p_max );
	planeList[5] = PLANE( VECTOR3(-1.f, 0.f, 0.f ), p_min );
}

AABBOX3::AABBOX3( VECTOR3 &center, float Seitenlaenge ) {
	float hs = Seitenlaenge * 0.5f;
	min.x = center.x - hs;
	min.y = center.y - hs;
	min.z = center.z - hs;
	max.x = center.x + hs;
	max.y = center.y + hs;
	max.z = center.z + hs;
	planeList[0] = PLANE( VECTOR3( 0.f, 1.f, 0.f ), max );
	planeList[1] = PLANE( VECTOR3( 0.f,-1.f, 0.f ), min );
	planeList[2] = PLANE( VECTOR3( 0.f, 0.f, 1.f ), max );
	planeList[3] = PLANE( VECTOR3( 0.f, 0.f,-1.f ), min );
	planeList[4] = PLANE( VECTOR3( 1.f, 0.f, 0.f ), max );
	planeList[5] = PLANE( VECTOR3(-1.f, 0.f, 0.f ), min );
}

AABBOX3::AABBOX3( float x_min, float y_min, float z_min, float x_max, float y_max, float z_max ) {
	min.x = x_min;
	min.y = y_min;
	min.z = z_min;
	max.x = x_max;
	max.y = y_max;
	max.z = z_max;
	planeList[0] = PLANE( VECTOR3( 0.f, 1.f, 0.f ), max );
	planeList[1] = PLANE( VECTOR3( 0.f,-1.f, 0.f ), min );
	planeList[2] = PLANE( VECTOR3( 0.f, 0.f, 1.f ), max );
	planeList[3] = PLANE( VECTOR3( 0.f, 0.f,-1.f ), min );
	planeList[4] = PLANE( VECTOR3( 1.f, 0.f, 0.f ), max );
	planeList[5] = PLANE( VECTOR3(-1.f, 0.f, 0.f ), min );
}


void AABBOX3::Create( VECTOR3 &p_min, VECTOR3 &p_max ) {
	// top, bottom, back, front, right, left
	max = p_max;
	min = p_min;
	planeList[0] = PLANE( VECTOR3( 0.f, 1.f, 0.f ), p_max );
	planeList[1] = PLANE( VECTOR3( 0.f,-1.f, 0.f ), p_min );
	planeList[2] = PLANE( VECTOR3( 0.f, 0.f, 1.f ), p_max );
	planeList[3] = PLANE( VECTOR3( 0.f, 0.f,-1.f ), p_min );
	planeList[4] = PLANE( VECTOR3( 1.f, 0.f, 0.f ), p_max );
	planeList[5] = PLANE( VECTOR3(-1.f, 0.f, 0.f ), p_min );
}

void AABBOX3::Create( VECTOR3 &center, float Seitenlaenge ) {
	float hs = Seitenlaenge * 0.5f;
	min.x = center.x - hs;
	min.y = center.y - hs;
	min.z = center.z - hs;
	max.x = center.x + hs;
	max.y = center.y + hs;
	max.z = center.z + hs;
	planeList[0] = PLANE( VECTOR3( 0.f, 1.f, 0.f ), max );
	planeList[1] = PLANE( VECTOR3( 0.f,-1.f, 0.f ), min );
	planeList[2] = PLANE( VECTOR3( 0.f, 0.f, 1.f ), max );
	planeList[3] = PLANE( VECTOR3( 0.f, 0.f,-1.f ), min );
	planeList[4] = PLANE( VECTOR3( 1.f, 0.f, 0.f ), max );
	planeList[5] = PLANE( VECTOR3(-1.f, 0.f, 0.f ), min );
}

void AABBOX3::Create( float x_min, float y_min, float z_min, float x_max, float y_max, float z_max ) {
	min.x = x_min;
	min.y = y_min;
	min.z = z_min;
	max.x = x_max;
	max.y = y_max;
	max.z = z_max;
	planeList[0] = PLANE( VECTOR3( 0.f, 1.f, 0.f ), max );
	planeList[1] = PLANE( VECTOR3( 0.f,-1.f, 0.f ), min );
	planeList[2] = PLANE( VECTOR3( 0.f, 0.f, 1.f ), max );
	planeList[3] = PLANE( VECTOR3( 0.f, 0.f,-1.f ), min );
	planeList[4] = PLANE( VECTOR3( 1.f, 0.f, 0.f ), max );
	planeList[5] = PLANE( VECTOR3(-1.f, 0.f, 0.f ), min );
}

bool AABBOX3::Clip( LINESEG *inLine, VECTOR3 *hitLoc ) {
	LINESEG front, back, line = *inLine;
	LOCATION loc;
	for( int i=0; i<6; i++ ) {
		loc = planeList[i].GetLocation( &line.v0, 2 );
		switch( loc ) {
			case LOC_FRONT:
				// fail.
				return false;
				break;

			case LOC_BACK:
				// continue on.  basically do nothing.
				break;

			case LOC_SPLIT:
				// split and keep the back part
				planeList[i].Split( line, &front, &back );
				line = back;
				break;

			case LOC_COPLANAR:
				// fail.
				return false;
				break;
		}
	}
	*hitLoc = line.v0;
	return true;
}


bool AABBOX3::Clip( LINESEG *inLine, LINESEG *clippedLine ) {
	LINESEG front, back, line = *inLine;
	LOCATION loc;
	for( int i=0; i<6; i++ ) {
		loc = planeList[i].GetLocation( &line.v0, 2 );
		switch( loc ) {
			case LOC_FRONT:
				// fail.
				return false;
				break;

			case LOC_BACK:
				// continue on.  basically do nothing.
				break;

			case LOC_SPLIT:
				// split and keep the back part
				planeList[i].Split( line, &front, &back );
				line = back;
				break;

			case LOC_COPLANAR:
				// fail.
				return false;
				break;
		}
	}
	*clippedLine = line;
	return true;
}


void AABBOX3::ReCalcPlanes() {
	planeList[0].d = planeList[0].a * max.x + planeList[0].b * max.y + planeList[0].c * max.z;
	planeList[1].d = planeList[1].a * min.x + planeList[1].b * min.y + planeList[1].c * min.z;
	planeList[2].d = planeList[2].a * max.x + planeList[2].b * max.y + planeList[2].c * max.z;
	planeList[3].d = planeList[3].a * min.x + planeList[3].b * min.y + planeList[3].c * min.z;
	planeList[4].d = planeList[4].a * max.x + planeList[4].b * max.y + planeList[4].c * max.z;
	planeList[5].d = planeList[5].a * min.x + planeList[5].b * min.y + planeList[5].c * min.z;
}

const AABBOX3 AABBOX3::operator + ( const AABBOX3 &box ) {
	VECTOR3 mmax, mmin;
	mmax.x = MAX(box.max.x, max.x);
	mmax.y = MAX(box.max.y, max.y);
	mmax.z = MAX(box.max.z, max.z);
	mmin.x = MIN(box.min.x, min.x);
	mmin.y = MIN(box.min.y, min.y);
	mmin.z = MIN(box.min.z, min.z);
	return AABBOX3(mmin, mmax);
}

const void AABBOX3::operator += ( const AABBOX3 &box ) {
	max.x = MAX(box.max.x, max.x);
	max.y = MAX(box.max.y, max.y);
	max.z = MAX(box.max.z, max.z);
	min.x = MIN(box.min.x, min.x);
	min.y = MIN(box.min.y, min.y);
	min.z = MIN(box.min.z, min.z);
	ReCalcPlanes();
}