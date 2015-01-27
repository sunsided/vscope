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

	Dateiname:		viewcone.inl.h
	Beschreibung:	Viewcone Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 00:46

	Changelog:
	[1]		10. Juli 2002 00:46
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "viewcone.h"
#include "..\fastmath\fastsqrt.h"
#include "..\vektoren\vector3.h"
#include "..\plane\plane.h"
#include "..\matrix\matrix4.h"
#include "..\bounding\aabbox.h"
#include "..\enums-math.h"

#include "..\plane\plane.inl.h"
#include "..\matrix\matrix4.inl.h"
#include "..\vektoren\vector3.inl.h"

#include "..\matrix\matrix4.inl.h"

/*
 * Diese Funktionen sind alle inlines, da sie sehr häufig benötigt werden.
 *
 */

#define FRUSTRUMPLANE_LEFT	0
#define FRUSTRUMPLANE_RIGHT	1
#define FRUSTRUMPLANE_TOP	2
#define FRUSTRUMPLANE_BOTTOM 3
#define FRUSTRUMPLANE_FAR	4
#define FRUSTRUMPLANE_NEAR	5

VSINLINE LOCATION VIEWCONE::GetLocation(AABBOX3& AABBox) const {
	VECTOR3 bMax = AABBox.max;
	VECTOR3 bMin = AABBox.min;
	VECTOR3 NearPoint, FarPoint;
	BOOL      bClipped=FALSE;

	for (int i=0; i<6; i++) {
		// Initialisiere nahen Punkt unter der Annahme
		// dass alle Normalen Komponenten <= 0.0f sind
		NearPoint.x = bMax.x;
		NearPoint.y = bMax.y;
		NearPoint.z = bMax.z;

		FarPoint.x = bMin.x;
		FarPoint.y = bMin.y;
		FarPoint.z = bMin.z;

		// Überprüfe die Annahme...
		if (this->m_Planes[i].a > 0.0f) {
			NearPoint.x = bMin.x;
			FarPoint.x  = bMax.x;
		}

		if (this->m_Planes[i].b > 0.0f) {
			NearPoint.y = bMin.y;
			FarPoint.y   = bMax.y;
		}

		if (this->m_Planes[i].c > 0.0f) {
			NearPoint.z = bMin.z;
			FarPoint.z   = bMax.z;
		}

		// Checke ob der nahe Punkt ausserhalb liegt,
		// dann ist auch die ganze Box ausserhalb
		if ((this->m_Planes[i].GetNormal() DOT NearPoint) + this->m_Planes[i].d > 0)
			return LOC_OUTSIDE;

		// Checke ob der ferne Punkt ausserhalb liegt
		if ((this->m_Planes[i].GetNormal() DOT FarPoint) + this->m_Planes[i].d > 0)
			bClipped = TRUE;
	}

	// Sind wir bis hierher gekommen dann ist die Box nicht ganz
	// ausserhalb. Lag der FarPoint aber ausserhalb dann ist die
	// Box nur teilweise im View Frustrum
	if (bClipped)
		return LOC_SPLIT;

	// Sonst komplett innerhalb
	return LOC_INSIDE;

}

VSINLINE LOCATION VIEWCONE::GetLocation(VECTOR3& Point) const {
	return this->GetLocation(AABBOX3(Point, Point));
}