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

	Dateiname:		quaternion.inl.h
	Beschreibung:	Quaternion Inline-Funktionen
	Revision:		2
	Erstellt:		MMT, 07. Juli 2002 18:56

	Changelog:
	[2]		14. Juli 2002 22:05
			GetRotation() hinzugefügt
	[1]		07. Juli 2002 18:56

===========================================================================*/

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\fastmath\fastsqrt.h"
#include "quaternion.h"
#include "..\matrix\matrix4.h"
#include "..\vektoren\vector3.h"
#include "..\vektoren\vector3.inl.h"
#include "..\matrix\matrix4.inl.h"

#pragma intrinsic(memcpy)
#pragma intrinsic(memcmp)

//==================----------- Konstrukoren ------------------------------------


VSINLINE QUATERNION::QUATERNION( float X, float Y, float Z, float W ) {
	x = X; y = Y; z = Z; w = W;
}


VSINLINE QUATERNION::QUATERNION( const float* pf ) {
	/*
	x = pf[0];
	y = pf[1];
	z = pf[2];
	w = pf[3];
	*/
	memcpy(this, pf, sizeof(float)*4);
}


//==================----------- Casting ------------------------------------

VSINLINE QUATERNION::operator float* () {
	return (float *) &x;
}


VSINLINE QUATERNION::operator const float* () const {
	return (const float *) &x;
}


//==================----------- Zuweisung ------------------------------------

VSINLINE QUATERNION& QUATERNION::operator += ( const QUATERNION& q ) {
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;
	return *this;
}


VSINLINE QUATERNION& QUATERNION::operator -= ( const QUATERNION& q ) {
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;
	return *this;
}


VSINLINE QUATERNION& QUATERNION::operator *= ( const QUATERNION& q ) {
	//OWN: Eigene Multiplikation einbinden
	D3DXQuaternionMultiply((D3DXQUATERNION*)this, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&q);
	return *this;
}


VSINLINE QUATERNION& QUATERNION::operator *= ( float f ) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}


VSINLINE QUATERNION& QUATERNION::operator /= ( float f ) {
	float fInv = 1.0f / f;
	x *= fInv;
	y *= fInv;
	z *= fInv;
	w *= fInv;
	return *this;
}


//==================----------- Unär ------------------------------------

VSINLINE QUATERNION QUATERNION::operator + () const {
	return *this;
}


VSINLINE QUATERNION QUATERNION::operator - () const {
	return QUATERNION(-x, -y, -z, -w);
}


//==================----------- Binär ------------------------------------

VSINLINE QUATERNION QUATERNION::operator + ( const QUATERNION& q ) const {
	return QUATERNION(x + q.x, y + q.y, z + q.z, w + q.w);
}

VSINLINE QUATERNION QUATERNION::operator - ( const QUATERNION& q ) const {
	return QUATERNION(x - q.x, y - q.y, z - q.z, w - q.w);
}

VSINLINE QUATERNION QUATERNION::operator * ( const QUATERNION& q ) const {
	//OWN: Eigene Multiplikation
	QUATERNION qT;
	D3DXQuaternionMultiply((D3DXQUATERNION*)&qT, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&q);
	return qT;
}

VSINLINE QUATERNION QUATERNION::operator * ( float f ) const {
	return QUATERNION(x * f, y * f, z * f, w * f);
}

VSINLINE QUATERNION QUATERNION::operator / ( float f ) const {
	float fInv = 1.0f / f;
	return QUATERNION(x * fInv, y * fInv, z * fInv, w * fInv);
}

VSINLINE QUATERNION operator * (float f, const QUATERNION& q ) {
	return QUATERNION(f * q.x, f * q.y, f * q.z, f * q.w);
}

VSINLINE bool QUATERNION::operator == ( const QUATERNION& q ) const {
	return x == q.x && y == q.y && z == q.z && w == q.w;
}

VSINLINE bool QUATERNION::operator != ( const QUATERNION& q ) const {
	return x != q.x || y != q.y || z != q.z || w != q.w;
}


//==================----------- Kopieroperator --------------------------------------
VSINLINE const QUATERNION& QUATERNION::operator = (const QUATERNION& Quaternion) {
	memcpy(this, &Quaternion, sizeof(float)*4);
	return *this;
}

//==================----------- Memberfunktionen ------------------------------------

VSINLINE void QUATERNION::Assign( float X, float Y, float Z, float W ) {
	this->x = X;
	this->y = Y;
	this->z = Z;
	this->w = W;
}

