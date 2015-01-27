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

	Dateiname:		color4.h
	Beschreibung:	Color4 Definition
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 23:54

	Changelog:
	[1]		09. Juli 2002 23:54

===========================================================================*/

#pragma once

#ifndef COLOR4_DEFINED
#define COLOR4_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct COLOR3;

/*---------------------------------------------------------------------------
	Struktur für die 4-unsigned char-Farbe
---------------------------------------------------------------------------*/
struct COLOR4 {
//:: Die Membervariablen ....................................................
public:		
					union {
						struct {
							float r, g, b, a;		// 0.f .. 1.f
						};
						float f[4];
					};

//:: Die Konstruktoren ......................................................
public:
						COLOR4();
						COLOR4( const COLOR3& in, const unsigned char alpha = 1.0f );
						COLOR4( unsigned long dw );
						COLOR4( const unsigned char* pf );
						COLOR4( const D3DCOLORVALUE& c );
						COLOR4( const float* pf );
						COLOR4( float fr, float fg, float fb, float fa );


//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
						operator unsigned long () const;
						operator float * ();
						operator const float * () const;
						operator D3DCOLORVALUE * ();
						operator const D3DCOLORVALUE * () const;	
						operator D3DCOLORVALUE& ();
						operator const D3DCOLORVALUE& () const;
						operator D3DCOLORVALUE ();
						operator const D3DCOLORVALUE () const;	

	// Operatoren: Zuweisung ................................................	
	COLOR4&				operator += ( const COLOR4& c );
	COLOR4&				operator -= ( const COLOR4& c );
	COLOR4&				operator *= ( float f );
	COLOR4&				operator /= ( float f );
	COLOR4&				operator *= ( const unsigned char in );
	COLOR4&				operator /= ( const unsigned char in );

	// Operatoren: Unär .....................................................
	COLOR4				operator + () const;
	COLOR4				operator - () const;

	// Operatoren: Binär ....................................................
	COLOR4				operator + ( const COLOR4& c ) const;
	COLOR4				operator - ( const COLOR4& c ) const;
	COLOR4				operator * ( float f ) const;
	COLOR4				operator / ( float f ) const;
	bool				operator == ( const COLOR4& c ) const;
	bool				operator != ( const COLOR4& c ) const;

	// Funktionen: Einfach ..................................................
	void				Assign( const unsigned char inR, const unsigned char inG, const unsigned char inB, const unsigned char inA );
	void				Assign( const float inR, const float inG, const float inB, const float inA );
	unsigned long		MakeDWord() const;
	void				MakeDWord(unsigned long& out_iColor) const;

	// Statische Variablen ..................................................
	static const COLOR4 Black;
	static const COLOR4 Gray;
	static const COLOR4 White;
	static const COLOR4 Red;
	static const COLOR4 Green;
	static const COLOR4 Blue;
	static const COLOR4 Magenta;
	static const COLOR4 Cyan;
	static const COLOR4 Yellow;
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef COLOR4					*LPCOLOR4;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 COLOR4		COLOR4A16;
typedef _ALIGN_16 COLOR4		*LPCOLOR4A16;

typedef _ALIGN_32 COLOR4		COLOR4A32;
typedef _ALIGN_32 COLOR4		*LPCOLOR4A32;

typedef _CACHEALIGN COLOR4		COLOR4AC;
typedef _CACHEALIGN COLOR4		*LPCOLOR4AC;*/