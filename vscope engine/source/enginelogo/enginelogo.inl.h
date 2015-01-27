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

	Dateiname:		enginelogo.inl.h
	Beschreibung:	EngineLogo Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 00:16

	Changelog:
	[1]		10. Juli 2002 00:16

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "enginelogo.h"

VSINLINE ENGINELOGO::ENGINELOGO() {
	this->LogoTexture = NULL;
}

VSINLINE ENGINELOGO::~ENGINELOGO() {
	this->Release();
}

VSINLINE void ENGINELOGO::Release() {
	if(this->LogoTexture) {
		this->LogoTexture->Release();
		this->LogoTexture = NULL;
	}
}