VSINLINE void QUATERNION::Assign( QUATERNION *In ) {
	/*
	this->x = In->x;
	this->y = In->y;
	this->z = In->z;
	this->w = In->w;
	*/
	memcpy(this, In, sizeof(QUATERNION));
}

VSINLINE void QUATERNION::Negate() {
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
	this->w = -this->w;
}

VSINLINE QUATERNION QUATERNION::GetNegated() const {
	QUATERNION Quat(this->x, this->y, this->z, this->w);
	Quat.Negate();
	return Quat;
}

VSINLINE float QUATERNION::GetMag() const {
	return fastsqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

VSINLINE float QUATERNION::GetMagSquared() const {
	return this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;
}

VSINLINE float QUATERNION::GetLength() const {
	return fastsqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

VSINLINE float QUATERNION::GetLengthSquared() const {
	return this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;
}

VSINLINE void QUATERNION::Normalize() {
	D3DXQuaternionNormalize((D3DXQUATERNION*)this, (D3DXQUATERNION*)this);
}

VSINLINE QUATERNION QUATERNION::GetNormalized() const {
	QUATERNION Quat;
	D3DXQuaternionNormalize((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)this);
	return Quat;
}

VSINLINE float QUATERNION::GetDistance( const QUATERNION& v ) const {
	return (*this - v).GetMag();
}


//==================----------- Erweiterte Memberfunktionen ------------------------------------

VSINLINE void QUATERNION::Conjugate() const {
	D3DXQuaternionConjugate((D3DXQUATERNION*)this, (D3DXQUATERNION*)this);
}

VSINLINE QUATERNION QUATERNION::GetConjugated() const {
	QUATERNION Quat;
	D3DXQuaternionConjugate((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)this);
	return Quat;
}

VSINLINE void QUATERNION::Exponential() const {
	D3DXQuaternionExp((D3DXQUATERNION*)this, (D3DXQUATERNION*)this);
}

VSINLINE QUATERNION QUATERNION::GetExponential() const {
	QUATERNION Quat;
	D3DXQuaternionExp((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)this);
	return Quat;
}

VSINLINE void QUATERNION::Identity() {
	this->x = 0.f;
	this->y = 0.f;
	this->z = 0.f;
	this->w = 1.f;
}

VSINLINE QUATERNION QUATERNION::GetIdentity() const {
	return QUATERNION(0.f, 0.f, 0.f, 1.f);
}

VSINLINE void QUATERNION::Inverse() const {
	D3DXQuaternionInverse((D3DXQUATERNION*)this, (D3DXQUATERNION*)this);
}

VSINLINE QUATERNION QUATERNION::GetInversed() const {
	QUATERNION Quat;
	D3DXQuaternionInverse((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)this);
	return Quat;
}

VSINLINE BOOL QUATERNION::IsIdentity() const {
	return (BOOL)(this->x == 0 && this->y == 0 && this->z == 0 && this->w == 1);
}

VSINLINE void QUATERNION::Ln() const {
	D3DXQuaternionLn((D3DXQUATERNION*)this, (D3DXQUATERNION*)this);
}

VSINLINE QUATERNION QUATERNION::GetLn() const {
	QUATERNION Quat;
	D3DXQuaternionLn((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)this);
	return Quat;
}

VSINLINE float QUATERNION::Dot(const QUATERNION& v) const {
	return D3DXQuaternionDot((D3DXQUATERNION*)this, (D3DXQUATERNION*)&v);
}

VSINLINE void QUATERNION::Multiply(const QUATERNION& v) {
	D3DXQuaternionMultiply((D3DXQUATERNION*)this, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&v);
}

VSINLINE QUATERNION QUATERNION::GetMultiplied(const QUATERNION& v) const {
	QUATERNION Quat;
	D3DXQuaternionMultiply((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&v);
	return Quat;
}

VSINLINE void QUATERNION::Rotate(const VECTOR3& v, const float angle) {
	D3DXQuaternionRotationAxis((D3DXQUATERNION*)this, (D3DXVECTOR3*)&v, angle);
}

VSINLINE QUATERNION QUATERNION::GetRotated(const VECTOR3& v, const float angle) {
	QUATERNION Quat;
	D3DXQuaternionRotationAxis((D3DXQUATERNION*)&Quat, (D3DXVECTOR3*)&v, angle);
	return Quat;
}

VSINLINE void QUATERNION::Rotate(const MATRIX4& m) {
	D3DXQuaternionRotationMatrix((D3DXQUATERNION*)this, (D3DXMATRIX*)&m);
}

VSINLINE QUATERNION QUATERNION::GetRotated(const MATRIX4& m) const {
	QUATERNION Quat;
	D3DXQuaternionRotationMatrix((D3DXQUATERNION*)&Quat, (D3DXMATRIX*)&m);
	return Quat;
}

VSINLINE void QUATERNION::Rotate(const float x, const float y, const float z) {
	D3DXQuaternionRotationYawPitchRoll((D3DXQUATERNION*)this, x, y, z);
}

VSINLINE QUATERNION QUATERNION::GetRotated(const float x, const float y, const float z) const {
	QUATERNION Quat;
	D3DXQuaternionRotationYawPitchRoll((D3DXQUATERNION*)&Quat, y /*yaw*/, x /*pitch*/, z /*roll*/);
	return Quat;
}

VSINLINE void QUATERNION::GetRotationAxisAngle(VECTOR3 *axis, float* angle) const {
	D3DXQuaternionToAxisAngle((D3DXQUATERNION*)this, (D3DXVECTOR3*)&axis, angle);
}

VSINLINE void QUATERNION::Slerp(const QUATERNION& v, const float s) {
	D3DXQuaternionSlerp((D3DXQUATERNION*)this, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&v, s);
}

VSINLINE QUATERNION QUATERNION::GetSlerped(const QUATERNION& v, const float s) const {
	QUATERNION Quat;
	D3DXQuaternionSlerp((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&v, s);
	return Quat;
}

VSINLINE void QUATERNION::Squad(const QUATERNION& Q1, const QUATERNION& A, const QUATERNION& B, const QUATERNION& C, const float t) {
	D3DXQuaternionSquad((D3DXQUATERNION*)this, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&A, (D3DXQUATERNION*)&B, (D3DXQUATERNION*)&C, t);
}

VSINLINE QUATERNION QUATERNION::GetSquaded(const QUATERNION& Q1, const QUATERNION& A, const QUATERNION& B, const QUATERNION& C, const float t) const {
	QUATERNION Quat;
	D3DXQuaternionSquad((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&A, (D3DXQUATERNION*)&B, (D3DXQUATERNION*)&C, t);
	return Quat;
}

VSINLINE void QUATERNION::GetSquadSetup(const QUATERNION* outA, const QUATERNION* outB, const QUATERNION* outC, const QUATERNION& Q0, const QUATERNION& Q1, const QUATERNION& Q2, const QUATERNION& Q3) const {
	D3DXQuaternionSquadSetup((D3DXQUATERNION*)&outA, (D3DXQUATERNION*)&outB, (D3DXQUATERNION*)&outC, (D3DXQUATERNION*)&Q0, (D3DXQUATERNION*)&Q1, (D3DXQUATERNION*)&Q2, (D3DXQUATERNION*)&Q3);
}

VSINLINE void QUATERNION::BaryCentric(const QUATERNION& v1, const QUATERNION& v2, const QUATERNION& v3, const float f, const float g) {
	D3DXQuaternionBaryCentric((D3DXQUATERNION*)this, (D3DXQUATERNION*)&v1, (D3DXQUATERNION*)&v2, (D3DXQUATERNION*)&v3, f, g);
}

VSINLINE QUATERNION QUATERNION::GetBaryCentric(const QUATERNION& v1, const QUATERNION& v2, const QUATERNION& v3, const float f, const float g) const {
	QUATERNION Quat;
	D3DXQuaternionBaryCentric((D3DXQUATERNION*)&Quat, (D3DXQUATERNION*)&v1, (D3DXQUATERNION*)&v2, (D3DXQUATERNION*)&v3, f, g);
	return Quat;
}


VSINLINE void QUATERNION::GetRotation(VECTOR3* vRotation) const{
	MATRIX4 mat;
	this->ToMatrix(&mat);
	vRotation->x = fastasin( -mat._32 );
	vRotation->y = fastasin(  mat._31 );
	vRotation->z = fastasin(  mat._12 );
}

VSINLINE void QUATERNION::GetRotation(float& fX, float& fY, float& fZ) const{
	MATRIX4 mat;
	this->ToMatrix(&mat);
	fX = fastasin( -mat._32 );
	fY = fastasin(  mat._31 );
	fZ = fastasin(  mat._12 );
}