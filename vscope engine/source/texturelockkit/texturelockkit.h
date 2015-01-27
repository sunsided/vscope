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

	Dateiname:		texturelockkit.h
	Beschreibung:	TextureLock Kit Definition
	Revision:		1
	Erstellt:		MMT, 17. Juli 2002 21:03

	Changelog:
	[1]		17. Juli 2002 21:03
			Erstellt

===========================================================================*/

#pragma once

#ifndef TEXTURELOCKKIT_DEFINED
#define TEXTURELOCKKIT_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"


/*---------------------------------------------------------------------------
	Klasse FIREEFFECT
---------------------------------------------------------------------------*/
class TEXTURELOCKKIT {
//:: Die Membervariablen ....................................................
private:
	LPDIRECT3DTEXTURE9		m_Texture;
	bool					m_bLocked;
	int						m_iLockLevel;
public:
	D3DLOCKED_RECT			LockedRect;
	unsigned int			PitchOverhead;
	unsigned int			Pitch;
	D3DSURFACE_DESC			SurfaceDesc;
	unsigned char			BytesPerPixel;

//:: Die Konstruktoren ......................................................
public:
							TEXTURELOCKKIT();

//:: Die Destruktoren .......................................................
public:
							~TEXTURELOCKKIT();

//:: Das Interface ..........................................................
public:
	// Funktionen: Zugriff ..................................................
	void					AccessArrayDWORD(DWORD *pData);
	void					AccessArrayWORD(WORD *pData);
	void					AccessArrayChar(unsigned char *pData);

	// Funktionen: Lock/Unlock ..............................................
	HRESULT					Lock(LPDIRECT3DTEXTURE9 Texture, const unsigned int iMIPlevel = 0, const RECT *LockRect = NULL, const DWORD lLockFlags = 0);
	HRESULT					Unlock();
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef TEXTURELOCKKIT					*LPTEXTURELOCKKIT;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 TEXTURELOCKKIT		TEXTURELOCKKITA16;
typedef _ALIGN_16 TEXTURELOCKKIT		*LPTEXTURELOCKKITA16;

typedef _ALIGN_32 TEXTURELOCKKIT		TEXTURELOCKKITA32;
typedef _ALIGN_32 TEXTURELOCKKIT		*LPTEXTURELOCKKITA32;

typedef _CACHEALIGN TEXTURELOCKKIT		TEXTURELOCKKITAC;
typedef _CACHEALIGN TEXTURELOCKKIT		*LPTEXTURELOCKKITAC;*/