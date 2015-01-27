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

	Dateiname:		vector3.inl.h
	Beschreibung:	3D-Vektor Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 16:09

	Changelog:
	[1]		05. Juli 2002 16:09
			Verwendung von intrinsischen memcpys und memcmps

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "vector3.h"
#include "vector2.h"
#include "vector4.h"
#include "..\matrix\matrix4.h"
#include "..\fastmath\fastsqrt.h"

#pragma intrinsic(memcpy)
#pragma intrinsic(memcmp)

//:: Die Konstruktoren :::::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR3::VECTOR3() {
}

VSINLINE VECTOR3::VECTOR3(const VECTOR3 &inVec) :
	x( inVec.x ), y( inVec.y ), z( inVec.z ) {
}

VSINLINE VECTOR3::VECTOR3(const VECTOR3 *inVec) :
	x( inVec->x ), y( inVec->y ), z( inVec->z ) {
}

VSINLINE VECTOR3::VECTOR3(const float inx, const float iny, const float inz) :
	x( inx ), y( iny ), z( inz ) {
}

VSINLINE VECTOR3::VECTOR3(const float *inv) :
	x( inv[0] ), y( inv[1] ), z( inv[2] ) {
}

VSINLINE VECTOR3::VECTOR3(const VECTOR2 &inVec) :
	x( inVec.x ), y( inVec.y ), z( 0.f ) {
}

VSINLINE VECTOR3::VECTOR3(const VECTOR2 *inVec) :
	x( inVec->x ), y( inVec->y ), z( 0.f ) {
}

VSINLINE VECTOR3::VECTOR3(const D3DXVECTOR3 &inVec) :
	x( inVec.x ), y( inVec.y ), z( inVec.z ) {
}

VSINLINE VECTOR3::VECTOR3(const D3DXVECTOR3 *inVec) :
	x( inVec->x ), y( inVec->y ), z( inVec->z ) {
}

//:: Operatoren: Casting ::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR3::operator float* () const {
	return (float *) &this->x;
}

VSINLINE VECTOR3::operator const float* () const {
	return (const float *) &this->x;
}

VSINLINE VECTOR3::operator D3DXVECTOR3 () const {
	return D3DXVECTOR3(this->x, this->y, this->z);
}

VSINLINE VECTOR3::operator const D3DXVECTOR3 () const {
	return (const D3DXVECTOR3) D3DXVECTOR3(this->x, this->y, this->z);
}

VSINLINE VECTOR3::operator VECTOR2 () const {
	return VECTOR2(this->x, this->y);
}

VSINLINE VECTOR3::operator const VECTOR2 () const {
	return (const VECTOR2) VECTOR2(this->x, this->y);
}

VSINLINE VECTOR3::operator VECTOR4 () const {
	return VECTOR4(this->x, this->y, this->z, 0.f);
}

VSINLINE VECTOR3::operator const VECTOR4 () const {
	return (const VECTOR4) VECTOR4(this->x, this->y, this->z, 0.f);
}

//:: Operatoren: Casting ::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR3& VECTOR3::operator += ( const VECTOR3 &v ) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

VSINLINE VECTOR3& VECTOR3::operator += ( const D3DXVECTOR3 &v ) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

