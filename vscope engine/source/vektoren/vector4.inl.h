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

	Dateiname:		vector4.inl.h
	Beschreibung:	4D-Vektor Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 16:09

	Changelog:
	[1]		05. Juli 2002 16:09
			Verwendung von intrinsischen memcpys und memcmps

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "vector4.h"
#include "vector2.h"
#include "vector3.h"
#include "..\matrix\matrix4.h"
#include "..\fastmath\fastsqrt.h"

#pragma intrinsic(memcpy)
#pragma intrinsic(memcmp)

//:: Die Konstruktoren :::::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR4::VECTOR4() {
}

VSINLINE VECTOR4::VECTOR4(const VECTOR4 &inVec) :
	x( inVec.x ), y( inVec.y ), z( inVec.z ), w( inVec.w ) {
}

VSINLINE VECTOR4::VECTOR4(const VECTOR4 *inVec) :
	x( inVec->x ), y( inVec->y ), z( inVec->z ), w( inVec->w ) {
}

VSINLINE VECTOR4::VECTOR4(const float inx, const float iny, const float inz, const float inw) :
	x( inx ), y( iny ), z( inz ), w( inw ) {
}

VSINLINE VECTOR4::VECTOR4(const float *inv) :
	x( inv[0] ), y( inv[1] ), z( inv[2] ), w( inv[3] ) {
}

VSINLINE VECTOR4::VECTOR4(const VECTOR2 &inVec) :
	x( inVec.x ), y( inVec.y ), z( 0.f ), w( 0.f ) {
}

VSINLINE VECTOR4::VECTOR4(const VECTOR2 *inVec) :
	x( inVec->x ), y( inVec->y ), z( 0.f ), w( 0.f ) {
}

VSINLINE VECTOR4::VECTOR4(const VECTOR3 &inVec) :
	x( inVec.x ), y( inVec.y ), z( inVec.z ), w( 0.f ) {
}

VSINLINE VECTOR4::VECTOR4(const VECTOR3 *inVec) :
	x( inVec->x ), y( inVec->y ), z( inVec->z ), w( 0.f ) {
}

VSINLINE VECTOR4::VECTOR4(const D3DXVECTOR4 &inVec) :
	x( inVec.x ), y( inVec.y ), z( inVec.z ), w( inVec.w ) {
}

VSINLINE VECTOR4::VECTOR4(const D3DXVECTOR4 *inVec) :
	x( inVec->x ), y( inVec->y ), z( inVec->z ), w( inVec->w ) {
}

//:: Operatoren: Casting ::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR4::operator float* () const {
	return (float *) &this->x;
}

VSINLINE VECTOR4::operator const float* () const {
	return (const float *) &this->x;
}

VSINLINE VECTOR4::operator D3DXVECTOR4 () const {
	return D3DXVECTOR4(this->x, this->y, this->z, this->w);
}

VSINLINE VECTOR4::operator const D3DXVECTOR4 () const {
	return (const D3DXVECTOR4) D3DXVECTOR4(this->x, this->y, this->z, this->w);
}

VSINLINE VECTOR4::operator D3DXVECTOR3 () const {
	return D3DXVECTOR3(this->x, this->y, this->z);
}

VSINLINE VECTOR4::operator const D3DXVECTOR3 () const {
	return (const D3DXVECTOR3) D3DXVECTOR3(this->x, this->y, this->z);
}

VSINLINE VECTOR4::operator VECTOR3 () const {
	return VECTOR3(this->x, this->y, this->z);
}

VSINLINE VECTOR4::operator const VECTOR3 () const {
	return (const VECTOR3) VECTOR3(this->x, this->y, this->z);
}

//:: Operatoren: Casting ::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR4& VECTOR4::operator += ( const VECTOR4 &v ) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

VSINLINE VECTOR4& VECTOR4::operator += ( const D3DXVECTOR4 &v ) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

