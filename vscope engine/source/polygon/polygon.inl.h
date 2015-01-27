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

	Dateiname:		polygon.inl.h
	Beschreibung:	Polygon (Template) Inlines
	Revision:		1
	Erstellt:		MMT, 10. Juli 2003 20:03

	Changelog:
	[1]		10. Juli 2003 20:03

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "polygon.h"
#include "..\debug\debugassert.h"
#include "..\vektoren\vector3.inl.h"
#include "..\plane\plane.inl.h"
#include "..\triangle\triangle3.inl.h"
#include "..\bounding\aabbox.inl.h"


VSINLINE POLYGON3::POLYGON3() : 
	nElem(0), maxElem(0), pList(0x0)
{
	vCenter.Assign(0.f, 0.f, 0.f);
};

VSINLINE POLYGON3::POLYGON3( int maxSize ) {
	maxElem = maxSize;
	//pList = new type[maxSize];
	pList = new VECTOR3[maxSize];
}

VSINLINE POLYGON3::POLYGON3( const POLYGON3 &in ) {
	CloneData( in );
}


VSINLINE POLYGON3::~POLYGON3() {
	DestroyData();
}


VSINLINE POLYGON3& POLYGON3::operator=( const POLYGON3 &in ) {
	if( &in != this ) {
		DestroyData();
		CloneData( in );
	}
	return *this;
}


VSINLINE void POLYGON3::CloneData( const POLYGON3 &in ) {
	VSBREAKIF(!in.pList);
#ifdef _DEBUG
	if( !in.pList ) 
		return;
#endif

	//pList = new type[in.maxElem];
	DestroyData();
	pList = new VECTOR3[in.maxElem];
	maxElem = in.maxElem;
	nElem = in.nElem;
	
	signed int i = in.nElem-1;
	do {
		pList[i] = in.pList[i];
	} while( --i>=0 );
}


VSINLINE void POLYGON3::DestroyData( )	{
	delete[] pList;
	pList = NULL;
}




VSINLINE bool POLYGON3::Clip( const PLANE &in_Plane, POLYGON3 *out ) const {
	VSBREAKIFNOT( out!=NULL ); // Make sure our pointer to the out vs_polygon is valid
	//assert( in.nElem > 2 ); // Make sure we're not passed a degenerate vs_polygon
	VSBREAKIFNOT( this->nElem > 2 );

	unsigned int thisInd=this->nElem-1;
	unsigned int nextInd=0;

	LOCATION thisRes = in_Plane.GetLocation( this->pList[thisInd] );
	LOCATION nextRes;

	out->nElem = 0;

	for( nextInd=0; nextInd<this->nElem; nextInd++ ) {

		nextRes = in_Plane.GetLocation( this->pList[nextInd] );

		if( thisRes == LOC_FRONT || thisRes == LOC_COPLANAR ) {
			// Add the point
			out->pList[out->nElem++] = this->pList[thisInd];
		}

		if( ( thisRes == LOC_BACK && nextRes == LOC_FRONT ) ||
			( thisRes == LOC_FRONT && nextRes == LOC_BACK ) ) {
			// Add the split point
			out->pList[out->nElem++] = in_Plane.GetIntersection( this->pList[thisInd], this->pList[nextInd] );
		}

		thisInd = nextInd;
		thisRes = nextRes;
	}
	if( out->nElem >= 3 ) {
		return true;
	}
	return false;
}


VSINLINE __declspec(deprecated) float POLYGON3::GetArea() const {
	//HACK: POLYGON:GetArea sollte dreidimensional werden!
	unsigned long	n = this->m_iElementCount;
	float			A = 0.0f;
	unsigned long	p = n-1;
	unsigned long	q = 0;
	do {
		A+= pList[p].x*pList[q].y;
		A-= pList[q].x*pList[p].y;
		p = q++;
	} while(q<n);
	return A*0.5f;
}



// Achtung! Triangulate erwartet ein allokiertes, ausreichend großes Array!
VSINLINE void POLYGON3::Triangulate(TRIANGLE3 *out_TriangleList) const {
	// Mapping auf MMT-Implementierung
#ifdef TRIANGULATE_MMTFAN
	TriangulateMMTFan(out_TriangleList); return;
#endif
	TriangulateMMTFan(out_TriangleList);
}

VSINLINE unsigned int POLYGON3::TriangulationCost() const {
#ifdef TRIANGULATE_MMTFAN
	return TriangulationCostMMTFan();
#endif
	return TriangulationCostMMTFan();
}

