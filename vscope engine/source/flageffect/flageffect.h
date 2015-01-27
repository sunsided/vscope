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

	Dateiname:		flageffect.h
	Beschreibung:	FlagEffect Definition
	Revision:		1
	Erstellt:		MMT, 17. Juli 2002 18:35

	Changelog:
	[1]		17. Juli 2002 18:35
			Erstellt

===========================================================================*/

#pragma once

#ifndef FLAGEFFECT_DEFINED
#define FLAGEFFECT_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
#define VAL360d129				2.7906976744186046511627906976744f

/*---------------------------------------------------------------------------
	Klasse FIREEFFECT
---------------------------------------------------------------------------*/
class FLAGEFFECT {
//:: Die Membervariablen ....................................................
protected:
	LPDIRECT3DDEVICE9			m_pd3dDevice;			// Das Direct3D-Device
	int							m_iTextureSize;

	LPDIRECT3DTEXTURE9			m_pInputTex;
	LPDIRECT3DTEXTURE9			m_pFlagTex;

	int							m_SinLUT[128];

//:: Die Konstruktoren ......................................................
public:
							FLAGEFFECT();

//:: Die Destruktoren .......................................................
public:
							~FLAGEFFECT();

//:: Private Funktionen .....................................................
private:
	void					ProcessFlag();
	bool					CopyToTexture();
	void					CalcSINLUT();


//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
							operator LPDIRECT3DTEXTURE9 () const;

	// Funktionen: Berechnung ...............................................
	void					Update();
	void					Update(const LPDIRECT3DTEXTURE9 texIn, LPDIRECT3DTEXTURE9 texOut);
	void					Update(LPDIRECT3DTEXTURE9 texOut);

	// Funktionen: Erstellen ................................................
	void					Create(const LPDIRECT3DDEVICE9 pDevice, const int iTextureSize = 128);
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

};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef FLAGEFFECT					*LPFLAGEFFECT;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 FLAGEFFECT		FLAGEFFECTA16;
typedef _ALIGN_16 FLAGEFFECT		*LPFLAGEFFECTA16;

typedef _ALIGN_32 FLAGEFFECT		FLAGEFFECTA32;
typedef _ALIGN_32 FLAGEFFECT		*LPFLAGEFFECTA32;

typedef _CACHEALIGN FLAGEFFECT		FLAGEFFECTAC;
typedef _CACHEALIGN FLAGEFFECT		*LPFLAGEFFECTAC;*/