VSINLINE VECTOR4& VECTOR4::operator -= ( const VECTOR4 &v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

VSINLINE VECTOR4& VECTOR4::operator -= ( const D3DXVECTOR4 &v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

VSINLINE VECTOR4& VECTOR4::operator *= ( float f ) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

VSINLINE VECTOR4& VECTOR4::operator /= ( float f ) {
	float inv_f = 1.f/f;
	x *= inv_f;
	y *= inv_f;
	z *= inv_f;
	w *= inv_f;
	return *this;
}

VSINLINE VECTOR4& VECTOR4::operator = ( const VECTOR4 &v ) {
	/*
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	*/
	memcpy(this, &v, sizeof(float)*4);
	return *this;
}

VSINLINE VECTOR4& VECTOR4::operator = ( const D3DXVECTOR4 &v ) {
	/*
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	*/
	memcpy(this, &v, sizeof(float)*4);
	return *this;
}

//:: Operatoren: Unär ::::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR4 VECTOR4::operator + () const {
	return VECTOR4(x, y, z, w);
}

VSINLINE VECTOR4 VECTOR4::operator - () const {
	return VECTOR4(-x, -y, -z, -w);
}

//:: Operatoren: Binär :::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR4 VECTOR4::operator + ( const VECTOR4& v ) const {
	return VECTOR4(x + v.x, y + v.y, z + v.z, w + v.w);
}

VSINLINE VECTOR4 VECTOR4::operator + ( const D3DXVECTOR4& v ) const {
	return VECTOR4(x + v.x, y + v.y, z + v.z, w + v.w);
}

VSINLINE VECTOR4 VECTOR4::operator - ( const VECTOR4& v ) const {
	return VECTOR4(x - v.x, y - v.y, z - v.z, w - v.w);
}

VSINLINE VECTOR4 VECTOR4::operator - ( const D3DXVECTOR4& v ) const {
	return VECTOR4(x - v.x, y - v.y, z - v.z, w - v.w);
}

VSINLINE VECTOR4 VECTOR4::operator * ( float f ) const {
	return VECTOR4(x * f, y * f, z * f, w * f);
}

VSINLINE float VECTOR4::operator DOT ( const VECTOR4 &v ) const {
	return this->x*v.x + this->y*v.y + this->z*v.z + this->w*v.w;
}

VSINLINE float VECTOR4::operator DOT ( const D3DXVECTOR4 &v ) const {
	return this->x*v.x + this->y*v.y + this->z*v.z + this->w*v.w;
}

/*
VSINLINE VECTOR4 VECTOR4::operator CROSS ( const VECTOR4 &b) const {
	return VECTOR4(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
}

VSINLINE VECTOR4 VECTOR4::operator CROSS ( const D3DXVECTOR4 &b) const {
	return VECTOR4(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
}
*/

VSINLINE VECTOR4 VECTOR4::operator / ( float f ) const {
	float fInv = 1.0f / f;
	return VECTOR4(x * fInv, y * fInv, z * fInv, w * fInv);
}

VSINLINE VECTOR4 operator * ( float f, const VECTOR4& v ) {
	return VECTOR4(f * v.x, f * v.y, f * v.z, f * v.w);
}

//:: Operatoren: Vergleich :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE bool VECTOR4::operator == ( const VECTOR4& v ) const {
	//return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
	return (memcmp(*this, &v, sizeof(float)*4)==0)?true:false;
}

VSINLINE bool VECTOR4::operator == ( const D3DXVECTOR4& v ) const {
	//return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
	return (memcmp(*this, &v, sizeof(float)*4)==0)?true:false;
}

VSINLINE bool VECTOR4::operator != ( const VECTOR4& v ) const {
	//return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
	return (memcmp(*this, &v, sizeof(float)*4)!=0)?true:false;
}

VSINLINE bool VECTOR4::operator != ( const D3DXVECTOR4& v ) const {
	//return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
	return (memcmp(*this, &v, sizeof(float)*4)!=0)?true:false;
}

//:: Operatoren: Vergleich :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE void VECTOR4::Assign( const float inx, const float iny, const float inz, const float inw ) {
	x = inx;
	y = iny;
	z = inz;
	w = inw;
}

