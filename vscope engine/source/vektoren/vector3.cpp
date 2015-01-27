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

	Dateiname:		vector3.h
	Beschreibung:	3D-Vektor Kontainer
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:37

	Changelog:
	[1]		04. Juli 2002 23:37

===========================================================================*/

#include "vector3.h"

const VECTOR3 VECTOR3::Zero( 0.f,0.f,0.f );
const VECTOR3 VECTOR3::i( 1.f, 0.f, 0.f );
const VECTOR3 VECTOR3::j( 0.f, 1.f, 0.f );
const VECTOR3 VECTOR3::k( 0.f, 0.f, 1.f );