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

	Dateiname:		particlestorm.h
	Beschreibung:	ParticleStorm Definition
	Revision:		1
	Erstellt:		MMT, 20. Juli 2002 06:58

	Changelog:
	[1]		20. Juli 2002 06:58
			Erstellt

===========================================================================*/

#pragma once

#ifndef PARTICLESTORM_DEFINED
#define PARTICLESTORM_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vertices\vertices.h"
#include "..\bounding\aabbox.h"
#include "particle.h"
#include "..\piped3d2\piped3d2.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
typedef enum PARTICLESYSTEMTYPE {
	PST_GENERIC = 0,					// Standard-System (yuck)
	PST_USERDEFINED
};

/*---------------------------------------------------------------------------
	Strukturen für die PARTICLESTORMSYSTEM
---------------------------------------------------------------------------*/
class PARTICLESTORMSYSTEM {
//:: Die Membervariablen ....................................................
protected:
	unsigned short			m_iEmissionRate;				// Emission in Partikeln pro Sekunde
	VECTOR3					m_vEmissionOriginMin,			// Ursprungsposition der neuen Partikel min, rel. Emitterposition
							m_vEmissionOriginMax;			// Ursprungsposition der neuen Partikel max
	VECTOR3					m_vSystemPos;					// Die Position des Systems
	VECTOR3					m_vEmissionDirectionMin,		// Emissionsrichtung min
							m_vEmissionDirectionMax;		// Emissionsrichtung max

	unsigned short			m_iMaxParticleCount;			// Maximale Anzahl (Arraygröße)
	//unsigned short			m_iParticleCount;				// Anzahl der tatsächlichen Partikel
	unsigned short			m_iParticlesAlive;				// Anzahl lebendiger Partikel

	float					m_fMaxParticleAgeMin,			// Maximale Lebenszeit in Sekunden (~18 Minuten max) min
							m_fMaxParticleAgeMax;			// Maximale Lebenszeit in Sekunden (~18 Minuten max) max

	COLOR4					m_cEmissionColor;				// Startfarbe des Partikels
	float					m_fEmissionSize;				// Startgröße des Partikels
	float					m_fEmissionSpeed;				// Emissionsgeschwindigkeit

	PARTICLE				*m_ParticleList;				// Die Liste aller Partikel

protected:
	LPPIPED3D2				m_pPipe;						// Die Pipeline
	LPDIRECT3DTEXTURE9		m_pTexture;						// Die Basistextur der Partikel
	LPDIRECT3DVERTEXBUFFER9	m_pVB;							// Vertexbuffer für die Partikel
	bool					m_bSystemActive;				// System emittiert (nicht aktualisiert) noch?
	bool					m_bUsePointSprites;				// Werden Point Sprites verwendet?
	bool					m_bHalted;						// System angehalten? (aka bullet time heavy mode)
	PARTICLESYSTEMTYPE		m_SystemType;					// System-ID für den Manager

//:: Die Konstruktoren ......................................................
public:
							PARTICLESTORMSYSTEM();

//:: Die Destruktoren .......................................................
public:
							~PARTICLESTORMSYSTEM();

protected:
	BOOL					DeleteParticleArray();

private:
	void					ClearSystemToZero();

//:: Das Interface ..........................................................
public:
	virtual BOOL			Update(const float fElapsedTime) = 0;
	virtual BOOL			Initialize(PIPED3D2 &in_pPipe, const LPDIRECT3DTEXTURE9 pTexture, const unsigned short iMaxParticles = 500) = 0;
	virtual void			Release();
	virtual BOOL			Render() = 0;

public:
	// Funktionen: Zugriff ..................................................
	PARTICLE&				operator [] ( const unsigned short x ) const;
	PARTICLE&				GetParticle(const unsigned short x) const;
	BOOL					ParticleIsAlive(const unsigned short x) const;
	float					ParticleGetAge(const unsigned short x) const;

	void					DecreaseLivingCount();	// erhöht die Zahl der lebendigen Partikel
	void					IncreaseLivingCount();	// verringert die Zahl der lebendigen Partikel

	unsigned short			GetParticleCount() const;
	unsigned short			GetParticlesAlive() const;
	VECTOR3					GetSystemPos() const;
	void					SetSystemPos(const VECTOR3 &vNewPosition);
	unsigned short			GetMaxParticleCount() const;
	void					SetMaxParticleCount(const unsigned short iCount);
	float					GetMaxParticleAgeMin() const;
	float					GetMaxParticleAgeMax() const;
	void					SetMaxParticleAgeMin(const float fAge);
	void					SetMaxParticleAgeMax(const float fAge);
	unsigned short			GetEmissionRate() const;
	void					SetEmissionRate(const unsigned short iRate);
	VECTOR3					GetEmissionDirectionMin() const;
	VECTOR3					GetEmissionDirectionMax() const;
	void					SetEmissionDirectionMin(const VECTOR3 &vDirection);
	void					SetEmissionDirectionMax(const VECTOR3 &vDirection);
	float					GetEmissionSpeed() const;
	void					SetEmissionSpeed(const float fSpeed);
	COLOR4					GetEmissionColor() const;
	void					SetEmissionColor(const COLOR4 &Color);
	float					GetEmissionSize() const;
	void					SetEmissionSize(const float fSize);
	bool					GetSystemActive() const;
	bool					GetSystemHalted() const;
	void					SetSystemHalted(const bool bHalted);
	PARTICLESYSTEMTYPE		GetSystemType() const;
	LPPIPED3D2				GetPipe() const;
	void					SetPipe(PIPED3D2 &in_pPipe);
	LPDIRECT3DTEXTURE9		GetTexture() const;
	void					SetTexture(const LPDIRECT3DTEXTURE9 pTexture);
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PARTICLESTORMSYSTEM					*LPPARTICLESTORMSYSTEM;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PARTICLESTORMSYSTEM		PARTICLESTORMSYSTEMA16;
typedef _ALIGN_16 PARTICLESTORMSYSTEM		*LPPARTICLESTORMSYSTEMA16;

typedef _ALIGN_32 PARTICLESTORMSYSTEM		PARTICLESTORMSYSTEMA32;
typedef _ALIGN_32 PARTICLESTORMSYSTEM		*LPPARTICLESTORMSYSTEMA32;

typedef _CACHEALIGN PARTICLESTORMSYSTEM		PARTICLESTORMSYSTEMAC;
typedef _CACHEALIGN PARTICLESTORMSYSTEM		*LPPARTICLESTORMSYSTEMAC;*/