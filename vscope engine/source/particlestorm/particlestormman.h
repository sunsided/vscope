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

	Dateiname:		particlestormman.h
	Beschreibung:	ParticleStorm Manager Definition
	Revision:		1
	Erstellt:		MMT, 20. Juli 2002 16:17

	Changelog:
	[1]		20. Juli 2002 16:17
			Erstellt

===========================================================================*/

#pragma once

#ifndef PARTICLESTORMMAN_DEFINED
#define PARTICLESTORMMAN_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vertices\vertices.h"
#include "particle.h"
#include "particlestorm.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Strukturen für PARTICLESTORMMAN
---------------------------------------------------------------------------*/
class PARTICLESTORMMAN {
//:: Die Membervariablen ....................................................
private:

//:: Die Konstruktoren ......................................................
public:
							PARTICLESTORMMAN();

//:: Die Destruktoren .......................................................
public:
							~PARTICLESTORMMAN();

//:: Das Interface ..........................................................
public:

};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PARTICLESTORMMAN				*LPPARTICLESTORMMAN;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PARTICLESTORMMAN		PARTICLESTORMMANA16;
typedef _ALIGN_16 PARTICLESTORMMAN		*LPPARTICLESTORMMANA16;

typedef _ALIGN_32 PARTICLESTORMMAN		PARTICLESTORMMANA32;
typedef _ALIGN_32 PARTICLESTORMMAN		*LPPARTICLESTORMMANA32;

typedef _CACHEALIGN PARTICLESTORMMAN	PARTICLESTORMMANAC;
typedef _CACHEALIGN PARTICLESTORMMAN	*LPPARTICLESTORMMANAC;*/