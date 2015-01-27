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
	Beschreibung:	Vertextypen
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

#ifndef VERTICES_DEFINED
#define VERTICES_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vektoren\vector3.inl.h"
#include "..\color\color4.h"

namespace VERTICES {

/*---------------------------------------------------------------------------
	Strukturen für VSD3DTLVERTEX
---------------------------------------------------------------------------*/
struct VSD3DTLVERTEX {// Vertex Struktur (transformiert, beleuchtet)
public:
				float x, y, z;
				float rhw;
				D3DCOLOR color;
				float tu, tv;

public:
				VSD3DTLVERTEX();
			    VSD3DTLVERTEX(const D3DVECTOR& v, float _rhw, D3DCOLOR _color, float _tu=0.f, float _tv=0.f);
};
#define VS_D3DFVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*---------------------------------------------------------------------------
	Strukturen für VSD3DLVERTEX
---------------------------------------------------------------------------*/
struct VSD3DLVERTEX {// Vertex Struktur (transformiert, beleuchtet)
public:
				float x, y, z;
				D3DCOLOR color;
				float tu, tv;

public:
				VSD3DLVERTEX();
			    VSD3DLVERTEX(const D3DVECTOR& v, D3DCOLOR _color, float _tu=0.f, float _tv=0.f);
};
#define VS_D3DFVF_LVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/*---------------------------------------------------------------------------
	Strukturen für VSD3DVERTEX
---------------------------------------------------------------------------*/
struct VSD3DVERTEX {
public:
				float     x, y, z;								// D3DFVF_XYZ
				VECTOR3 vN;										// D3DFVF_NORMAL
				float     tu, tv;								// D3DFVF_TEX1

public:
				VSD3DVERTEX();
				VSD3DVERTEX(const VECTOR3& v, VECTOR3 &_vN, float _tu=0.f, float _tv=0.f);
				void Assign(const VECTOR3& v, VECTOR3 &_vN, float _tu=0.f, float _tv=0.f);
};
#define VS_D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

/*---------------------------------------------------------------------------
	Strukturen für VSVERTEX_XYZ_NORMAL_TEX1
---------------------------------------------------------------------------*/
struct VSD3DVERTEX_DIFFUSE {
public:
				float x, y, z;
				VECTOR3 vN;
				D3DCOLOR diffuse;
				float tu, tv;

public:
				/*
				VSD3DVERTEX_DIFFUSE();
			    VSD3DVERTEX_DIFFUSE(const D3DVECTOR& v, float _tu=0.f, float _tv=0.f);
				VSD3DVERTEX_DIFFUSE(const float _x, const float _y, const float _z, float _tu=0.f, float _tv=0.f);
				*/
				void Assign(const VECTOR3& v, VECTOR3 &_vN, D3DCOLOR &color, float _tu=0.f, float _tv=0.f);
				void Assign(const VECTOR3& v, VECTOR3 &_vN, COLOR4 &color, float _tu=0.f, float _tv=0.f);
};
#define VS_D3DFVF_VERTEX_DIFFUSE (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*---------------------------------------------------------------------------
	Strukturen für VSVERTEX_XYZ_TEX1
---------------------------------------------------------------------------*/
struct VSVERTEX_XYZ_TEX1 {
public:
				float x, y, z;
				VECTOR3 vN;
				float tu, tv;

public:
				VSVERTEX_XYZ_TEX1();
				VSVERTEX_XYZ_TEX1(const VECTOR3& v, const VECTOR3& _vN, float _tu=0.f, float _tv=0.f);
				VSVERTEX_XYZ_TEX1(const VECTOR3 v, const VECTOR3 _vN, float _tu=0.f, float _tv=0.f);
			    VSVERTEX_XYZ_TEX1(const D3DVECTOR& v, float _tu=0.f, float _tv=0.f);
				VSVERTEX_XYZ_TEX1(const float _x, const float _y, const float _z, float _tu=0.f, float _tv=0.f);
};
#define VSFVF_XYZ_TEX1 (D3DFVF_XYZ | D3DFVF_TEX1)

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef VSD3DTLVERTEX				*LPVSD3DTLVERTEX;
typedef VSD3DVERTEX					*LPVSD3DVERTEX;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 VSD3DTLVERTEX		VSD3DTLVERTEXA16;
typedef _ALIGN_16 VSD3DTLVERTEX		*LPVSD3DTLVERTEXA16;
typedef _ALIGN_16 VSD3DVERTEX		VSD3DVERTEXA16;
typedef _ALIGN_16 VSD3DVERTEX		*LPVSD3DVERTEXA16;

typedef _ALIGN_32 VSD3DTLVERTEX		VSD3DTLVERTEXA32;
typedef _ALIGN_32 VSD3DTLVERTEX		*LPVSD3DTLVERTEXA32;
typedef _ALIGN_32 VSD3DVERTEX		VSD3DVERTEXA32;
typedef _ALIGN_32 VSD3DVERTEX		*LPVSD3DVERTEXA32;

typedef _CACHEALIGN VSD3DTLVERTEX	VSD3DTLVERTEXAC;
typedef _CACHEALIGN VSD3DTLVERTEX	*LPVSD3DTLVERTEXAC;
typedef _CACHEALIGN VSD3DVERTEX		VSD3DVERTEXAC;
typedef _CACHEALIGN VSD3DVERTEX		*LPVSD3DVERTEXAC;*/

} //namespace
using namespace VERTICES;