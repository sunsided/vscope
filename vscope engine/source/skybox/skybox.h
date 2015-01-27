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

	Dateiname:		skybox.h
	Beschreibung:	Skybox Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 18:09

	Changelog:
	[1]		10. Juli 2002 18:09
			Erstellt

===========================================================================*/

#pragma once

#ifndef SKYBOX_DEFINED
#define SKYBOX_DEFINED
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
struct SKYBOX {
//:: Die Membervariablen ....................................................
protected:
	float						m_fWidth;		// Die Dimension der Skybox (Breite)
	LPPIPED3D2					m_pPipe;		// Spart die Übergabe bei jedem Aufruf
	DWORD						m_fFilter;		// Texturfilterung
	LPDIRECT3DVERTEXBUFFER9		m_skyVB;		// Nur aus Spaß an der Freude ...
	VSVERTEX_XYZ_TEX1			m_skyVertices[24];
public:
	LPDIRECT3DTEXTURE9			m_Texture[6];	// Die Texturen

//:: Die Konstruktoren ......................................................
public:
							SKYBOX();
							SKYBOX(PIPED3D2 &in_pPipe);
							SKYBOX(PIPED3D2 &in_pPipe, const float Width);
							SKYBOX(PIPED3D2 &in_pPipe, const float Width, const LPDIRECT3DTEXTURE9 *Textures);
							SKYBOX(PIPED3D2 &in_pPipe, const float Width, const LPDIRECT3DTEXTURE9 texFront, const LPDIRECT3DTEXTURE9 texRight, const LPDIRECT3DTEXTURE9 texBack, const LPDIRECT3DTEXTURE9 texLeft, const LPDIRECT3DTEXTURE9 texTop, const LPDIRECT3DTEXTURE9 texBottom);

//:: Die Destruktoren .......................................................
public:
	virtual ~SKYBOX();

//:: Das Interface ..........................................................
public:
	// Funktionen: Erstellen der Skybox .....................................
	HRESULT	VSFASTCALL 		Create(PIPED3D2 &in_pPipe);
	HRESULT	VSFASTCALL 		Create(PIPED3D2 &in_pPipe, const float Width);

	// Funktionen: Texturspezifisch .........................................
	void					SetTextures(const LPDIRECT3DTEXTURE9 *Textures);
	void					SetTextures(const unsigned int Index, const LPDIRECT3DTEXTURE9 Texture);
	void					GetTextures(LPDIRECT3DTEXTURE9 *Textures) const;
	void					GetTextures(unsigned int Index, LPDIRECT3DTEXTURE9 Texture) const;

	// Funktionen: Rendering ................................................
	int 					Render(const VECTOR3 CameraPosition);
	int VSFASTCALL 			Render(const float cameraX, const float cameraY, const float cameraZ);

	// Funktionen: Rendering mit VFD ........................................
	int 					Render(const VIEWCONE *ViewCone, const VECTOR3 CameraPosition);
	int VSFASTCALL 			Render(const VIEWCONE *ViewCone, const float cameraX, const float cameraY, const float cameraZ);

	// Funktionen: Texturfilterung ..........................................
	void					SetFiltering(const D3DTEXTUREFILTERTYPE FilterType = D3DTEXF_ANISOTROPIC);
	D3DTEXTUREFILTERTYPE	GetFiltering() const;

	// Funktionen: Freigeben ................................................
	void VSFASTCALL			Release(BOOL AlsoReleaseTextures = FALSE);
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef SKYBOX					*LPSKYBOX;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 SKYBOX		SKYBOXA16;
typedef _ALIGN_16 SKYBOX		*LPSKYBOXA16;

typedef _ALIGN_32 SKYBOX		SKYBOXA32;
typedef _ALIGN_32 SKYBOX		*LPSKYBOXA32;

typedef _CACHEALIGN SKYBOX		SKYBOXAC;
typedef _CACHEALIGN SKYBOX		*LPSKYBOXAC;*/