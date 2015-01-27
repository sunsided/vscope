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

	Dateiname:		aabbox.inl.h
	Beschreibung:	Axis Aligned Bounding Box Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 22:50

	Changelog:
	[1]		09. Juli 2002 22:50

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "aabbox.h"
#include "aabsphere.inl.h"
#include "..\plane\plane.h"
#include "..\lines\lineseg.h"
#include "..\plane\plane.inl.h"
#include "..\lines\lineseg.inl.h"
#include "..\vektoren\vector3.inl.h"

VSINLINE void AABBOX3::UpdateBounds( const VECTOR3 &in ) {
	if( in.x > max.x ) max.x = in.x;
	if( in.y > max.y ) max.y = in.y;
	if( in.z > max.z ) max.z = in.z;
	if( in.x < min.x ) min.x = in.x;
	if( in.y < min.y ) min.y = in.y;
	if( in.z < min.z ) min.z = in.z;
}

VSINLINE const PLANE AABBOX3::operator [] (int x) {
	return planeList[x];
}

VSINLINE void AABBOX3::Convert(AABSPHERE3 &out_BSphere) {
	/*out_BSphere.UpdateBounds(this->max);
	out_BSphere.UpdateBounds(this->min);*/
	VECTOR3 vCenter(max + min);
	vCenter *= 0.5f;
	out_BSphere.m_loc = vCenter;
	out_BSphere.m_radius = (max-vCenter).GetLength();
}