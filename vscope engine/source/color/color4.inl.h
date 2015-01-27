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

	Dateiname:		color4.inl.h
	Beschreibung:	Color4 Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 09. Juli 2002 23:54

	Changelog:
	[1]		09. Juli 2002 23:54

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "color4.h"
#include "color3.h"
#include "..\include-direct3d.h"
#include "..\fastmath\fastassort.h"

VSINLINE COLOR4::COLOR4() {
}

VSINLINE COLOR4::COLOR4( const COLOR3& in, const unsigned char alpha) {
	r = (float)in.r * VAL1d255;
	g = (float)in.g * VAL1d255;
	b = (float)in.b * VAL1d255;
	a = (float)alpha * VAL1d255;
}

VSINLINE void COLOR4::Assign( const unsigned char inR, const unsigned char inG, const unsigned char inB, const unsigned char inA ) {
	r = (float)inR * VAL1d255;
	g = (float)inG * VAL1d255;
	b = (float)inB * VAL1d255;
	a = (float)inA * VAL1d255;
}

VSINLINE void COLOR4::Assign( const float inR, const float inG, const float inB, const float inA ) {
	r = inR;
	g = inG;
	b = inB;
	a = inA;
}


VSINLINE unsigned long COLOR4::MakeDWord() const {
	unsigned long dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned long) (r * 255.0f + 0.5f);
	unsigned long dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned long) (g * 255.0f + 0.5f);
	unsigned long dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned long) (b * 255.0f + 0.5f);
	unsigned long dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned long) (a * 255.0f + 0.5f);
	return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

VSINLINE void COLOR4::MakeDWord(unsigned long& out_iColor) const {
	unsigned long dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned long) (r * 255.0f + 0.5f);
	unsigned long dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned long) (g * 255.0f + 0.5f);
	unsigned long dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned long) (b * 255.0f + 0.5f);
	unsigned long dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned long) (a * 255.0f + 0.5f);
	out_iColor = (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

/**
* Adds two colors together: ret = a + b
*/
VSINLINE COLOR4 operator+(COLOR4 const &a, COLOR4 const &b) {
	return COLOR4
	(
		a.r+b.r,
		a.g+b.g,
		a.b+b.b,
		a.a+b.a
	);
}; 
	

/**
* Subtracts two colors : ret = a - b
*/
VSINLINE COLOR4 operator-(COLOR4 const &a, COLOR4 const &b) {
	return COLOR4
	(
		a.r-b.r,
		a.g-b.g,
		a.b-b.b,
		a.a-b.a
	);
}; 


/**
* Scales a color by a float : ret = a * b
*/
VSINLINE COLOR4 operator*(COLOR4 const &a, const unsigned char &b) {
	return COLOR4
	(
		a.r*b,
		a.g*b,
		a.b*b,
		a.a*b
	);
}; 


/**
* Scales a color by a float : ret = a * b
*/
VSINLINE COLOR4 operator*(const unsigned char &a, COLOR4 const &b) {
	return COLOR4
	(
		a*b.r,
		a*b.g,
		a*b.b,
		a*b.a
	);
}; 


/**
* Divides a color by a float : ret = a / b
*/
VSINLINE COLOR4 operator/(COLOR4 const &a, const unsigned char &b) {
	return COLOR4
	(
		a.r/b,
		a.g/b,
		a.b/b,
		a.a/b
	);
}; 

/**
* Divides a color by a color (piecewise): ret = a / b
*/
VSINLINE COLOR4 operator/(COLOR4 const &a, COLOR4 const &b) {
	return COLOR4
	(
		a.r / b.r,
		a.g / b.g,
		a.b / b.b,
		a.a / b.a
	);
}; 

/**
* Multiplies a color by a color (piecewise): ret = a / b
*/
VSINLINE COLOR4 operator*(COLOR4 const &a, COLOR4 const &b) {
	return COLOR4
	(
		a.r * b.r,
		a.g * b.g,
		a.b * b.b,
		a.a * b.a
	);
}; 


/**
* color Equality, epsilon used due to numerical imprecision
*/
VSINLINE bool operator==(COLOR4 const &a, COLOR4 const &b) {
	if(EQUALS(a.r,b.r))
		if(EQUALS(a.g,b.g))
			if(EQUALS(a.b,b.b))
				if(EQUALS(a.a,b.a))
					return true;
	return false;
};


// ************************************************************************


VSINLINE COLOR4::COLOR4( unsigned long dw ) {
	const float f = 1.0f / 255.0f;
	r = f * (float) (unsigned char) (dw >> 16);
	g = f * (float) (unsigned char) (dw >>  8);
	b = f * (float) (unsigned char) (dw >>  0);
	a = f * (float) (unsigned char) (dw >> 24);
}

VSINLINE COLOR4::COLOR4( const float* pf ) {
	r = pf[0];
	g = pf[1];
	b = pf[2];
	a = pf[3];
}

VSINLINE COLOR4::COLOR4( const D3DCOLORVALUE& c ) {
	r = c.r;
	g = c.g;
	b = c.b;
	a = c.a;
}

VSINLINE COLOR4::COLOR4( float fr, float fg, float fb, float fa ) {
	r = fr;
	g = fg;
	b = fb;
	a = fa;
}


// casting
VSINLINE COLOR4::operator unsigned long () const {
	unsigned long dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned long) (r * 255.0f + 0.5f);
	unsigned long dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned long) (g * 255.0f + 0.5f);
	unsigned long dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned long) (b * 255.0f + 0.5f);
	unsigned long dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned long) (a * 255.0f + 0.5f);

	return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}


