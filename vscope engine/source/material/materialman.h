/*==========================================================================*
    v-scope: the vision's scope realtime 3D engine
    Copyright (C) 2003, Markus Mayer, Alle Rechte vorbehalten.

	Dieser Quellcode wird "WIE ER IST" vertrieben, ohne jegliche Garantie
	auf Stabilität, Vollständigkeit oder Nützlichkeit für einen bestimmten
	Zweck. Sie sind berechtigt, ihn für jeden beliebigen unkommerziellen 
	Zweck zu nutzen, verändern oder weiter zu vertreiben, solange die
	Copyrightinformation (oben) als Teil dieser Datei erhalten bleibt.
	Der Autor möchte ebenfalls freundlich darum bitten, dass ihm alle 
	signifikanten Änderungen an diesem Quellcode zugeschickt werden.

	Dateiname:		materialman.h
	Beschreibung:	Material-Manager Definition
	Revision:		1
	Erstellt:		MMT, 26. Juni 2003 08:35

	Changelog:
	[1]		26. Juni 2003 08:35
			Erstellt

===========================================================================*/

#pragma once

#ifndef MATERIALMAN_DEFINED
#define MATERIALMAN_DEFINED

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\color\color4.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
class PIPED3D2;
struct MATERIAL;

/*---------------------------------------------------------------------------
	Strukturen für die Skybox
---------------------------------------------------------------------------*/
class MATERIALMAN {
friend MATERIAL;
//:: Die Membervariablen ....................................................
public:

protected:
	unsigned short int		m_iMaterialsUsed;
	MATERIAL				*m_pMaterials;
	signed char				m_bIdUsed[32767];	// 0 unused, 1 used =)
public:

//:: Die Konstruktoren ......................................................
public:
							MATERIALMAN();

//:: Die Destruktoren .......................................................
public:
							~MATERIALMAN();

//:: Akzessor ...............................................................
public:
	void					Dummy() {};
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef MATERIALMAN					*LPMATERIALMAN;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 MATERIALMAN		MATERIALMANA16;
typedef _ALIGN_16 MATERIALMAN		*LPMATERIALMANA16;

typedef _ALIGN_32 MATERIALMAN		MATERIALMANA32;
typedef _ALIGN_32 MATERIALMAN		*LPMATERIALMANA32;

typedef _CACHEALIGN MATERIALMAN		MATERIALMANAC;
typedef _CACHEALIGN MATERIALMAN		*LPMATERIALMANAC;*/

#endif