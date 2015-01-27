/*==========================================================================*
    v-scope: the vision's scope realtime 3D engine
    Copyright (C) 2003, Markus Mayer, Alle Rechte vorbehalten.

	Dieser Quellcode wird "WIE ER IST" vertrieben, ohne jegliche Garantie
	auf Stabilität, Vollständigkeit oder Nützlichkeit für einen bestimmten
	Zweck. Sie sind berechtigt, ihn für jeden beliebigen unkommerziellen 
	Zweck zu nutzen, verändern oder weiter zu vertreiben, solange die
	Copyrightinformation (oben) als Teil dieser Datei erhalten bleibt.
	Der Autor möchte ebenfalls freundlich darum bitten, dass ihm alle 
	signifikanten Änderungen an diesem Quellcode zugeschickt werden.

	Dateiname:		vsfloat.h
	Beschreibung:	VSFLOAT Definition
	Revision:		1
	Erstellt:		MMT, 21. Juni 2003 06:52

	Changelog:
	[1]		21. Juni 2003 06:52
			Erstellt

===========================================================================*/

#pragma once

#ifndef VSFLOAT_DEFINED
#define VSFLOAT_DEFINED

#include "..\defines.h"

namespace TYPES {

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
	Strukturen für die Skybox
---------------------------------------------------------------------------*/
typedef union __declspec(align(4)) VSFLOAT {
public:
	float f;							// float (32bit)
	union value {
		float				f;			// float (32bit)
		unsigned long		uLong;		// unsigned long (32bit)
		signed long			sLong;		// signed long (32bit)
		struct signedShort {
			signed short	sShort1;	// signed short (16bit, high part)
			signed short	sShort2;	// signed short (16bit, low part)
		};
		struct unsignedShort {
			unsigned short	uShort1;	// unsigned short (16bit, high part)
			unsigned short	uShort2;	// unsigned short (16bit, low part)
		};
		signed short		sShort[2];	// signed short, 2x 16bit
		unsigned short		uShort[2];	// unsigned short, 2x 16bit
		unsigned char		uChar[4];	// unsigned char, 4x 1 Byte == 32bit
		signed char			sChar[4];	// signed char, 4x 1 Byte == 32bit
		struct bits {
			unsigned _1 : 1;			// Bit 1
			unsigned _2 : 1;			// Bit 2
			unsigned _3 : 1;			// Bit 3
			unsigned _4 : 1;			// Bit 4
			unsigned _5 : 1;			// Bit 5
			unsigned _6 : 1;			// Bit 6
			unsigned _7 : 1;			// Bit 7
			unsigned _8 : 1;			// Bit 8
			unsigned _9 : 1;			// Bit 9
			unsigned _10 : 1;			// Bit 10
			unsigned _11 : 1;			// Bit 11
			unsigned _12 : 1;			// Bit 12
			unsigned _13 : 1;			// Bit 13
			unsigned _14 : 1;			// Bit 14
			unsigned _15 : 1;			// Bit 15
			unsigned _16 : 1;			// Bit 16
			unsigned _17 : 1;			// Bit 17
			unsigned _18 : 1;			// Bit 18
			unsigned _19 : 1;			// Bit 19
			unsigned _20 : 1;			// Bit 20
			unsigned _21 : 1;			// Bit 21
			unsigned _22 : 1;			// Bit 22
			unsigned _23 : 1;			// Bit 23
			unsigned _24 : 1;			// Bit 24
			unsigned _25 : 1;			// Bit 25
			unsigned _26 : 1;			// Bit 26
			unsigned _27 : 1;			// Bit 27
			unsigned _28 : 1;			// Bit 28
			unsigned _29 : 1;			// Bit 29
			unsigned _30 : 1;			// Bit 30
			unsigned _31 : 1;			// Bit 31
			unsigned _32 : 1;			// Bit 32
		} bits;
		struct bitsFloat {
			unsigned _Mantissa : 23;			// Bit 1 - 24
			unsigned _Exponent : 8;			// Bit 25 - 33
			unsigned _SignBit : 1;			// Bit 34
		} bitsFloat;
	} value;

public:
	VSFLOAT(float in_fFloat) : f(in_fFloat) { }

	VSINLINE operator float();
	VSINLINE operator float&();
	VSINLINE float& operator = (float f);
	VSINLINE float& operator = (VSFLOAT vsf);
	VSINLINE float& operator = (unsigned long ul);
	VSINLINE VSFLOAT& operator--();
	VSINLINE VSFLOAT operator--(int);
	VSINLINE VSFLOAT& operator++();
	VSINLINE VSFLOAT operator++(int);
	VSINLINE float operator()();

	VSINLINE float GetFloat() const;
	VSINLINE unsigned long GetFloatAsInt() const;

	VSINLINE unsigned long GetFlipped();
	VSINLINE void Flip();
	VSINLINE unsigned long GetInverseFlipped();
	VSINLINE void InverseFlip();

	VSINLINE bool IsNegative();
	VSINLINE bool IsPositive();
} VSFLOAT;

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef VSFLOAT					*LPVSFLOAT;

} // namespace
using namespace TYPES;


#endif