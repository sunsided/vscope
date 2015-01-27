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

	Dateiname:		vector2.inl.h
	Beschreibung:	2D-Vektor Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 16:09

	Changelog:
	[1]		05. Juli 2002 16:09

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "..\matrix\matrix4.h"
#include "..\fastmath\fastsqrt.h"

//:: Die Konstruktoren :::::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR2::VECTOR2() {
}

VSINLINE VECTOR2::VECTOR2(const VECTOR2 &inVec) :
	x( inVec.x ), y( inVec.y ) {
}

VSINLINE VECTOR2::VECTOR2(const VECTOR2 *inVec) :
	x( inVec->x ), y( inVec->y ) {
}

VSINLINE VECTOR2::VECTOR2(const float inx, const float iny) :
	x( inx ), y( iny ) {
}

VSINLINE VECTOR2::VECTOR2(const float *inv) :
	x( inv[0] ), y( inv[1] ) {
}

VSINLINE VECTOR2::VECTOR2(const VECTOR3 &inVec) :
	x( inVec.x ), y( inVec.y ) {
}

VSINLINE VECTOR2::VECTOR2(const VECTOR3 *inVec) :
	x( inVec->x ), y( inVec->y ) {
}

VSINLINE VECTOR2::VECTOR2(const VECTOR4 &inVec) :
	x( inVec.x ), y( inVec.y ) {
}

VSINLINE VECTOR2::VECTOR2(const VECTOR4 *inVec) :
	x( inVec->x ), y( inVec->y ) {
}

VSINLINE VECTOR2::VECTOR2(const D3DXVECTOR2 &inVec) :
	x( inVec.x ), y( inVec.y ) {
}

VSINLINE VECTOR2::VECTOR2(const D3DXVECTOR2 *inVec) :
	x( inVec->x ), y( inVec->y ) {
}

//:: Operatoren: Casting ::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR2::operator float* () const {
	return (float *) &this->x;
}

VSINLINE VECTOR2::operator const float* () const {
	return (const float *) &this->x;
}

VSINLINE VECTOR2::operator D3DXVECTOR2 () const {
	return D3DXVECTOR2(this->x, this->y);
}

VSINLINE VECTOR2::operator const D3DXVECTOR2 () const {
	return (const D3DXVECTOR2) D3DXVECTOR2(this->x, this->y);
}

//:: Operatoren: Casting ::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR2& VECTOR2::operator += ( const VECTOR2 &v ) {
	x += v.x;
	y += v.y;
	return *this;
}

VSINLINE VECTOR2& VECTOR2::operator += ( const D3DXVECTOR2 &v ) {
	x += v.x;
	y += v.y;
	return *this;
}

VSINLINE VECTOR2& VECTOR2::operator -= ( const VECTOR2 &v ) {
	x -= v.x;
	y -= v.y;
	return *this;
}

VSINLINE VECTOR2& VECTOR2::operator -= ( const D3DXVECTOR2 &v ) {
	x -= v.x;
	y -= v.y;
	return *this;
}

VSINLINE VECTOR2& VECTOR2::operator *= ( float f ) {
	x *= f;
	y *= f;
	return *this;
}

VSINLINE VECTOR2& VECTOR2::operator /= ( float f ) {
	float inv_f = 1.f/f;
	x *= inv_f;
	y *= inv_f;
	return *this;
}

VSINLINE VECTOR2& VECTOR2::operator = ( const VECTOR2 &v ) {
	x = v.x;
	y = v.y;
	return *this;
}

VSINLINE VECTOR2& VECTOR2::operator = ( const D3DXVECTOR2 &v ) {
	x = v.x;
	y = v.y;
	return *this;
}

//:: Operatoren: Unär ::::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR2 VECTOR2::operator + () const {
	return VECTOR2(x, y);
}

VSINLINE VECTOR2 VECTOR2::operator - () const {
	return VECTOR2(-x, -y);
}

//:: Operatoren: Binär :::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR2 VECTOR2::operator + ( const VECTOR2& v ) const {
	return VECTOR2(x + v.x, y + v.y);
}