VSINLINE void VECTOR4::Assign( const float *inv ) {
	/*
	x = inv[0];
	y = inv[1];
	z = inv[2];
	w = inv[3];
	*/
	memcpy(this, inv, sizeof(float)*4);
}

VSINLINE void VECTOR4::Assign( const VECTOR4 &inVec ) {
	/*
	x = inVec.x;
	y = inVec.y;
	z = inVec.z;
	w = inVec.w;
	*/
	memcpy(this, &inVec, sizeof(float)*4);
}

VSINLINE void VECTOR4::Assign( const VECTOR4 *inVec ) {
	/*
	x = inVec->x;
	y = inVec->y;
	z = inVec->z;
	w = inVec->w;
	*/
	memcpy(this, inVec, sizeof(float)*4);
}

VSINLINE void VECTOR4::Assign( const D3DXVECTOR4 &inVec ) {
	/*
	x = inVec.x;
	y = inVec.y;
	z = inVec.z;
	w = inVec.w;
	*/
	memcpy(this, &inVec, sizeof(float)*4);
}

VSINLINE void VECTOR4::Assign( const VECTOR2 &inVec ) {
	/*
	x = inVec.x;
	y = inVec.y;
	*/
	z = 0.f;
	w = 0.f;
	memcpy(this, &inVec, sizeof(float)*2);
}

VSINLINE void VECTOR4::Assign( const VECTOR2 *inVec ) {
	/*
	x = inVec->x;
	y = inVec->y;
	*/
	z = 0.f;
	w = 0.f;
	memcpy(this, inVec, sizeof(float)*2);
}

VSINLINE void VECTOR4::Assign( const VECTOR3 &inVec ) {
	/*
	x = inVec.x;
	y = inVec.y;
	z = inVec.z;
	*/
	w = 0.f;
	memcpy(this, &inVec, sizeof(float)*3);
}

VSINLINE void VECTOR4::Assign( const VECTOR3 *inVec ) {
	/*
	x = inVec->x;
	y = inVec->y;
	z = inVec->z;
	*/
	w = 0.f;
	memcpy(this, inVec, sizeof(float)*3);
}

VSINLINE void VECTOR4::Assign( const D3DXVECTOR4 *inVec ) {
	/*
	x = inVec->x;
	y = inVec->y;
	z = inVec->z;
	w = inVec->w;
	*/
	memcpy(this, inVec, sizeof(float)*4);
}

//:: Operatoren: Einfach :::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE void VECTOR4::Negate() {
	x = -x;
	y = -y;
	z = -z;
	w = -w;
}

VSINLINE VECTOR4 VECTOR4::GetNegated() const {
	return VECTOR4( -x, -y, -z, -w );
}

VSINLINE float VECTOR4::GetMag() const {
	return fastsqrt( x*x + y*y + z*z + w*w );
}

VSINLINE float VECTOR4::GetMagSquared() const {
	return (float)( x*x + y*y + z*z + w*w );
}

VSINLINE float VECTOR4::GetLength() const {
	return fastsqrt( x*x + y*y + z*z + w*w );
}

VSINLINE float VECTOR4::GetLengthSquared() const {
	return (float)( x*x + y*y + z*z + w*w );
}

VSINLINE void VECTOR4::Normalize() {
	float foo=1/GetMag();	
	x*=foo;
	y*=foo;
	z*=foo;
	w*=foo;
}

VSINLINE VECTOR4 VECTOR4::GetNormalized() const {
	VECTOR4 Vec4(*this);
	Vec4.Normalize();
	return Vec4;
}

//:: Operatoren: Erweitert :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE float VECTOR4::GetDistance( const VECTOR4 &v ) const {
	VECTOR4 Vec4(this->x-v.x, this->y-v.y, this->z - v.z, this->w - v.w);
	return Vec4.GetMag();
}

VSINLINE float VECTOR4::GetDistance( const D3DXVECTOR4 &v ) const {
	VECTOR4 Vec4(this->x-v.x, this->y-v.y, this->z - v.z, this->w - v.w);
	return Vec4.GetMag();
}

