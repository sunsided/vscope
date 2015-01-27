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

	Dateiname:		basicemitter.h
	Beschreibung:	ParticleStorm Basic Emitter
	Revision:		1
	Erstellt:		MMT, 20. Juli 2002 17:25

	Changelog:
	[1]		20. Juli 2002 17:25
			Erstellt

===========================================================================*/

#pragma once

#ifndef PS1BASICEMITTER_DEFINED
#define PS1BASICEMITTER_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vertices\vertices.h"
#include "..\bounding\aabbox.h"
#include "particle.h"
#include "particlestorm.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Strukturen für die PARTICLESTORMSYSTEM
---------------------------------------------------------------------------*/
struct PS1BASICEMITTER : public PARTICLESTORMSYSTEM {
//:: Die Membervariablen ....................................................
private:
	unsigned long		m_iLastNew;
	unsigned long		m_iParticlesAliveLastTurn;		// Anzahl lebendiger Partikel in der letzten Runde
	float				m_fNewParticlesExcess;

//:: Das Interface ..........................................................
public:
						PS1BASICEMITTER();
						~PS1BASICEMITTER();

protected:
	long				CreateNewParticle();
	BOOL				CreateParticleArray();

public:
	BOOL				Update(const float in_fElapsedTime);
	BOOL				Initialize(PIPED3D2 &in_pPipe, const LPDIRECT3DTEXTURE9 pTexture, const unsigned short iMaxParticles = 500);
	BOOL				Restore();
	void				Release();
	BOOL				Render();
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PS1BASICEMITTER					*LPPS1BASICEMITTER;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PS1BASICEMITTER		PS1BASICEMITTERA16;
typedef _ALIGN_16 PS1BASICEMITTER		*LPPS1BASICEMITTERA16;

typedef _ALIGN_32 PS1BASICEMITTER		PS1BASICEMITTERA32;
typedef _ALIGN_32 PS1BASICEMITTER		*LPPS1BASICEMITTERA32;

typedef _CACHEALIGN PS1BASICEMITTER		PS1BASICEMITTERAC;
typedef _CACHEALIGN PS1BASICEMITTER		*LPPS1BASICEMITTERAC;*/