VSINLINE VECTOR2 VECTOR2::operator + ( const D3DXVECTOR2& v ) const {
	return VECTOR2(x + v.x, y + v.y);
}

VSINLINE VECTOR2 VECTOR2::operator - ( const VECTOR2& v ) const {
	return VECTOR2(x - v.x, y - v.y);
}

VSINLINE VECTOR2 VECTOR2::operator - ( const D3DXVECTOR2& v ) const {
	return VECTOR2(x - v.x, y - v.y);
}

VSINLINE VECTOR2 VECTOR2::operator * ( float f ) const {
	return VECTOR2(x * f, y * f);
}

VSINLINE float VECTOR2::operator DOT ( const VECTOR2 &v ) const {
	return this->x*v.x + this->y*v.y;
}

VSINLINE float VECTOR2::operator DOT ( const D3DXVECTOR2 &v ) const {
	return this->x*v.x + this->y*v.y;
}

VSINLINE VECTOR2 VECTOR2::operator / ( float f ) const {
	float fInv = 1.0f / f;
	return VECTOR2(x * fInv, y * fInv);
}

VSINLINE VECTOR2 operator * ( float f, const VECTOR2& v ) {
	return VECTOR2(f * v.x, f * v.y);
}

//:: Operatoren: Vergleich :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE bool VECTOR2::operator == ( const VECTOR2& v ) const {
	return (x == v.x) && (y == v.y);
}

VSINLINE bool VECTOR2::operator == ( const D3DXVECTOR2& v ) const {
	return (x == v.x) && (y == v.y);
}

VSINLINE bool VECTOR2::operator != ( const VECTOR2& v ) const {
	return (x != v.x) || (y != v.y);
}

VSINLINE bool VECTOR2::operator != ( const D3DXVECTOR2& v ) const {
	return (x != v.x) || (y != v.y);
}

//:: Operatoren: Vergleich :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE void VECTOR2::Assign( const float inx, const float iny ) {
	x = inx;
	y = iny;
}

VSINLINE void VECTOR2::Assign( const float *inv ) {
	x = inv[0];
	y = inv[1];
}

VSINLINE void VECTOR2::Assign( const VECTOR2 &inVec ) {
	x = inVec.x;
	y = inVec.y;
}

VSINLINE void VECTOR2::Assign( const VECTOR2 *inVec ) {
	x = inVec->x;
	y = inVec->y;
}

VSINLINE void VECTOR2::Assign( const D3DXVECTOR2 &inVec ) {
	x = inVec.x;
	y = inVec.y;
}

VSINLINE void VECTOR2::Assign( const D3DXVECTOR2 *inVec ) {
	x = inVec->x;
	y = inVec->y;
}

VSINLINE void VECTOR2::Assign( const VECTOR3 &inVec ) {
	x = inVec.x;
	y = inVec.y;
}

VSINLINE void VECTOR2::Assign( const VECTOR3 *inVec ) {
	x = inVec->x;
	y = inVec->y;
}

VSINLINE void VECTOR2::Assign( const VECTOR4 &inVec ) {
	x = inVec.x;
	y = inVec.y;
}

VSINLINE void VECTOR2::Assign( const VECTOR4 *inVec ) {
	x = inVec->x;
	y = inVec->y;
}

//:: Operatoren: Einfach :::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE void VECTOR2::Negate() {
	x = -x;
	y = -y;
}

VSINLINE VECTOR2 VECTOR2::GetNegated() const {
	return VECTOR2( -x, -y );
}

VSINLINE float VECTOR2::GetMag() const {
	return fastsqrt( x*x + y*y );
}

VSINLINE float VECTOR2::GetMagSquared() const {
	return (float)( x*x + y*y );
}

VSINLINE float VECTOR2::GetLength() const {
	return fastsqrt( x*x + y*y );
}

VSINLINE float VECTOR2::GetLengthSquared() const {
	return (float)( x*x + y*y );
}

VSINLINE void VECTOR2::Normalize() {
	float foo=1/GetMag();	
	x*=foo;	
	y*=foo; 
}