VSINLINE float VECTOR4::Dot( const VECTOR4 &v ) const {
	return this->x*v.x + this->y*v.y + this->z*v.z + this->w*v.w;
}

VSINLINE float VECTOR4::Dot( const D3DXVECTOR4 &v ) const {
	return this->x*v.x + this->y*v.y + this->z*v.z + this->w*v.w;
}

/*
VSINLINE VECTOR4 VECTOR4::Cross(const VECTOR4& v) const {
	return VECTOR4(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}

VSINLINE void VECTOR4::ToCross(const VECTOR4& v) {
	this->x		= this->y * v.z - this->z * v.y;
	this->y		= this->z * v.x - this->x * v.z;
	this->z		= this->x * v.y - this->y * v.x;
}

VSINLINE VECTOR4 VECTOR4::Cross(const D3DXVECTOR4& v) const {
	return VECTOR4(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}

VSINLINE void VECTOR4::ToCross(const D3DXVECTOR4& v) {
	this->x		= this->y * v.z - this->z * v.y;
	this->y		= this->z * v.x - this->x * v.z;
	this->z		= this->x * v.y - this->y * v.x;
}
*/

VSINLINE void VECTOR4::Lerp( const VECTOR4 &v, const float s ) const {
	//OWN: Lineare Interpolation von 2D-Vektoren
	D3DXVec4Lerp((D3DXVECTOR4*)this, (D3DXVECTOR4*)this, (D3DXVECTOR4*)&v, s);
}

VSINLINE VECTOR4 VECTOR4::GetLerped( const VECTOR4 &v, const float s ) const {
	VECTOR4 Vec4;
	D3DXVec4Lerp((D3DXVECTOR4*)&Vec4, (D3DXVECTOR4*)this, (D3DXVECTOR4*)&v, s);
	return Vec4;
}

VSINLINE void VECTOR4::Maximise( const VECTOR4 &v ) {
	if(v.x > this->x) this->x = v.x;
	if(v.y > this->y) this->y = v.y;
	if(v.z > this->z) this->z = v.z;
	if(v.w > this->w) this->w = v.w;
}

VSINLINE VECTOR4 VECTOR4::GetMaximised( const VECTOR4 &v ) const {
	VECTOR4 Vec4;
	Vec4.x = (v.x>Vec4.x)?v.x:this->x;
	Vec4.y = (v.y>Vec4.y)?v.y:this->y;
	Vec4.y = (v.z>Vec4.z)?v.z:this->z;
	Vec4.w = (v.w>Vec4.w)?v.w:this->w;
	return Vec4;
}

VSINLINE void VECTOR4::Minimise( const VECTOR4 &v ) {
	if(v.x < this->x) this->x = v.x;
	if(v.y < this->y) this->y = v.y;
	if(v.z < this->z) this->z = v.z;
	if(v.w < this->w) this->w = v.w;
}

VSINLINE VECTOR4 VECTOR4::GetMinimised( const VECTOR4 &v ) const {
	VECTOR4 Vec4;
	Vec4.x = (v.x>Vec4.x)?v.x:this->x;
	Vec4.y = (v.y<Vec4.y)?v.y:this->y;
	Vec4.y = (v.z<Vec4.z)?v.z:this->z;
	Vec4.w = (v.w<Vec4.w)?v.w:this->w;
	return Vec4;
}

VSINLINE void VECTOR4::Scale( const float s ) {
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
}

VSINLINE VECTOR4 VECTOR4::GetScaled( const float s ) const {
	return VECTOR4(x*s, y*s, z*s, w*s);
}

VSINLINE void VECTOR4::Add( const VECTOR4 &v ) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}

VSINLINE VECTOR4 VECTOR4::GetAdded( const VECTOR4 &v ) const {
	return VECTOR4(x+v.x, y+v.y, z+v.z, w+v.w);
}