VSINLINE void POLYGON3::TriangulateMMTFan(TRIANGLE3 *out_TriangleList) const{
	signed long iCount = m_iElementCount-1;
	unsigned long iStep = 0;
	do {
		out_TriangleList[iStep].v0 = pList[0];
		out_TriangleList[iStep].v1 = pList[m_iElementCount-iStep-2];
		out_TriangleList[iStep].v2 = pList[m_iElementCount-iStep-1];
		++iStep;
	} while(--iCount > 1);
}

VSINLINE unsigned int POLYGON3::TriangulationCostMMTFan() const{
	return m_iElementCount - 2;
}


/*------------------------------------------------------------
/|	Funktion:		GetCenter()
/|	Beschreibung:	Liefert das vorberechnete Zentrum des Polygons
/|	Parameter:		VECTOR3
/|	Rückgabe:		n/a
/|  2003-07-24 18:50 MMT
/+------------------------------------------------------------*/
VSINLINE void POLYGON3::GetCenter(VECTOR3 *out_vCenter) const {
	out_vCenter->Assign(vCenter);
}


/*------------------------------------------------------------
/|	Funktion:		GetCenter()
/|	Beschreibung:	Liefert das vorberechnete Zentrum des Polygons
/|	Parameter:		n/a
/|	Rückgabe:		VECTOR3
/|  2003-07-24 18:50 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 POLYGON3::GetCenter() const {
	return vCenter;
}

/*------------------------------------------------------------
/|	Funktion:		GetCenterFresh()
/|	Beschreibung:	Liefert das Zentrum des Polygons, berechnet es neu
/|	Parameter:		VECTOR3
/|	Rückgabe:		n/a
/|  2003-07-24 18:46 MMT
/+------------------------------------------------------------*/
VSINLINE void POLYGON3::GetCenterFresh(VECTOR3 *out_vCenter) {
	out_vCenter->Assign(0.f, 0.f, 0.f);
	signed long int iCount = (signed long int)m_iElementCount - 1;
	do {
		out_vCenter->Add(pList[iCount]);
	} while(--iCount >= 0);
	//out_vCenter->Scale(0.5f);
	out_vCenter->Scale(1.f/m_iElementCount);
	// Werte speichern
	vCenter.x = out_vCenter->x;
	vCenter.y = out_vCenter->y;
	vCenter.z = out_vCenter->z;
}


/*------------------------------------------------------------
/|	Funktion:		GetCenterFresh()
/|	Beschreibung:	Liefert das Zentrum des Polygons, berechnet es neu
/|	Parameter:		n/a
/|	Rückgabe:		VECTOR3
/|  2003-07-24 18:46 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 POLYGON3::GetCenterFresh() {
	CalculateCenter();
	return vCenter;
}

/*------------------------------------------------------------
/|	Funktion:		CalculateCenter()
/|	Beschreibung:	Berechnet das Zentrum des Polygons und speichert den Wert
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-07-24 18:46 MMT
/+------------------------------------------------------------*/
VSINLINE void POLYGON3::CalculateCenter() {
	GetCenter(&vCenter);
}

/*------------------------------------------------------------
/|	Funktion:		GetAABBCalcCenter()
/|	Beschreibung:	Liefert die AABB des Polygons und berechnet das Zentrum des Polygons neu!
/|	Parameter:		out_AABB
/|	Rückgabe:		n/a
/|  2003-07-24 18:46 MMT
/+------------------------------------------------------------*/
VSINLINE void POLYGON3::GetAABBCalcCenter(AABBOX3 *out_AABB) {
	CalculateCenter();
	GetAABB(out_AABB);
}

/*------------------------------------------------------------
/|	Funktion:		GetAABB()
/|	Beschreibung:	Liefert die AABB des Polygons - Berechnet das Zentrum des Polygons nicht neu!
/|	Parameter:		out_AABB
/|	Rückgabe:		n/a
/|  2003-07-24 18:46 MMT
/+------------------------------------------------------------*/
VSINLINE void POLYGON3::GetAABB(AABBOX3 *out_AABB) {
	out_AABB->Create(this->vCenter, this->vCenter);
	signed long int iCount = (signed long int)m_iElementCount - 1;
	do {
		out_AABB->UpdateBounds(pList[iCount]);
	} while(--iCount >= 0);
}