VSINLINE VECTOR2 VECTOR2::GetNormalized() const {
	VECTOR2 Vec2(*this);
	Vec2.Normalize();
	return Vec2;
}

//:: Operatoren: Erweitert :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE float VECTOR2::GetDistance( const VECTOR2 &v ) const {
	VECTOR2 Vec2(this->x-v.x, this->y-v.y);
	return Vec2.GetMag();
}

VSINLINE float VECTOR2::GetDistance( const D3DXVECTOR2 &v ) const {
	VECTOR2 Vec2(this->x-v.x, this->y-v.y);
	return Vec2.GetMag();
}

VSINLINE float VECTOR2::Dot( const VECTOR2 &v ) const {
	return this->x*v.x + this->y*v.y;
}

VSINLINE float VECTOR2::Dot( const D3DXVECTOR2 &v ) const {
	return this->x*v.x + this->y*v.y;
}

VSINLINE void VECTOR2::Lerp( const VECTOR2 &v, const float s ) const {
	//OWN: Lineare Interpolation von 2D-Vektoren
	D3DXVec2Lerp((D3DXVECTOR2*)this, (D3DXVECTOR2*)this, (D3DXVECTOR2*)&v, s);
}

VSINLINE VECTOR2 VECTOR2::GetLerped( const VECTOR2 &v, const float s ) const {
	VECTOR2 Vec2;
	D3DXVec2Lerp((D3DXVECTOR2*)&Vec2, (D3DXVECTOR2*)this, (D3DXVECTOR2*)&v, s);
	return Vec2;
}

VSINLINE void VECTOR2::Maximise( const VECTOR2 &v ) {
	if(v.x > this->x) this->x = v.x;
	if(v.y > this->y) this->y = v.y;
}

VSINLINE VECTOR2 VECTOR2::GetMaximised( const VECTOR2 &v ) const {
	VECTOR2 Vec2;
	Vec2.x = (v.x>Vec2.x)?v.x:this->x;
	Vec2.y = (v.y>Vec2.y)?v.y:this->y;
	return Vec2;
}

VSINLINE void VECTOR2::Minimise( const VECTOR2 &v ) {
	if(v.x < this->x) this->x = v.x;
	if(v.y < this->y) this->y = v.y;
}

VSINLINE VECTOR2 VECTOR2::GetMinimised( const VECTOR2 &v ) const {
	VECTOR2 Vec2;
	Vec2.x = (v.x>Vec2.x)?v.x:this->x;
	Vec2.y = (v.y<Vec2.y)?v.y:this->y;
	return Vec2;
}

VSINLINE void VECTOR2::Scale( const float s ) {
	this->x *= s;
	this->y *= s;
}

VSINLINE VECTOR2 VECTOR2::GetScaled( const float s ) const {
	return VECTOR2(x*s, y*s);
}

VSINLINE void VECTOR2::Add( const VECTOR2 &v ) {
	x += v.x;
	y += v.y;
}

VSINLINE VECTOR2 VECTOR2::GetAdded( const VECTOR2 &v ) const {
	return VECTOR2(x+v.x, y+v.y);
}

VSINLINE void VECTOR2::Subtract( const VECTOR2 &v ) {
	x -= v.x;
	y -= v.y;
}

VSINLINE VECTOR2 VECTOR2::GetSubtracted( const VECTOR2 &v ) const {
	return VECTOR2(x-v.x, y-v.y);
}

VSINLINE void VECTOR2::Transform( const MATRIX4 &m ) {
	VECTOR4 Vec4;
	D3DXVec2Transform((D3DXVECTOR4*)&Vec4, (D3DXVECTOR2*)this, (D3DXMATRIX*)&m);
	this->x = Vec4.x;
	this->y = Vec4.y;
}

VSINLINE VECTOR2 VECTOR2::GetTransformed( const MATRIX4 &m ) const {
	VECTOR2 Vec4;
	D3DXVec2Transform((D3DXVECTOR4*)&Vec4, (D3DXVECTOR2*)this, (D3DXMATRIX*)&m);
	return VECTOR2(Vec4.x, Vec4.y);
}