VSINLINE COLOR4::operator float * () {
	return (float *) &r;
}

VSINLINE COLOR4::operator const float * () const {
	return (const float *) &r;
}


VSINLINE COLOR4::operator D3DCOLORVALUE * () {
	return (D3DCOLORVALUE *) &r;
}

VSINLINE COLOR4::operator const D3DCOLORVALUE * () const {
	return (const D3DCOLORVALUE *) &r;
}


VSINLINE COLOR4::operator D3DCOLORVALUE& () {
	return *((D3DCOLORVALUE *) &r);
}

VSINLINE COLOR4::operator const D3DCOLORVALUE& () const {
	return *((const D3DCOLORVALUE *) &r);
}

// assignment operators
VSINLINE COLOR4& COLOR4::operator += ( const COLOR4& c ) {
	r += c.r;
	g += c.g;
	b += c.b;
	a += c.a;
	return *this;
}

VSINLINE COLOR4& COLOR4::operator -= ( const COLOR4& c ) {
	r -= c.r;
	g -= c.g;
	b -= c.b;
	a -= c.a;
	return *this;
}

VSINLINE COLOR4& COLOR4::operator *= ( float f ) {
	r *= f;
	g *= f;
	b *= f;
	a *= f;
	return *this;
}

VSINLINE COLOR4& COLOR4::operator /= ( float f ) {
	float fInv = 1.0f / f;
	r *= fInv;
	g *= fInv;
	b *= fInv;
	a *= fInv;
	return *this;
}


// unary operators
VSINLINE COLOR4 COLOR4::operator + () const {
	return *this;
}

VSINLINE COLOR4 COLOR4::operator - () const {
	return COLOR4(-r, -g, -b, -a);
}


// binary operators
VSINLINE COLOR4 COLOR4::operator + ( const COLOR4& c ) const {
	return COLOR4(r + c.r, g + c.g, b + c.b, a + c.a);
}

VSINLINE COLOR4 COLOR4::operator - ( const COLOR4& c ) const {
	return COLOR4(r - c.r, g - c.g, b - c.b, a - c.a);
}

VSINLINE COLOR4 COLOR4::operator * ( float f ) const {
	return COLOR4(r * f, g * f, b * f, a * f);
}

VSINLINE COLOR4 COLOR4::operator / ( float f ) const {
	float fInv = 1.0f / f;
	return COLOR4(r * fInv, g * fInv, b * fInv, a * fInv);
}


VSINLINE COLOR4 operator * (float f, const COLOR4& c ) {
	return COLOR4(f * c.r, f * c.g, f * c.b, f * c.a);
}


VSINLINE bool COLOR4::operator == ( const COLOR4& c ) const {
	return r == c.r && g == c.g && b == c.b && a == c.a;
}

VSINLINE bool COLOR4::operator != ( const COLOR4& c ) const {
	return r != c.r || g != c.g || b != c.b || a != c.a;
}