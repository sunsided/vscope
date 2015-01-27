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

	Dateiname:		perlinnoise.inl.h
	Beschreibung:	Perlin Noise Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 18:55

	Changelog:
	[1]		07. Juli 2002 16:59

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "perlinnoise.h"

VSINLINE float& PERLINNOISE::GetOctaves() const {
	return (float&)this->octaves;
}

VSINLINE float& PERLINNOISE::GetPersistence() const {
	return (float&)this->persistence;
}

VSINLINE void PERLINNOISE::Init(const float &persistence, const float &octaves) {
	this->persistence = persistence;
	this->octaves = octaves;
}

VSINLINE PERLINNOISE::PERLINNOISE() {
	this->persistence = 0.25f;
	this->octaves = 4.f;
}

VSINLINE PERLINNOISE::PERLINNOISE( const float &persistence, const float &octaves ) {
	this->persistence = persistence;
	this->octaves = octaves;
}