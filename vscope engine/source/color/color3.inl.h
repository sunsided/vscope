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

	Dateiname:		color3.inl.h
	Beschreibung:	Color3 Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 23:39

	Changelog:
	[1]		09. Juli 2002 23:39

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "color3.h"
#include "..\fastmath\fastassort.h"

VSINLINE COLOR3::COLOR3() {
}

VSINLINE COLOR3::COLOR3( const unsigned char inR, const unsigned char inG, const unsigned char inB ) :
	r( inR ), g( inG ), b( inB )
{
}

VSINLINE void COLOR3::Assign( const unsigned char inR, const unsigned char inG, const unsigned char inB ) {
	r = inR;
	g = inG;
	b = inB;
}

VSINLINE unsigned long COLOR3::MakeDWord() const {
	unsigned long iR = (int)(r) << 16;
	unsigned long iG = (int)(g) << 8;
	unsigned long iB = (int)(b);
	return 0xff000000 | iR | iG | iB;
}

VSINLINE COLOR3::operator unsigned long () const {
	unsigned long iR = (int)(r) << 16;
	unsigned long iG = (int)(g) << 8;
	unsigned long iB = (int)(b);
	return 0xff000000 | iR | iG | iB;
}

VSINLINE COLOR3::operator const unsigned long () const {
	unsigned long iR = (int)(r) << 16;
	unsigned long iG = (int)(g) << 8;
	unsigned long iB = (int)(b);
	return 0xff000000 | iR | iG | iB;
}

/**
* Accumulative addition of two colors
*/
VSINLINE COLOR3& COLOR3::operator += ( const COLOR3& in ) {
	r += in.r;   
	g += in.g;   
	b += in.b;
	return *this;
}


/**
* Accumulative subtraction of two colors
*/
VSINLINE COLOR3& COLOR3::operator -= ( const COLOR3& in ) {
	r -= in.r;   
	g -= in.g;   
	b -= in.b;
	return *this;
}


/**
* Accumulative multiplication of a color by a scalar
*/
VSINLINE COLOR3& COLOR3::operator *= ( const unsigned char in ) {
	r *= in;   
	g *= in;   
	b *= in;
	return *this;
}


/**
* Accumulative division of a color by a scalar
*/
VSINLINE COLOR3& COLOR3::operator /= ( const unsigned char in ) {
	r = (const unsigned char)(r / in);
	g = (const unsigned char)(g / in);   
	b = (const unsigned char)(b / in);
	return *this;
}


/**
* Adds two colors together: ret = a + b
*/
VSINLINE COLOR3 operator+(const COLOR3 &a, const COLOR3 &b) {
	return COLOR3 (
		a.r+b.r,
		a.g+b.g,
		a.b+b.b
	);
}; 
	

/**
* Subtracts two colors : ret = a - b
*/
VSINLINE COLOR3 operator-(const COLOR3 &a, const COLOR3 &b) {
	return COLOR3 (
		a.r-b.r,
		a.g-b.g,
		a.b-b.b
	);
}; 


/**
* Scales a color by a float : ret = a * b
*/
VSINLINE COLOR3 operator*(const COLOR3 &a, const unsigned char &b) {
	return COLOR3 (
		a.r*b,
		a.g*b,
		a.b*b
	);
}; 


/**
* Scales a color by a float : ret = a * b
*/
VSINLINE COLOR3 operator*(const unsigned char &a, const COLOR3 &b) {
	return COLOR3 (
		a*b.r,
		a*b.g,
		a*b.b
	);
}; 


/**
* Divides a color by a float : ret = a / b
*/
VSINLINE COLOR3 operator/(const COLOR3 &a, const unsigned char &b) {
	return COLOR3 (
		(const unsigned char)(a.r / b),
		(const unsigned char)(a.g / b),
		(const unsigned char)(a.b / b)
	);
}; 


/**
* color Equality, epsilon used due to numerical imprecision
*/
VSINLINE bool operator==(const COLOR3 &a, const COLOR3 &b) {
	if(EQUALS(a.r,b.r))
		if(EQUALS(a.g,b.g))
			if(EQUALS(a.b,b.b))
				return true;
	return false;
};