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

	Dateiname:		color4.cpp
	Beschreibung:	Color4 Kontainer
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 23:54

	Changelog:
	[1]		09. Juli 2002 23:54

===========================================================================*/

#include "color4.h"
#include "color4.inl.h"

const COLOR4 COLOR4::Black	( 0.0f, 0.0f, 0.0f, 1.0f );
const COLOR4 COLOR4::Gray	( 0.5f, 0.5f, 0.5f, 1.0f );
const COLOR4 COLOR4::White	( 1.0f, 1.0f, 1.0f, 1.0f );
const COLOR4 COLOR4::Red	( 1.0f, 0.0f, 0.0f, 1.0f );
const COLOR4 COLOR4::Green	( 0.0f, 1.0f, 0.0f, 1.0f );
const COLOR4 COLOR4::Blue	( 0.0f, 0.0f, 1.0f, 1.0f );
const COLOR4 COLOR4::Magenta( 1.0f, 0.0f, 1.0f, 1.0f );
const COLOR4 COLOR4::Cyan	( 0.0f, 1.0f, 1.0f, 1.0f );
const COLOR4 COLOR4::Yellow	( 1.0f, 1.0f, 0.0f, 1.0f );