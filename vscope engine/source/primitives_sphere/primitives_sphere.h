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

	Dateiname:		primitives_sphere.h
	Beschreibung:	Sphere Definition
	Revision:		1
	Erstellt:		MMT, 14. Juni 2003 14:01

	Changelog:
	[1]		14. Juni 2003 14:01
			Erstellt

===========================================================================*/

#pragma once

#ifndef PRIMITIVESSPHERE_DEFINED
#define PRIMITIVESSPHERE_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vertices\vertices.h"
#include "..\piped3d2\piped3d2.h"

//#define SKYBOX_STRICT

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
class VIEWCONE;
struct VECTOR3;

/*---------------------------------------------------------------------------
	Strukturen für die Skybox
---------------------------------------------------------------------------*/
struct PRIMITIVE_SPHERE {
//:: Die Membervariablen ....................................................
protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVBsphere;
	unsigned int				m_iEdges;
	unsigned int				m_iRows;
	//unsigned int				m_iVertexCount = (m_iEdges+1) * 2 * m_iRows * 2 /*Hälften*/;
	float						m_fRadius;
	float						m_fNormalFactor;
	VSD3DVERTEX_DIFFUSE			*m_pVertices;
	LPPIPED3D2					m_pPipe;

public:

//:: Die Konstruktoren ......................................................
public:
							PRIMITIVE_SPHERE();
							PRIMITIVE_SPHERE(PIPED3D2 &in_pPipe, const unsigned int in_iEdges = 16 , const unsigned int in_iRows = 4, const float in_fRadius = 3.f, const float in_fNormalFactor = 1.f);

private:
	void					_Initialize();
	unsigned int			_GetVertexCount() const;

//:: Die Destruktoren .......................................................
public:
	virtual ~PRIMITIVE_SPHERE();

//:: Das Interface ..........................................................

private:
	// Funktionen: Erstellen der Skybox .....................................
	HRESULT	VSFASTCALL 		Create();
public:
	HRESULT	VSFASTCALL 		Create(PIPED3D2 &in_pPipe, const unsigned int in_iEdges = 16 , const unsigned int in_iRows = 4, const float in_fRadius = 3.f, const float in_fNormalFactor = 1.f);

/*
	// Funktionen: Texturspezifisch .........................................
	void					SetTextures(const LPDIRECT3DTEXTURE9 *Textures);
	void					SetTextures(const unsigned int Index, const LPDIRECT3DTEXTURE9 Texture);
	void					GetTextures(LPDIRECT3DTEXTURE9 *Textures) const;
	void					GetTextures(unsigned int Index, LPDIRECT3DTEXTURE9 Texture) const;
*/
	// Funktionen: Rendering ................................................
	HRESULT					Render();
/*
	int VSFASTCALL 			Render(const float cameraX, const float cameraY, const float cameraZ);

	// Funktionen: Rendering mit VFD ........................................

	int 					Render(const VIEWCONE *ViewCone);
	int VSFASTCALL 			Render(const VIEWCONE *ViewCone, const float cameraX, const float cameraY, const float cameraZ);

	// Funktionen: Texturfilterung ..........................................
	void					SetFiltering(const D3DTEXTUREFILTERTYPE FilterType = D3DTEXF_ANISOTROPIC);
	D3DTEXTUREFILTERTYPE	GetFiltering() const;
*/
	// Funktionen: Freigeben ................................................
	void VSFASTCALL			Release();
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PRIMITIVE_SPHERE					SPHERE;
typedef PRIMITIVE_SPHERE					*LPSPHERE;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*
typedef _ALIGN_16 PRIMITIVE_SPHERE		SPHEREA16;
typedef _ALIGN_16 PRIMITIVE_SPHERE		*LPSPHEREA16;

typedef _ALIGN_32 PRIMITIVE_SPHERE		SPHEREA32;
typedef _ALIGN_32 PRIMITIVE_SPHERE		*LPSPHEREA32;

typedef _CACHEALIGN PRIMITIVE_SPHERE		SPHEREAC;
typedef _CACHEALIGN PRIMITIVE_SPHERE		*LPSPHEREAC;*/