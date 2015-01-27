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

	Dateiname:		primitives_ring.h
	Beschreibung:	Primitive: Ring Header
	Revision:		1
	Erstellt:		MMT, 29. Mai 2003 13:03

	Changelog:
	[1]		29. Mai 2003 13:03
			Erstellt

===========================================================================*/

#pragma once

#ifndef PRIMITIVE_RING_DEFINED
#define PRIMITIVE_RING_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vertices\vertices.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct VECTOR2;
struct VECTOR3;
struct AABBOX3;

/*---------------------------------------------------------------------------
	Strukturen für die Skybox
---------------------------------------------------------------------------*/
struct PRIMITIVE_RING {
//:: Die Membervariablen ....................................................
protected:
	float						m_fRadius;		// Der Radius des Kreises
	LPDIRECT3DDEVICE9			m_pd3dDevice;	// Spart die Übergabe bei jedem Aufruf
	LPDIRECT3DVERTEXBUFFER9		m_RingVB;		// Nur aus Spaß an der Freude ...
	VSVERTEX_XYZ_TEX1			*m_RingVertices;
	unsigned int				m_iSegments;	// Kreissegmente
	unsigned int				m_iRows;		// Hoehensegmente

//:: Die Konstruktoren ......................................................
public:
							PRIMITIVE_RING();
							//PRIMITIVE_RING(const LPDIRECT3DDEVICE9 in_Device);
							//PRIMITIVE_RING(const LPDIRECT3DDEVICE9 in_Device, const float in_fInnerRadius = 2.f, const float in_fOuterRadius = 3.f, const unsigned int in_iSegments = 8, const unsigned int in_iRows = 1);

//:: Die Destruktoren .......................................................
public:
	virtual					~PRIMITIVE_RING();

//:: Das Interface ..........................................................
public:
	// Funktionen: Erstellen der Vertices ...................................
	HRESULT	VSFASTCALL 		Create(const float in_fInnerRadius = 2.f, const float in_fOuterRadius = 3.f, const unsigned int in_iSegments = 8, const unsigned int in_iRows = 1, const bool in_bFirstVertexUp = false);
	HRESULT	VSFASTCALL 		Create(const LPDIRECT3DDEVICE9 in_Device, const float in_fInnerRadius = 2.f,const float in_fOuterRadius = 3.f, const unsigned int in_iSegments = 8, const unsigned int in_iRows = 1, const bool in_bFirstVertexUp = false);

	unsigned int VSFASTCALL ExportVertices(VSVERTEX_XYZ_TEX1 *out_VertexArray, const float in_fInnerRadius = 2.f, const float in_fOuterRadius = 3.f, const unsigned int in_iSegments = 8, const unsigned int in_iRows = 1, const bool in_bFirstVertexUp = false);

	// Funktionen: Rendering ................................................
	int VSFASTCALL			Render();

	// Kollisions-Tests
	AABBOX3					GetAABB();

	// Funktionen: Freigeben ................................................
	void VSFASTCALL			Release();
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PRIMITIVE_RING						RING;
typedef PRIMITIVE_RING						*LPRING;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PRIMITIVE_RING			RINGA16;
typedef _ALIGN_16 PRIMITIVE_RING			*LPRINGA16;

typedef _ALIGN_32 PRIMITIVE_RING			RINGA32;
typedef _ALIGN_32 PRIMITIVE_RING			*LPRINGA32;

typedef _CACHEALIGN PRIMITIVE_RING			RINGAC;
typedef _CACHEALIGN PRIMITIVE_RING			*LPRINGAC;*/