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

	Dateiname:		PerlinNoiseEffect.h
	Beschreibung:	PerlinNoiseEffect Definition
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 21:25

	Changelog:
	[1]		16. Juli 2002 21:25
			Erstellt

===========================================================================*/

#pragma once

#ifndef PERLINNOISEEFFECT_DEFINED
#define PERLINNOISEEFFECT_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\perlinnoise\perlinnoise.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
#define PERLINNOISEMASK 0xFF

/*---------------------------------------------------------------------------
	Klasse FIREEFFECT
---------------------------------------------------------------------------*/
class PERLINNOISEEFFECT {
//:: Die Membervariablen ....................................................
protected:
	PERLINNOISE					m_Generator;
	LPDIRECT3DTEXTURE9			m_Texture;
	int							m_iTextureSize;			// Texturgröße

	float						m_fSeed;

	float						m_fOctaves;
	float						m_fPersistence;

	unsigned char				*m_NoiseBuffer1;		// Erstes Feuer-Array
	unsigned char				*m_NoiseBuffer2;		// Zweites Array

	unsigned char				*m_pActiveBuffer;
	unsigned char				*m_pScratchBuffer;

	PALETTEENTRY				m_Palette[256];

	LPDIRECT3DDEVICE9			m_pd3dDevice;			// Das Direct3D-Device
	LPDIRECT3DTEXTURE9			m_pTexture;				// Die finale Noise-Textur

//:: Die Konstruktoren ......................................................
public:
							PERLINNOISEEFFECT();

//:: Die Destruktoren .......................................................
public:
							~PERLINNOISEEFFECT();

//:: Private Funktionen .....................................................
private:
	void					Process();
	void					Process(const float fTreshold);
	bool					CopyToTexture();

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
							operator LPDIRECT3DTEXTURE9 () const;

	// Funktionen: Berechnung ...............................................
	void					Update();
	void					Update(const float fTreshold);

	// Funktionen: Erstellen ................................................
	void					Create(const LPDIRECT3DDEVICE9 pDevice, const unsigned int iTextureSize = 128, const float &seed = 0.f, const float &persistence = 0.25f, const float &octaves = 4.f);
	void					Restore();
	void					Invalidate();
	void					Delete();

	// Funktionen: Perlin Noise .............................................
	float					GetPersistence() const;
	void					SetPersistence(const float &persistence);
	float					GetOctaves() const;
	void					SetOctaves(const float &octaves);
	float					GetSeed() const;
	void					SetSeed(const float &seed);

	// Funktionen: Textur ...................................................
	void					GetTexture(LPDIRECT3DTEXTURE9 Texture) const;
	LPDIRECT3DTEXTURE9		GetTexture() const;
	void					SetTextureStages() const;
	void					SetTexture() const;

	// Funktionen: Palette ..................................................
	bool					LoadPalette(const char *strBMPfile);
	bool					LoadPalette(const PALETTEENTRY *Palette);
	bool					LoadPalette();
	bool					LoadPaletteInverse();
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PERLINNOISEEFFECT				*LPPERLINNOISEEFFECT;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PERLINNOISEEFFECT		PERLINNOISEEFFECTA16;
typedef _ALIGN_16 PERLINNOISEEFFECT		*LPPERLINNOISEEFFECTA16;

typedef _ALIGN_32 PERLINNOISEEFFECT		PERLINNOISEEFFECTA32;
typedef _ALIGN_32 PERLINNOISEEFFECT		*LPPERLINNOISEEFFECTA32;

typedef _CACHEALIGN PERLINNOISEEFFECT	PERLINNOISEEFFECTAC;
typedef _CACHEALIGN PERLINNOISEEFFECT	*LPPERLINNOISEEFFECTAC;*/