VSINLINE void VECTOR2::TransformCoord( const MATRIX4 &m ) {
	D3DXVec2TransformCoord((D3DXVECTOR2*)this, (D3DXVECTOR2*)this, (D3DXMATRIX*)&m);
}

VSINLINE VECTOR2 VECTOR2::GetTransformCoord( const MATRIX4 &m ) const {
	VECTOR2 Vec2;
	D3DXVec2TransformCoord((D3DXVECTOR2*)&Vec2, &((D3DXVECTOR2)*this), (D3DXMATRIX*)&m);
	return Vec2;
}

VSINLINE void VECTOR2::TransformNormal( const MATRIX4 &m ) {
	D3DXVec2TransformNormal((D3DXVECTOR2*)this, &((D3DXVECTOR2)*this), (D3DXMATRIX*)&m);
}

VSINLINE VECTOR2 VECTOR2::GetTransformNormal( const MATRIX4 &m ) const {
	VECTOR2 Vec2;
	D3DXVec2TransformNormal((D3DXVECTOR2*)&Vec2, &((D3DXVECTOR2)*this), (D3DXMATRIX*)&m);
	return Vec2;
}

VSINLINE void VECTOR2::BaryCentric( const VECTOR2 &v1, const VECTOR2 &v2, const VECTOR2 &v3, const float f, const float g ) {
	//OWN: Baryzentrische Koordinaten für Vektor2
	D3DXVec2BaryCentric((D3DXVECTOR2*)this, (D3DXVECTOR2*)&v1, (D3DXVECTOR2*)&v2, (D3DXVECTOR2*)&v3, f, g);
}

VSINLINE VECTOR2 VECTOR2::GetBaryCentric( const VECTOR2 &v1, const VECTOR2 &v2, const VECTOR2 &v3, const float f, const float g ) const {
	VECTOR2 Vec2;
	D3DXVec2BaryCentric((D3DXVECTOR2*)&Vec2, (D3DXVECTOR2*)&v1, (D3DXVECTOR2*)&v2, (D3DXVECTOR2*)&v3, f, g);
	return Vec2;
}

VSINLINE void VECTOR2::CatmullRom( const VECTOR2 &v1, const VECTOR2 &v2, const VECTOR2 &v3, const VECTOR2 &v4, const float s ) {
	//OWN: CatmullRom für Vektor2
	D3DXVec2CatmullRom((D3DXVECTOR2*)this, (D3DXVECTOR2*)&v1, (D3DXVECTOR2*)&v2, (D3DXVECTOR2*)&v3, (D3DXVECTOR2*)&v4, s);
}

VSINLINE VECTOR2 VECTOR2::GetCatmullRom( const VECTOR2 &v1, const VECTOR2 &v2, const VECTOR2 &v3, const VECTOR2 &v4, const float s ) const {
	VECTOR2 Vec2;
	D3DXVec2CatmullRom((D3DXVECTOR2*)&Vec2, (D3DXVECTOR2*)&v1, (D3DXVECTOR2*)&v2, (D3DXVECTOR2*)&v3, (D3DXVECTOR2*)&v4, s);
	return Vec2;
}

VSINLINE void VECTOR2::Hermite( const VECTOR2 &v1, const VECTOR2 &t1, const VECTOR2 &v2, const VECTOR2 &t2, const float s ) {
	//OWN: Hermite für Vektor2
	D3DXVec2Hermite((D3DXVECTOR2*)this, (D3DXVECTOR2*)&v1, (D3DXVECTOR2*)&t1, (D3DXVECTOR2*)&v2, (D3DXVECTOR2*)&t2, s);
}

VSINLINE VECTOR2 VECTOR2::GetHermite( const VECTOR2 &v1, const VECTOR2 &t1, const VECTOR2 &v2, const VECTOR2 &t2, const float s ) const {
	VECTOR2 Vec2;
	D3DXVec2Hermite((D3DXVECTOR2*)&Vec2, (D3DXVECTOR2*)&v1, (D3DXVECTOR2*)&t1, (D3DXVECTOR2*)&v2, (D3DXVECTOR2*)&t2, s);
	return Vec2;
}