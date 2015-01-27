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

	Dateiname:		vertices.h
	Beschreibung:	Vertextypen Inline-Funktionen
	Revision:		3
	Erstellt:		MMT, 10. Juli 2002 00:33

	Changelog:
	[3]		10. Juli 2002 22:35
			VSD3DVERTEX
	[2]		10. Juli 2002 18:28
			VSVERTEX_XYZ_TEX1
	[1]		10. Juli 2002 00:33
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "vertices.h"
#include "..\color\color4.inl.h"

namespace VERTICES {

VSINLINE VSD3DTLVERTEX::VSD3DTLVERTEX() { 
}

VSINLINE VSD3DTLVERTEX::VSD3DTLVERTEX(const D3DVECTOR& v, float _rhw, D3DCOLOR _color, float _tu, float _tv) { 
	x = v.x; y = v.y; z = v.z; 
	rhw = _rhw;
	color = _color; 
	tu = _tu; tv = _tv;
}

VSINLINE VSD3DLVERTEX::VSD3DLVERTEX() { 
}

VSINLINE VSD3DLVERTEX::VSD3DLVERTEX(const D3DVECTOR& v, D3DCOLOR _color, float _tu, float _tv) { 
	x = v.x; y = v.y; z = v.z; 
	color = _color; 
	tu = _tu; tv = _tv;
}


VSINLINE VSVERTEX_XYZ_TEX1::VSVERTEX_XYZ_TEX1() { 
}

VSINLINE VSVERTEX_XYZ_TEX1::VSVERTEX_XYZ_TEX1(const D3DVECTOR& v, float _tu, float _tv) { 
	x = v.x; y = v.y; z = v.z; 
	tu = _tu; tv = _tv;
}

VSINLINE VSVERTEX_XYZ_TEX1::VSVERTEX_XYZ_TEX1(const float _x, const float _y, const float _z, float _tu, float _tv) {
	x = _x; y = _y; z = _z; 
	tu = _tu; tv = _tv;
}

VSINLINE VSD3DVERTEX::VSD3DVERTEX() { 
}

VSINLINE VSD3DVERTEX::VSD3DVERTEX(const VECTOR3& v, VECTOR3 &_vN, float _tu, float _tv) { 
	x = v.x; y = v.y; z = v.z; 
	vN = _vN;
	tu = _tu; tv = _tv;
}

VSINLINE void VSD3DVERTEX::Assign(const VECTOR3& v, VECTOR3 &_vN, float _tu, float _tv) {
	x = v.x; y = v.y; z = v.z; 
	vN = _vN;
	tu = _tu; tv = _tv;
}

VSINLINE void VSD3DVERTEX_DIFFUSE::Assign(const VECTOR3& v, VECTOR3 &_vN, D3DCOLOR &color, float _tu, float _tv) {
	x = v.x; y = v.y; z = v.z; 
	vN = _vN;
	tu = _tu; tv = _tv;
	diffuse = color;
}

VSINLINE void VSD3DVERTEX_DIFFUSE::Assign(const VECTOR3& v, VECTOR3 &_vN, COLOR4 &color, float _tu, float _tv) {
	x = v.x; y = v.y; z = v.z; 
	vN = _vN;
	tu = _tu; tv = _tv;
	diffuse = color.MakeDWord();
}

VSINLINE VSVERTEX_XYZ_TEX1::VSVERTEX_XYZ_TEX1(const VECTOR3& v, const VECTOR3& _vN, float _tu, float _tv) {
	x = v.x; y = v.y; z = v.z; 
	vN = _vN;
	tu = _tu; tv = _tv;
}

VSINLINE VSVERTEX_XYZ_TEX1::VSVERTEX_XYZ_TEX1(const VECTOR3 v, const VECTOR3 _vN, float _tu, float _tv) {
	x = v.x; y = v.y; z = v.z; 
	vN = _vN;
	tu = _tu; tv = _tv;
}


} // namespace
using namespace VERTICES;