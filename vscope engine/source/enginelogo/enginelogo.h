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

	Dateiname:		enginelogo.h
	Beschreibung:	EngineLogo Definition
	Revision:		2
	Erstellt:		MMT, 10. Juli 2002 00:16

	Changelog:
	[2]		15. Juli 2002 00:18
			Neuer Konstruktor (Pipe-Direktübergabe)
	[1]		10. Juli 2002 00:16

===========================================================================*/

#pragma once

#ifndef ENGINELOGO_DEFINED
#define ENGINELOGO_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Struktur für die 3-Byte-Farbe
---------------------------------------------------------------------------*/
class ENGINELOGO {
//:: Die Membervariablen ....................................................
private:		
	LPDIRECT3DTEXTURE9	LogoTexture;

//:: Die Konstruktoren ......................................................
public:
						ENGINELOGO();
						ENGINELOGO(LPDIRECT3DDEVICE9 in_Device);

//:: Die Destruktoren .......................................................
public:
						~ENGINELOGO();

//:: Das Interface ..........................................................
public:
	// Funktionen: Einfach ..................................................
	void VSFASTCALL		Render(LPDIRECT3DDEVICE9 in_Device, UINT Alpha = 192);
	void VSFASTCALL		Load(LPDIRECT3DDEVICE9 in_Device);
	void VSINLINE		Release();
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef ENGINELOGO				*LPENGINELOGO;