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

	Dateiname:		watereffect.h
	Beschreibung:	WaterEffect Definition
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 23:42

	Changelog:
	[1]		16. Juli 2002 23:42
			Erstellt

===========================================================================*/

#pragma once

#ifndef WATEREFFECT_DEFINED
#define WATEREFFECT_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
//#define TEXTURESIZE 256

/*---------------------------------------------------------------------------
	Klasse FIREEFFECT
---------------------------------------------------------------------------*/
class WATEREFFECT {
//:: Die Membervariablen ....................................................
protected:
	int							m_iTextureSize;

	LPDIRECT3DTEXTURE9			m_pImageTex; // this texture will go "underwater"...
	LPDIRECT3DTEXTURE9			m_pWaterTex; // ... and will appear on this texture.

	LPDIRECT3DDEVICE9			m_pd3dDevice;			// Das Direct3D-Device

	int							*m_iWaterField;  // first water array
	int							*m_iWaterField2; // second water array

	int							*m_pWaterActive;   // we use these two pointers to flip
	int							*m_pWaterScratch;  // the active water array back and forth.
	char						m_lutDisplacement[512]; // displacement lookup table (to optimize calculations)

	float						m_fRefraction;
	float						m_fDepth;
	float						m_fDamp;


//:: Die Konstruktoren ......................................................
public:
							WATEREFFECT();

//:: Die Destruktoren .......................................................
public:
							~WATEREFFECT();

//:: Private Funktionen .....................................................
private:
	void					MakeDisplacementLookupTable();
	void					ProcessWater();
	void VSFASTCALL 		CreateWaterDroplet(int iX, int iY, int iSize, int iSplashStrength, int *waterbuf, int iWaterWidth, int iWaterHeight);
	HRESULT					ProcessTexture();
	bool					CopyToTexture();


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

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef WATEREFFECT					*LPWATEREFFECT;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 WATEREFFECT		WATEREFFECTA16;
typedef _ALIGN_16 WATEREFFECT		*LPWATEREFFECTA16;

typedef _ALIGN_32 WATEREFFECT		WATEREFFECTA32;
typedef _ALIGN_32 WATEREFFECT		*LPWATEREFFECTA32;

typedef _CACHEALIGN WATEREFFECT		WATEREFFECTAC;
typedef _CACHEALIGN WATEREFFECT		*LPWATEREFFECTAC;*/