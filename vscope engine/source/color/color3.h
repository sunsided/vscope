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

	Dateiname:		color3.h
	Beschreibung:	Color3 Definition
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 23:39

	Changelog:
	[1]		09. Juli 2002 23:39

===========================================================================*/

#pragma once

#ifndef COLOR3_DEFINED
#define COLOR3_DEFINED
#endif

#include "..\defines.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Struktur für die 3-Byte-Farbe
---------------------------------------------------------------------------*/
struct COLOR3 {
//:: Die Membervariablen ....................................................
public:		
					union {
						struct {
							unsigned char r, g, b; // Red, Green, and Blue color data
						};
						unsigned char c[3];
					};

//:: Die Konstruktoren ......................................................
public:
						COLOR3();
						COLOR3( const unsigned char inR, const unsigned char inG, const unsigned char inB );

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
						operator unsigned long () const;
						operator const unsigned long () const;

	// Operatoren: Binär ....................................................
	COLOR3&				operator += ( const COLOR3& in );
	COLOR3&				operator -= ( const COLOR3& in );
	COLOR3&				operator *= ( const unsigned char in );
	COLOR3&				operator /= ( const unsigned char in );

	// Funktionen: Einfach ..................................................
	void				Assign( const unsigned char inR, const unsigned char inG, const unsigned char inB );
	unsigned long		MakeDWord() const;

	// Statische Variablen ..................................................
	static const COLOR3 Black;
	static const COLOR3 Gray;
	static const COLOR3 White;
	static const COLOR3 Red;
	static const COLOR3 Green;
	static const COLOR3 Blue;
	static const COLOR3 Magenta;
	static const COLOR3 Cyan;
	static const COLOR3 Yellow;
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef COLOR3					*LPCOLOR3;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 COLOR3		COLOR3A16;
typedef _ALIGN_16 COLOR3		*LPCOLOR3A16;

typedef _ALIGN_32 COLOR3		COLOR3A32;
typedef _ALIGN_32 COLOR3		*LPCOLOR3A32;

typedef _CACHEALIGN COLOR3		COLOR3AC;
typedef _CACHEALIGN COLOR3		*LPCOLOR3AC;*/