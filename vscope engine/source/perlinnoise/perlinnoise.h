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

	Dateiname:		perlinnoise.h
	Beschreibung:	Perlin Noise Definition
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 18:55

	Changelog:
	[1]		07. Juli 2002 16:59

===========================================================================*/

#pragma once

#ifndef PERLINNOISE_DEFINED
#define PERLINNOISE_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

/*---------------------------------------------------------------------------
	Struktur für die Perlin Noise Klasse
---------------------------------------------------------------------------*/
class PERLINNOISE {
//:: Die Membervariablen ....................................................
public:		
	float persistence;
	float octaves;

	//:: Die Konstruktoren ......................................................
public:
						PERLINNOISE();
						PERLINNOISE( const float &persistence, const float &octaves );

//:: Die kleinen Helferlein .................................................
protected:
	float virtual VSFASTCALL SmoothedNoise( const unsigned int x ) const;
	float virtual VSFASTCALL SmoothedNoise( const unsigned int x, const unsigned int y ) const;
	float virtual VSFASTCALL InterpolatedNoise( const float x ) const;
	float virtual VSFASTCALL InterpolatedNoise( const float x, const float y ) const;

//:: Das Interface ..........................................................
public:
	void				Init(const float &persistence, const float &octaves);
	float&				GetPersistence() const;
	float&				GetOctaves() const;
	float VSFASTCALL	GetNoise( const float x ) const;
	float VSFASTCALL	GetNoise( const float x, const float y ) const;
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PERLINNOISE				*LPPERLINNOISE;