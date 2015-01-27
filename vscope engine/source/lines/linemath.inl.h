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

	Dateiname:		linemath.inl.h
	Beschreibung:	Linien-Mathematik
	Revision:		1
	Erstellt:		MMT, 18. Juli 2003 17:11

	Changelog:
	[1]		18. Juli 2003 17:11

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\vektoren\vector3.h"
#include "..\debug\debugassert.h"
#include "..\vektoren\vectormath.inl.h"



/*------------------------------------------------------------
/|	Funktion:		GetDistancePointLine()
/|	Beschreibung:	Entfernung des Punktes von der Linie (2 Punkte)
/|	Parameter:		in_Point (VECTOR3&), 2 Punkte (VECTOR3&)
/|	Rückgabe:		Distanz (float)
/|  2003-07-18 17:09 MMT
/+------------------------------------------------------------*/
VSINLINE float GetDistancePointLine(const VECTOR3& in_Point, const VECTOR3& in_LineOrigin, VECTOR3& in_LinePoint2) {
	VECTOR3 vResult;
	VECTOR3 vDirection	= in_LinePoint2 - in_LineOrigin;
			vDirection.Normalize();
	VECTOR3 vDelta		= in_Point - in_LineOrigin;
	VecCross(&vResult, vDelta, vDirection);
	return VecMagnitude(vResult);
}

/*------------------------------------------------------------
/|	Funktion:		GetDistancePointLineByDir()
/|	Beschreibung:	Entfernung des Punktes von der Linie (1 Punkt, 1 Richtung)
/|	Parameter:		in_Point (VECTOR3&), Ursprung der Linie (VECTOR3&), Richtungsvektor (VECTOR3&)
/|	Rückgabe:		Distanz (float)
/|  2003-07-18 17:11 MMT
/+------------------------------------------------------------*/
VSINLINE float GetDistancePointLineByDir(const VECTOR3& in_Point, const VECTOR3& in_LineOrigin, VECTOR3& in_LineDirection) {
	VSBREAKIF( in_LineDirection.GetNormalized() != in_LineDirection );
	VECTOR3 vDelta		= in_Point - in_LineOrigin;
	VECTOR3 vResult;
	VecCross(&vResult, vDelta, in_LineDirection);
	return VecMagnitude(vResult);
}