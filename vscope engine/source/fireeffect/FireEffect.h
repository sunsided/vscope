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

	Dateiname:		FireEffect.h
	Beschreibung:	FireEffect Definition
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 16:58

	Changelog:
	[1]		16. Juli 2002 16:58
			Erstellt

===========================================================================*/

#pragma once

#ifndef FIREEFFECT_DEFINED
#define FIREEFFECT_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Klasse FIREEFFECT
---------------------------------------------------------------------------*/
class FIREEFFECT {
//:: Die Membervariablen ....................................................
protected:
  int						m_iCoolAmount;		// Abkühlung pro Frame
  int						m_iTextureSize;		// Texturgröße

  unsigned char				*m_FireBuffer1;		// Erstes Feuer-Array
  unsigned char				*m_FireBuffer2;		// Zweites Array

  unsigned char				*m_pActiveBuffer;
  unsigned char				*m_pScratchBuffer;

  PALETTEENTRY				m_Palette[256];

  LPDIRECT3DDEVICE9			m_pd3dDevice;		// Das Direct3D-Device
  LPDIRECT3DTEXTURE9		m_pTexture;			// Die finale Feuer-Textur

  static unsigned char		m_FireRed[256];
  static unsigned char		m_FireGreen[256];
  static unsigned char		m_FireBlue[256];

//:: Die Konstruktoren ......................................................
public:
							FIREEFFECT();

//:: Die Destruktoren .......................................................
public:
							~FIREEFFECT();

//:: Private Funktionen .....................................................
private:
	void 					Process();
	bool					CopyToTexture();

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
							operator LPDIRECT3DTEXTURE9 () const;

	// Funktionen: Berechnung ...............................................
	void					Update();
	void					Update(const float fDelayInS);

	// Funktionen: Erstellen ................................................
	void					Create(const LPDIRECT3DDEVICE9 pDevice, const unsigned int iTextureSize = 128, const int iCoolAmount = 1);
	void					Restore();
	void					Invalidate();
	void					Delete();

	// Funktionen: Cooling ..................................................
	int						GetCoolAmount() const;
	void					SetCoolAmount(const int coolamount);

	// Funktionen: Textur ...................................................
	void					GetTexture(LPDIRECT3DTEXTURE9 Texture) const;
	LPDIRECT3DTEXTURE9		GetTexture() const;
	void					SetTextureStages() const;
	void					SetTexture() const;

	// Funktionen: Palette ..................................................
	bool					LoadPalette(const char *strBMPfile);
	void					LoadPalette(const PALETTEENTRY *Palette);
	void					LoadPalette();
	void					LoadPaletteRBG();
	void					LoadPaletteGRB();
	void					LoadPaletteGBR();
	void					LoadPaletteBGR();
	void					LoadPaletteBRG();

};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef FIREEFFECT				*LPFIREEFFECT;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 FIREEFFECT	FIREEFFECTA16;
typedef _ALIGN_16 FIREEFFECT	*LPFIREEFFECTA16;

typedef _ALIGN_32 FIREEFFECT	FIREEFFECTA32;
typedef _ALIGN_32 FIREEFFECT	*LPFIREEFFECTA32;

typedef _CACHEALIGN FIREEFFECT	FIREEFFECTAC;
typedef _CACHEALIGN FIREEFFECT	*LPFIREEFFECTAC;*/