VSINLINE VECTOR3& VECTOR3::operator -= ( const VECTOR3 &v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

VSINLINE VECTOR3& VECTOR3::operator -= ( const D3DXVECTOR3 &v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

VSINLINE VECTOR3& VECTOR3::operator *= ( float f ) {
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

VSINLINE VECTOR3& VECTOR3::operator /= ( float f ) {
	float inv_f = 1.f/f;
	x *= inv_f;
	y *= inv_f;
	z *= inv_f;
	return *this;
}

VSINLINE VECTOR3& VECTOR3::operator = ( const VECTOR3 &v ) {
	/*
	x = v.x;
	y = v.y;
	z = v.z;
	*/
	memcpy(this, &v, sizeof(float)*3);
	return *this;
}

VSINLINE VECTOR3& VECTOR3::operator = ( const D3DXVECTOR3 &v ) {
	/*
	x = v.x;
	y = v.y;
	z = v.z;
	*/
	memcpy(this, &v, sizeof(float)*3);
	return *this;
}

//:: Operatoren: Unär ::::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR3 VECTOR3::operator + () const {
	return VECTOR3(x, y, z);
}

VSINLINE VECTOR3 VECTOR3::operator - () const {
	return VECTOR3(-x, -y, -z);
}

//:: Operatoren: Binär :::::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE VECTOR3 VECTOR3::operator + ( const VECTOR3& v ) const {
	return VECTOR3(x + v.x, y + v.y, z + v.z);
}

VSINLINE VECTOR3 VECTOR3::operator + ( const D3DXVECTOR3& v ) const {
	return VECTOR3(x + v.x, y + v.y, z + v.z);
}

VSINLINE VECTOR3 VECTOR3::operator - ( const VECTOR3& v ) const {
	return VECTOR3(x - v.x, y - v.y, z - v.z);
}

VSINLINE VECTOR3 VECTOR3::operator - ( const D3DXVECTOR3& v ) const {
	return VECTOR3(x - v.x, y - v.y, z - v.z);
}

VSINLINE VECTOR3 VECTOR3::operator * ( float f ) const {
	return VECTOR3(x * f, y * f, z * f);
}

VSINLINE float VECTOR3::operator DOT ( const VECTOR3 &v ) const {
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

VSINLINE float VECTOR3::operator DOT ( const D3DXVECTOR3 &v ) const {
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

VSINLINE VECTOR3 VECTOR3::operator CROSS ( const VECTOR3 &b) const {
	return VECTOR3(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
}

VSINLINE VECTOR3 VECTOR3::operator CROSS ( const D3DXVECTOR3 &b) const {
	return VECTOR3(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
}

VSINLINE VECTOR3 VECTOR3::operator / ( float f ) const {
	float fInv = 1.0f / f;
	return VECTOR3(x * fInv, y * fInv, z * fInv);
}

VSINLINE VECTOR3 operator * ( float f, const VECTOR3& v ) {
	return VECTOR3(f * v.x, f * v.y, f * v.z);
}

//:: Operatoren: Vergleich :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE bool VECTOR3::operator == ( const VECTOR3& v ) const {
	//return (x == v.x) && (y == v.y) && (z == v.z);
	return (memcmp(*this, &v, sizeof(float)*3)==0)?true:false;
}

VSINLINE bool VECTOR3::operator == ( const D3DXVECTOR3& v ) const {
	//return (x == v.x) && (y == v.y) && (z == v.z);
	return (memcmp(*this, &v, sizeof(float)*3)==0)?true:false;
}

VSINLINE bool VECTOR3::operator != ( const VECTOR3& v ) const {
	//return (x != v.x) || (y != v.y) || (z != v.z);
	return (memcmp(*this, &v, sizeof(float)*3)!=0)?true:false;
}

VSINLINE bool VECTOR3::operator != ( const D3DXVECTOR3& v ) const {
	//return (x != v.x) || (y != v.y) || (z != v.z);
	return (memcmp(*this, &v, sizeof(float)*3)!=0)?true:false;
}

//:: Operatoren: Vergleich :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE void VECTOR3::Assign( const float inx, const float iny, const float inz ) {
	x = inx;
	y = iny;
	z = inz;
}

VSINLINE void VECTOR3::Assign( const float *inv ) {
	/*
	x = inv[0];
	y = inv[1];
	z = inv[2];
	*/
	memcpy(this, inv, sizeof(float)*3);
}

VSINLINE void VECTOR3::Assign( const VECTOR3 &inVec ) {
	/*
	x = inVec.x;
	y = inVec.y;
	z = inVec.z;
	*/
	memcpy(this, &inVec, sizeof(float)*3);
}

VSINLINE void VECTOR3::Assign( const VECTOR3 *inVec ) {
	/*
	x = inVec->x;
	y = inVec->y;
	z = inVec->z;
	*/
	memcpy(this, inVec, sizeof(float)*3);
}

VSINLINE void VECTOR3::Assign( const D3DXVECTOR3 &inVec ) {
	/*
	x = inVec.x;
	y = inVec.y;
	z = inVec.z;
	*/
	memcpy(this, &inVec, sizeof(float)*3);
}

VSINLINE void VECTOR3::Assign( const D3DXVECTOR3 *inVec ) {
	/*
	x = inVec->x;
	y = inVec->y;
	z = inVec->z;
	*/
	memcpy(this, inVec, sizeof(float)*3);
}

VSINLINE void VECTOR3::Assign( const VECTOR2 &inVec ) {
	/*
	x = inVec.x;
	y = inVec.y;
	*/
	z = 0.f;
	memcpy(this, &inVec, sizeof(float)*2);
}

VSINLINE void VECTOR3::Assign( const VECTOR2 *inVec ) {
	/*
	x = inVec->x;
	y = inVec->y;
	*/
	z = 0.f;
	memcpy(this, inVec, sizeof(float)*2);
}

VSINLINE void VECTOR3::Assign( const VECTOR4 &inVec ) {
	/*
	x = inVec.x;
	y = inVec.y;
	z = inVec.z;
	*/
	memcpy(this, &inVec, sizeof(float)*3);
}

VSINLINE void VECTOR3::Assign( const VECTOR4 *inVec ) {
	/*
	x = inVec->x;
	y = inVec->y;
	z = inVec->z;
	*/
	memcpy(this, inVec, sizeof(float)*3);
}

//:: Operatoren: Einfach :::::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE void VECTOR3::Negate() {
	x = -x;
	y = -y;
	z = -z;
}

VSINLINE VECTOR3 VECTOR3::GetNegated() const {
	return VECTOR3( -x, -y, -z );
}

VSINLINE float VECTOR3::GetMag() const {
	return fastsqrt( x*x + y*y + z*z );
}

VSINLINE float VECTOR3::GetMagSquared() const {
	return (float)( x*x + y*y + z*z );
}

VSINLINE float VECTOR3::GetLength() const {
	return fastsqrt( x*x + y*y + z*z );
}

VSINLINE float VECTOR3::GetLengthSquared() const {
	return (float)( x*x + y*y + z*z );
}

VSINLINE void VECTOR3::Normalize() {
	float foo=1/GetMag();	
	x*=foo;
	y*=foo;
	z*=foo;
}

VSINLINE VECTOR3 VECTOR3::GetNormalized() const {
	VECTOR3 Vec3(*this);
	Vec3.Normalize();
	return Vec3;
}

//:: Operatoren: Erweitert :::::::::::::::::::::::::::::::::::::::::::::::

VSINLINE float VECTOR3::GetDistance( const VECTOR3 &v ) const {
	VECTOR3 Vec3(this->x-v.x, this->y-v.y, this->z - v.z);
	return Vec3.GetMag();
}

VSINLINE float VECTOR3::GetDistance( const D3DXVECTOR3 &v ) const {
	VECTOR3 Vec3(this->x-v.x, this->y-v.y, this->z - v.z);
	return Vec3.GetMag();
}

VSINLINE float VECTOR3::Dot( const VECTOR3 &v ) const {
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

VSINLINE float VECTOR3::Dot( const D3DXVECTOR3 &v ) const {
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

VSINLINE VECTOR3 VECTOR3::Cross(const VECTOR3& v) const {
	return VECTOR3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}

VSINLINE void VECTOR3::ToCross(const VECTOR3& v) {
	this->x		= this->y * v.z - this->z * v.y;
	this->y		= this->z * v.x - this->x * v.z;
	this->z		= this->x * v.y - this->y * v.x;
}

VSINLINE VECTOR3 VECTOR3::Cross(const D3DXVECTOR3& v) const {
	return VECTOR3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}

VSINLINE void VECTOR3::ToCross(const D3DXVECTOR3& v) {
	this->x		= this->y * v.z - this->z * v.y;
	this->y		= this->z * v.x - this->x * v.z;
	this->z		= this->x * v.y - this->y * v.x;
}

VSINLINE void VECTOR3::Lerp( const VECTOR3 &v, const float s ) const {
	//OWN: Lineare Interpolation von 2D-Vektoren
	D3DXVec3Lerp((D3DXVECTOR3*)this, (D3DXVECTOR3*)this, (D3DXVECTOR3*)&v, s);
}

VSINLINE VECTOR3 VECTOR3::GetLerped( const VECTOR3 &v, const float s ) const {
	VECTOR3 Vec3;
	D3DXVec3Lerp((D3DXVECTOR3*)&Vec3, (D3DXVECTOR3*)this, (D3DXVECTOR3*)&v, s);
	return Vec3;
}

VSINLINE void VECTOR3::Maximise( const VECTOR3 &v ) {
	if(v.x > this->x) this->x = v.x;
	if(v.y > this->y) this->y = v.y;
	if(v.z > this->z) this->z = v.z;
}

VSINLINE VECTOR3 VECTOR3::GetMaximised( const VECTOR3 &v ) const {
	VECTOR3 Vec3;
	Vec3.x = (v.x>Vec3.x)?v.x:this->x;
	Vec3.y = (v.y>Vec3.y)?v.y:this->y;
	Vec3.y = (v.z>Vec3.z)?v.z:this->z;
	return Vec3;
}

VSINLINE void VECTOR3::Minimise( const VECTOR3 &v ) {
	if(v.x < this->x) this->x = v.x;
	if(v.y < this->y) this->y = v.y;
	if(v.z < this->z) this->z = v.z;
}

VSINLINE VECTOR3 VECTOR3::GetMinimised( const VECTOR3 &v ) const {
	VECTOR3 Vec3;
	Vec3.x = (v.x>Vec3.x)?v.x:this->x;
	Vec3.y = (v.y<Vec3.y)?v.y:this->y;
	Vec3.y = (v.z<Vec3.z)?v.z:this->z;
	return Vec3;
}

VSINLINE void VECTOR3::Scale( const float s ) {
	this->x *= s;
	this->y *= s;
	this->z *= s;
}

VSINLINE VECTOR3 VECTOR3::GetScaled( const float s ) const {
	return VECTOR3(x*s, y*s, z*s);
}

VSINLINE void VECTOR3::Add( const VECTOR3 &v ) {
	x += v.x;
	y += v.y;
	z += v.z;
}

VSINLINE VECTOR3 VECTOR3::GetAdded( const VECTOR3 &v ) const {
	return VECTOR3(x+v.x, y+v.y, z+v.z);
}

VSINLINE void VECTOR3::Subtract( const VECTOR3 &v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

VSINLINE VECTOR3 VECTOR3::GetSubtracted( const VECTOR3 &v ) const {
	return VECTOR3(x-v.x, y-v.y, z-v.z);
}

VSINLINE void VECTOR3::Transform( const MATRIX4 &m ) {
	VECTOR4 Vec4;
	D3DXVec3Transform((D3DXVECTOR4*)&Vec4, (D3DXVECTOR3*)this, (D3DXMATRIX*)&m);
	this->x = Vec4.x;
	this->y = Vec4.y;
	this->z = Vec4.z;
}

VSINLINE VECTOR3 VECTOR3::GetTransformed( const MATRIX4 &m ) const {
	VECTOR3 Vec4;
	D3DXVec3Transform((D3DXVECTOR4*)&Vec4, (D3DXVECTOR3*)this, (D3DXMATRIX*)&m);
	return VECTOR3(Vec4.x, Vec4.y, Vec4.z);
}

VSINLINE void VECTOR3::TransformCoord( const MATRIX4 &m ) {
	D3DXVec3TransformCoord((D3DXVECTOR3*)this, (D3DXVECTOR3*)this, (D3DXMATRIX*)&m);
}

VSINLINE VECTOR3 VECTOR3::GetTransformCoord( const MATRIX4 &m ) const {
	VECTOR3 Vec3;
	D3DXVec3TransformCoord((D3DXVECTOR3*)&Vec3, &((D3DXVECTOR3)*this), (D3DXMATRIX*)&m);
	return Vec3;
}

VSINLINE void VECTOR3::TransformNormal( const MATRIX4 &m ) {
	D3DXVec3TransformNormal((D3DXVECTOR3*)this, &((D3DXVECTOR3)*this), (D3DXMATRIX*)&m);
}

VSINLINE VECTOR3 VECTOR3::GetTransformNormal( const MATRIX4 &m ) const {
	VECTOR3 Vec3;
	D3DXVec3TransformNormal((D3DXVECTOR3*)&Vec3, &((D3DXVECTOR3)*this), (D3DXMATRIX*)&m);
	return Vec3;
}

VSINLINE void VECTOR3::BaryCentric( const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &v3, const float f, const float g ) {
	//OWN: Baryzentrische Koordinaten für Vektor3
	D3DXVec3BaryCentric((D3DXVECTOR3*)this, (D3DXVECTOR3*)&v1, (D3DXVECTOR3*)&v2, (D3DXVECTOR3*)&v3, f, g);
}

VSINLINE VECTOR3 VECTOR3::GetBaryCentric( const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &v3, const float f, const float g ) const {
	VECTOR3 Vec3;
	D3DXVec3BaryCentric((D3DXVECTOR3*)&Vec3, (D3DXVECTOR3*)&v1, (D3DXVECTOR3*)&v2, (D3DXVECTOR3*)&v3, f, g);
	return Vec3;
}

VSINLINE void VECTOR3::CatmullRom( const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &v3, const VECTOR3 &v4, const float s ) {
	//OWN: CatmullRom für Vektor3
	D3DXVec3CatmullRom((D3DXVECTOR3*)this, (D3DXVECTOR3*)&v1, (D3DXVECTOR3*)&v2, (D3DXVECTOR3*)&v3, (D3DXVECTOR3*)&v4, s);
}

VSINLINE VECTOR3 VECTOR3::GetCatmullRom( const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &v3, const VECTOR3 &v4, const float s ) const {
	VECTOR3 Vec3;
	D3DXVec3CatmullRom((D3DXVECTOR3*)&Vec3, (D3DXVECTOR3*)&v1, (D3DXVECTOR3*)&v2, (D3DXVECTOR3*)&v3, (D3DXVECTOR3*)&v4, s);
	return Vec3;
}

VSINLINE void VECTOR3::Hermite( const VECTOR3 &v1, const VECTOR3 &t1, const VECTOR3 &v2, const VECTOR3 &t2, const float s ) {
	//OWN: Hermite für Vektor3
	D3DXVec3Hermite((D3DXVECTOR3*)this, (D3DXVECTOR3*)&v1, (D3DXVECTOR3*)&t1, (D3DXVECTOR3*)&v2, (D3DXVECTOR3*)&t2, s);
}

VSINLINE VECTOR3 VECTOR3::GetHermite( const VECTOR3 &v1, const VECTOR3 &t1, const VECTOR3 &v2, const VECTOR3 &t2, const float s ) const {
	VECTOR3 Vec3;
	D3DXVec3Hermite((D3DXVECTOR3*)&Vec3, (D3DXVECTOR3*)&v1, (D3DXVECTOR3*)&t1, (D3DXVECTOR3*)&v2, (D3DXVECTOR3*)&t2, s);
	return Vec3;
}

VSINLINE VECTOR3::VECTOR3( const VECTOR4& in ) {
	if( in.w != 1.f ) {
		float inv = 1/in.w;
		x = in.x * inv;
		y = in.y * inv;
		z = in.z * inv;
	} else {
		x = in.x;
		y = in.y;
		z = in.z;
	}
}

VSINLINE VECTOR3::VECTOR3( const VECTOR4* in ) {
	if( in->w != 1.f ) {
		float inv = 1/in->w;
		x = in->x * inv;
		y = in->y * inv;
		z = in->z * inv;
	} else {
		x = in->x;
		y = in->y;
		z = in->z;
	}
}

VSINLINE VECTOR3& VECTOR3::operator *= ( const MATRIX4& m ) {
	this->Assign(
		this->x*m._11 + this->y*m._21 + this->z*m._31 + m._41,
		this->x*m._12 + this->y*m._22 + this->z*m._32 + m._42,
		this->x*m._13 + this->y*m._23 + this->z*m._33 + m._43
	);
	return *this;
}