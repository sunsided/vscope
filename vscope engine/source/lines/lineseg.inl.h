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

	Dateiname:		lineseg.inl.h
	Beschreibung:	Liniensegment Inline-Funktionen
	Revision:		2
	Erstellt:		MMT, 08. Juli 2002 01:28

	Changelog:
	[2]		13. Juli 2003 15:14
			GetLength() hinzugefügt.
	[1]		08. Juli 2002 01:28

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "lineseg.h"
#include "..\vektoren\vector3.h"
#include "..\fastmath\fastsqrt.h"

#include "..\vektoren\vectormath.inl.h"



VSINLINE LINESEG::LINESEG( const VECTOR3 &a, const VECTOR3 &b )
	: v0(a), v1(b)
{
}

VSINLINE LINESEG::LINESEG() {
}

VSINLINE VECTOR3 LINESEG::operator [] ( int x ) {
	if(x==0)
		return v0;
	else
		return v1;
}


/*------------------------------------------------------------
/|	Funktion:		GetLenght()
/|	Beschreibung:	Berechnet die Länge des Liniensegmentes
/|	Parameter:		n/a
/|	Rückgabe:		Länge (float)
/|  2003-07-13 15:14 MMT
/+------------------------------------------------------------*/
VSINLINE float LINESEG::GetLenght() const {
	return fastsqrt((v1.x - v0.x) * (v1.y - v0.y) * (v1.z - v0.z));
}

/*------------------------------------------------------------
/|	Funktion:		GetLenghtSquared()
/|	Beschreibung:	Berechnet Länge² des Liniensegmentes
/|	Parameter:		n/a
/|	Rückgabe:		Länge² (float)
/|  2003-07-13 15:14 MMT
/+------------------------------------------------------------*/
VSINLINE float LINESEG::GetLenghtSquared() const {
	return ((v1.x - v0.x) * (v1.y - v0.y) * (v1.z - v0.z));
}

/*------------------------------------------------------------
/|	Funktion:		GetLenghtInv()
/|	Beschreibung:	Berechnet 1/Länge des Liniensegmentes
/|	Parameter:		n/a
/|	Rückgabe:		1/Länge (float)
/|  2003-07-13 15:14 MMT
/+------------------------------------------------------------*/
VSINLINE float LINESEG::GetLenghtInv() const {
	return fastisqrt((float)((v1.x - v0.x) * (v1.y - v0.y) * (v1.z - v0.z)));
}

/*------------------------------------------------------------
/|	Funktion:		GetDistanceLine()
/|	Beschreibung:	Entfernung des Punktes von der Linie
/|	Parameter:		in_Point (VECTOR3&)
/|	Rückgabe:		Distanz (float)
/|  2003-07-18 15:14 MMT
/+------------------------------------------------------------*/
VSINLINE float LINESEG::GetDistanceLine(VECTOR3& in_Point) const {
	VECTOR3 vDirection = v1 - v0;
	vDirection.Normalize();
	VECTOR3 vDelta = in_Point - v0;
	VECTOR3 vResult;
	VecCross(&vResult, vDelta, vDirection);
	float fProjection = VecMagnitude(vResult);
	return fProjection;
}

/*------------------------------------------------------------
/|	Funktion:		ProjectPoint()
/|	Beschreibung:	Projiziert einen Punkt auf die Strecke
/|	Parameter:		out_Projected (VECTOR3*), in_Point (VECTOR3&)
/|	Rückgabe:		out_Projected (in Parameterliste)
/|  2003-07-18 17:41 MMT
/+------------------------------------------------------------*/
VSINLINE void LINESEG::ProjectPoint(VECTOR3* out_Projected, VECTOR3& in_Point) const {
	VECTOR3 vDirection = v1 - v0;
	//vDirection.Normalize();

	VECTOR3 vDelta = in_Point - v0;
	float fProjection = VecDot(vDelta, vDirection);

	out_Projected->Assign(v0 + fProjection * vDirection);
	if(fProjection <= 0.f) { 
		out_Projected->Assign(&v0);
	} else if(fProjection >= 1.f) {
		out_Projected->Assign(&v1);
	}	
}

/*------------------------------------------------------------
/|	Funktion:		ProjectPointLine()
/|	Beschreibung:	Projiziert einen Punkt auf die Gerade
/|	Parameter:		out_Projected (VECTOR3*), in_Point (VECTOR3&)
/|	Rückgabe:		out_Projected (in Parameterliste)
/|  2003-07-18 17:41 MMT
/+------------------------------------------------------------*/
VSINLINE void LINESEG::ProjectPointLine(VECTOR3* out_Projected, VECTOR3& in_Point) const {
	VECTOR3 vDirection = v1 - v0;
	vDirection.Normalize();

	VECTOR3 vDelta = in_Point - v0;
	float fProjection = VecDot(vDelta, vDirection);
	out_Projected->Assign(v0 + fProjection * vDirection);
}