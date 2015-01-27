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

	Dateiname:		primitives_ring.inl.h
	Beschreibung:	Primitive: Ring Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 29. Mai 2003 13:03

	Changelog:
	[1]		29. Mai 2003 13:03
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "primitives_ring.h"
#include "..\vektoren\vector2.h"
#include "..\vektoren\vector3.h"
#include "..\vertices\vertices.h"
#include "..\bounding\aabbox.h"

#include "..\vertices\vertices.inl.h"
#include "..\vektoren\vector2.inl.h"
#include "..\vektoren\vector3.inl.h"
#include "..\bounding\aabbox.inl.h"
#include "..\common\common.h"

#pragma intrinsic(memset, memcpy)

VSINLINE PRIMITIVE_RING::PRIMITIVE_RING() {
	this->m_RingVertices = NULL;
	this->m_RingVB = NULL;
	this->m_pd3dDevice = NULL;
}

VSINLINE PRIMITIVE_RING::~PRIMITIVE_RING() {
	this->Release();
}

VSINLINE void PRIMITIVE_RING::Release() {
	SAFE_DELETE_ARRAY(this->m_RingVertices);
	SAFE_RELEASE(m_RingVB);
}

VSINLINE AABBOX3 PRIMITIVE_RING::GetAABB() {
	return AABBOX3(-this->m_fRadius,-this->m_fRadius,0.f,this->m_fRadius,this->m_fRadius,0.f);
}