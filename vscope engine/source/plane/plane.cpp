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

	Dateiname:		plane.cpp
	Beschreibung:	Plane Kontainer
	Revision:		2
	Erstellt:		MMT, 07. Juli 2002 19:33

	Changelog:
	[2]		10. Juli 2002 23:06
			Fehlende Funktionen hinzugefügt
	[1]		07. Juli 2002 19:33

===========================================================================*/

#include <assert.h>

#include "plane.h"
#include "plane.inl.h"
#include "..\enums-math.h"
#include "..\vektoren\vector3.h"
#include "..\lines\lineseg.h"
#include "..\bounding\aabsphere.h"
#include "..\polygon\polygon.h"

#include "..\vektoren\vector3.inl.h"
#include "..\lines\lineseg.inl.h"
#include "..\bounding\aabsphere.inl.h"

LOCATION PLANE::GetLocation( VECTOR3 *list, int num ) const {
	bool allfront=true, allback=true;
	LOCATION res;

	for( int i=0; i<num; i++ ) {
		res = GetLocation( list[i] );

		if( res == LOC_BACK ) {
			allfront = false;
		} else if( res == LOC_FRONT ) {
			allback = false;
		}
	}
	if( allfront && !allback ) {
		// All the points were either in front or coplanar
		return LOC_FRONT;
	} else if( !allfront && allback ) {
		// All the points were either in back or coplanar
		return LOC_BACK;
	} else if( !allfront && !allback ) {
		// Some were in front, some were in back
		return LOC_SPLIT;
	}
	// All were coplanar
	return LOC_COPLANAR;
}


LOCATION PLANE::GetLocation( const AABSPHERE3& sphere ) const {
	VECTOR3 n(a, b, c);
	float dp = (sphere.m_loc DOT n) + d;

	if((dp - sphere.m_radius) > EPSILON) {
		// Sphere was completely in front
		return LOC_FRONT;
	} if((dp + sphere.m_radius) < -EPSILON ) {
		// Sphere was completely in back
		return LOC_BACK;
	}
	// Sphere was partially in each
	return LOC_COPLANAR; 
}


bool PLANE::Clip( const POLYGON3 &in, POLYGON3 *out ) const {
	assert( out ); // Make sure our pointer to the out vs_polygon is valid
	//assert( in.nElem > 2 ); // Make sure we're not passed a degenerate vs_polygon
	if(in.nElem > 2) assert( in.nElem > 2 );

	unsigned int thisInd=in.nElem-1;
	unsigned int nextInd=0;

	LOCATION thisRes = GetLocation( in.pList[thisInd] );
	LOCATION nextRes;

	out->nElem = 0;

	for( nextInd=0; nextInd<in.nElem; nextInd++ ) {

		nextRes = GetLocation( in.pList[nextInd] );

		if( thisRes == LOC_FRONT || thisRes == LOC_COPLANAR ) {
			// Add the point
			out->pList[out->nElem++] = in.pList[thisInd];
		}

		if( ( thisRes == LOC_BACK && nextRes == LOC_FRONT ) ||
			( thisRes == LOC_FRONT && nextRes == LOC_BACK ) ) {
			// Add the split point
			out->pList[out->nElem++] = GetIntersection( in.pList[thisInd], in.pList[nextInd] );
		}

		thisInd = nextInd;
		thisRes = nextRes;
	}
	if( out->nElem >= 3 ) {
		return true;
	}
	return false;
}


bool PLANE::Split( POLYGON3 const &in, POLYGON3 *pFront, POLYGON3 *pBack ) const {
	assert( pFront ); // Make sure our pointer to the out vs_polygon is valid
	assert( pBack ); // Make sure our pointer to the out vs_polygon is valid
	//assert( in.nElem > 2 ); // Make sure we're not passed a degenerate vs_polygon
	if(in.nElem > 2) assert( in.nElem > 2 );

	// Start with curr as the last vertex and next as 0. 
	pFront->nElem = 0;
	pBack->nElem = 0;

	unsigned int thisInd=in.nElem-1;
	unsigned int nextInd=0;

	LOCATION thisRes = GetLocation( in.pList[thisInd] );
	LOCATION nextRes;

	for( nextInd=0; nextInd<in.nElem; nextInd++) {
		nextRes = GetLocation( in.pList[nextInd] );
		if( thisRes == LOC_FRONT ) {
			// Add the point to the front
			pFront->pList[pFront->nElem++] = in.pList[thisInd];
		}

		if( thisRes == LOC_BACK ) {
			// Add the point to the back
			pBack->pList[pBack->nElem++] = in.pList[thisInd];
		}

		if( thisRes == LOC_COPLANAR ) { 
			// Add the point to both
			pFront->pList[pFront->nElem++] = in.pList[thisInd];
			pBack->pList[pBack->nElem++] = in.pList[thisInd];
		}

		if( ( thisRes == LOC_BACK && nextRes == LOC_FRONT ) ||
			( thisRes == LOC_FRONT && nextRes == LOC_BACK ) ) { 
			// Add the split point to both
			VECTOR3 split = GetIntersection( in.pList[thisInd], in.pList[nextInd] );
			pFront->pList[pFront->nElem++] = split;
			pBack->pList[pBack->nElem++] = split;
		}

		thisInd = nextInd;
		thisRes = nextRes;
	}
	if( pFront->nElem >= 3 && pBack->nElem >= 3 ) { 
		// Nothing ended up degenerate
		return true;
	}
	return false;
}


// Behavior is undefined if seg can't actually be split
bool PLANE::Split( const LINESEG &in, LINESEG *front, LINESEG *back ) const {
	VECTOR3 temp = GetIntersection( in.v0, in.v1 );

	if( GetLocation( in.v0 ) == LOC_FRONT ) {
		front->v0 = in.v0;
		front->v1 = temp;
		back->v0 = temp;
		back->v1 = in.v1;
		return true;
	} else {
		front->v0 = temp;
		front->v1 = in.v1;
		back->v0 = in.v0;
		back->v1 = temp;
		return true;
	}
	return false;
}