VSINLINE void VECTOR4::Subtract( const VECTOR4 &v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

VSINLINE VECTOR4 VECTOR4::GetSubtracted( const VECTOR4 &v ) const {
	return VECTOR4(x-v.x, y-v.y, z-v.z, w-v.w);
}

VSINLINE void VECTOR4::Transform( const MATRIX4 &m ) {
	VECTOR4 Vec4;
	D3DXVec4Transform((D3DXVECTOR4*)this, (D3DXVECTOR4*)this, (D3DXMATRIX*)&m);
}

VSINLINE VECTOR4 VECTOR4::GetTransformed( const MATRIX4 &m ) const {
	VECTOR4 Vec4;
	D3DXVec4Transform((D3DXVECTOR4*)&Vec4, (D3DXVECTOR4*)this, (D3DXMATRIX*)&m);
	return VECTOR4(Vec4.x, Vec4.y, Vec4.z, Vec4.w);
}

VSINLINE void VECTOR4::BaryCentric( const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const float f, const float g ) {
	//OWN: Baryzentrische Koordinaten für Vektor4
	D3DXVec4BaryCentric((D3DXVECTOR4*)this, (D3DXVECTOR4*)&v1, (D3DXVECTOR4*)&v2, (D3DXVECTOR4*)&v3, f, g);
}

VSINLINE VECTOR4 VECTOR4::GetBaryCentric( const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const float f, const float g ) const {
	VECTOR4 Vec4;
	D3DXVec4BaryCentric((D3DXVECTOR4*)&Vec4, (D3DXVECTOR4*)&v1, (D3DXVECTOR4*)&v2, (D3DXVECTOR4*)&v3, f, g);
	return Vec4;
}

VSINLINE void VECTOR4::CatmullRom( const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const VECTOR4 &v4, const float s ) {
	//OWN: CatmullRom für Vektor4
	D3DXVec4CatmullRom((D3DXVECTOR4*)this, (D3DXVECTOR4*)&v1, (D3DXVECTOR4*)&v2, (D3DXVECTOR4*)&v3, (D3DXVECTOR4*)&v4, s);
}

VSINLINE VECTOR4 VECTOR4::GetCatmullRom( const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const VECTOR4 &v4, const float s ) const {
	VECTOR4 Vec4;
	D3DXVec4CatmullRom((D3DXVECTOR4*)&Vec4, (D3DXVECTOR4*)&v1, (D3DXVECTOR4*)&v2, (D3DXVECTOR4*)&v3, (D3DXVECTOR4*)&v4, s);
	return Vec4;
}

VSINLINE void VECTOR4::Hermite( const VECTOR4 &v1, const VECTOR4 &t1, const VECTOR4 &v2, const VECTOR4 &t2, const float s ) {
	//OWN: Hermite für Vektor4
	D3DXVec4Hermite((D3DXVECTOR4*)this, (D3DXVECTOR4*)&v1, (D3DXVECTOR4*)&t1, (D3DXVECTOR4*)&v2, (D3DXVECTOR4*)&t2, s);
}

VSINLINE VECTOR4 VECTOR4::GetHermite( const VECTOR4 &v1, const VECTOR4 &t1, const VECTOR4 &v2, const VECTOR4 &t2, const float s ) const {
	VECTOR4 Vec4;
	D3DXVec4Hermite((D3DXVECTOR4*)&Vec4, (D3DXVECTOR4*)&v1, (D3DXVECTOR4*)&t1, (D3DXVECTOR4*)&v2, (D3DXVECTOR4*)&t2, s);
	return Vec4;
}

VSINLINE VECTOR4& VECTOR4::operator *= ( const MATRIX4& a ) {
	this->Assign(
		this->x*a._11 + this->y*a._21 + this->z*a._31 + this->w*a._41,
		this->x*a._12 + this->y*a._22 + this->z*a._32 + this->w*a._42,
		this->x*a._13 + this->y*a._23 + this->z*a._33 + this->w*a._43,
		this->x*a._14 + this->y*a._24 + this->z*a._34 + this->w*a._44
	);
	return *this;
}