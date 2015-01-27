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

	Dateiname:		texturewarpeffect.h
	Beschreibung:	TextureWarpEffect Definition
	Revision:		1
	Erstellt:		MMT, 19. Juli 2002 03:02

	Changelog:
	[1]		19. Juli 2002 03:02
			Erstellt

===========================================================================*/

#pragma once
/*
#ifndef TEXTUREWARPEFFECT_DEFINED
#define TEXTUREWARPEFFECT_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
*/
/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
//#define VERTEX_GRID_DENSITY 50

/*---------------------------------------------------------------------------
	Klasse FIREEFFECT
---------------------------------------------------------------------------*/
/*
class TEXTUREWARPEFFECT {
//:: Die Membervariablen ....................................................
protected:
	int							m_iTextureSize;

	LPDIRECT3DTEXTURE9			m_pImageTex;
	LPDIRECT3DTEXTURE9			m_pTex1;
	LPDIRECT3DTEXTURE9			m_pTex2;

	LPDIRECT3DTEXTURE9			m_pActiveTex;
	LPDIRECT3DTEXTURE9			m_pScratchTex;

	LPDIRECT3DDEVICE9			m_pd3dDevice;			// Das Direct3D-Device
	LPDIRECT3DVERTEXBUFFER9		m_pVBGrid;
	LPDIRECT3DINDEXBUFFER8		m_pIBGrid;

	int							m_iImageWidth, m_iImageHeight;

//:: Die Konstruktoren ......................................................
public:
							TEXTUREWARPEFFECT();

//:: Die Destruktoren .......................................................
public:
							~TEXTUREWARPEFFECT();

//:: Private Funktionen .....................................................
private:
	void					SetupVertexGrid(LPDIRECT3DVERTEXBUFFER9 pVBGrid, int iGridWidth, int iGridHeight);
	void					ProcessBlendEffect(LPDIRECT3DDEVICE9 pd3dDevice, LPDIRECT3DTEXTURE9 pOrigTex, LPDIRECT3DTEXTURE9 pDestTex, LPDIRECT3DVERTEXBUFFER9 pVBGrid, LPDIRECT3DINDEXBUFFER8 pIBGrid, int iTextureWidth,int iTextureHeight);

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
							operator LPDIRECT3DTEXTURE9 () const;

	// Funktionen: Berechnung ...............................................
	void					Update();
	void					Update(const LPDIRECT3DTEXTURE9 texIn, LPDIRECT3DTEXTURE9 texOut);
	void					Update(LPDIRECT3DTEXTURE9 texOut);

	// Funktionen: Erstellen ................................................
	void					Create(const LPDIRECT3DDEVICE9 pDevice, const int iTextureSize = 128, const float fRefraction = 1.33333f, const float fDepth = 0.5f, const float fDampening = 0.5f);
	void					Restore();
	void					Invalidate();
	void					Delete();

	// Funktionen: Textur ...................................................
	void					GetTexture(LPDIRECT3DTEXTURE9 Texture) const;
	LPDIRECT3DTEXTURE9		GetTexture() const;
	void					SetTextureStages() const;
	void					SetTexture() const;

	// Funktionen: Das Untergrundbild .......................................
	void					SetBaseTexture(LPDIRECT3DTEXTURE9 Texture);

	// Funktionen: Steuerung der Welle ......................................
	void					AddDrop(int iX, int iY, int iSize, int iSplashStrength);
	void					AddDrop();

};
*/
/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
//typedef TEXTUREWARPEFFECT					*LPTEXTUREWARPEFFECT;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*
typedef _ALIGN_16 TEXTUREWARPEFFECT		TEXTUREWARPEFFECTA16;
typedef _ALIGN_16 TEXTUREWARPEFFECT		*LPTEXTUREWARPEFFECTA16;

typedef _ALIGN_32 TEXTUREWARPEFFECT		TEXTUREWARPEFFECTA32;
typedef _ALIGN_32 TEXTUREWARPEFFECT		*LPTEXTUREWARPEFFECTA32;

typedef _CACHEALIGN TEXTUREWARPEFFECT		TEXTUREWARPEFFECTAC;
typedef _CACHEALIGN TEXTUREWARPEFFECT		*LPTEXTUREWARPEFFECTAC;
*/