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

	Dateiname:		particle.h
	Beschreibung:	Partikel Definition
	Revision:		1
	Erstellt:		MMT, 20. Juli 2002 07:03

	Changelog:
	[2]		29. Mai 2003 18:01
			Überarbeitet+Aktualisiert
	[1]		20. Juli 2002 07:03
			Erstellt

===========================================================================*/

#pragma once

#ifndef PARTICLE_DEFINED
#define PARTICLE_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vertices\vertices.h"
#include "..\color\color4.h"
#include "..\vektoren\vector3.h"

namespace VERTICES {

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
typedef struct VERTEX_T1_PARTICLE {
	D3DXVECTOR3		position;
	float			pointsize;
	D3DCOLOR		color;
} VERTEX_T1_PARTICLE;
#define D3DFVF_T1_PARTICLE (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_PSIZE)

} // namespace
using namespace VERTICES;

/*---------------------------------------------------------------------------
	Strukturen für die PARTICLESTORM
---------------------------------------------------------------------------*/
#pragma pack(push)
#pragma pack(4)
struct __declspec(align(4)) PARTICLE {
//:: Die Membervariablen ....................................................
public:
	VECTOR3					m_vPosition;		// Positionsvektor
	VECTOR3					m_vOldPosition;		// vorheriger Positionsvektor
	VECTOR3					m_vSpeed;			// Geschwindigkeit
	float					m_fAge;				// Energie/Alter
	float					m_fMaxAge;			// Maximales Alter
	float					m_fSize;			// Partikelgröße (Radius)
	COLOR4					m_vColor;			// Farbe
	bool					m_bAlive;			// Partikel aktiv?

//:: Die Konstruktoren ......................................................
public:
							PARTICLE();

//:: Die Destruktoren .......................................................
public:
							~PARTICLE();

//:: Helferlein .............................................................
protected:
	bool					_CheckAge(float in_fElapsedTime);		// Injuranzer freuen sich: der Todes-Check

//:: Das Interface ..........................................................
public:
	void					Accelerate(VECTOR3 &in_vForce, float in_fElapsedTime);	// "Kollisions"- und "Kraft"beschleunigung (externe g, etc.)
	HRESULT					Update(float in_fElapsedTime);	// Aktualisiert Alter und Position
	void					GetParticleVertex(VERTEX_T1_PARTICLE *out_vtxVertex);

};
#pragma pack(pop)

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PARTICLE					*LPPARTICLE;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PARTICLE			PARTICLEA16;
typedef _ALIGN_16 PARTICLE			*LPPARTICLEA16;

typedef _ALIGN_32 PARTICLE			PARTICLEA32;
typedef _ALIGN_32 PARTICLE			*LPPARTICLEA32;

typedef _CACHEALIGN PARTICLE		PARTICLEAC;
typedef _CACHEALIGN PARTICLE		*LPPARTICLEAC;*/