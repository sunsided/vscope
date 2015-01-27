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

	Dateiname:		gdibitmap.h
	Beschreibung:	BDI Bitmap Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 14:36

	Changelog:
	[1]		10. Juli 2002 14:36

===========================================================================*/

#pragma once

#ifndef GDIBITMAP_DEFINED
#define GDIBITMAP_DEFINED
#endif

#include "..\defines.h"
#include "..\include-windows.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Struktur für die GDI-Bitmap Klasse
---------------------------------------------------------------------------*/
class GDIBITMAP {
//:: Die Membervariablen ....................................................
private:		
	HDC					m_hdcBitmap;	// DC unserer Bitmap
	HBITMAP				m_hBitmap;		// unsere Bitmap itself
	HBITMAP				m_hOldBitmap;	// 1x1 mono Bitmap
	UINT				m_iWidth;
	UINT				m_iHeight;

//:: Die Konstruktoren ......................................................
public:
						GDIBITMAP();
	virtual				~GDIBITMAP();
	
private:	
	void				Init();
	void				UnInit();

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
						operator HDC () const;

	// Funktionen: Einfach ..................................................
	void				Load(HDC hdcCompatible, LPCSTR lpszFilename);
	void				CreateBlank(HDC hdcCompatible, UINT width, UINT height);
	UINT				GetWidth() const;
	UINT				GetHeight() const;
	HDC					GetBitmapDC() const;
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef GDIBITMAP				*LPGDIBITMAP;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 GDIBITMAP		GDIBITMAPA16;
typedef _ALIGN_16 GDIBITMAP		*LPGDIBITMAPA16;

typedef _ALIGN_32 GDIBITMAP		GDIBITMAPA32;
typedef _ALIGN_32 GDIBITMAP		*LPGDIBITMAPA32;

typedef _CACHEALIGN GDIBITMAP	GDIBITMAPAC;
typedef _CACHEALIGN GDIBITMAP	*LPGDIBITMAPAC;*/