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

Dateiname:		matrix4.inl.h
Beschreibung:	4D-Matrix Inline-Funktionen
Revision:		1
Erstellt:		MMT, 05. Juli 2002 18:55

Changelog:
[1]		05. Juli 2002 18:55

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "matrix4.h"
#include "..\vektoren\vector3.h"
#include "..\vektoren\vector4.h"
#include "..\quaternion\quaternion.h"
#include "..\fastmath\fastassort.h"
#include "..\fastmath\fastfabs.h"
#include "..\fastmath\fasttrig.h"
#include "..\fastmath\fastsqrt.h"
#include "..\plane\plane.h"

#pragma intrinsic(memcpy)
#pragma intrinsic(memcmp)

//==========--------------------------  MATRIX4 operators


/**
* Specialization for multiplication by a VECTOR3 structure.
* in a mathematically perfect world, we would construct
* a 1x4 matrix for the point, and then multiply the 1x4
* and the 4x4 matrices toegether.  However, this performs
* much better.
*/
VSINLINE const VECTOR3 operator*( const MATRIX4 &a, const VECTOR3 &b) {
	return VECTOR3(
		b.x*a._11 + b.y*a._21 + b.z*a._31 + a._41,
		b.x*a._12 + b.y*a._22 + b.z*a._32 + a._42,
		b.x*a._13 + b.y*a._23 + b.z*a._33 + a._43
	);
};


VSINLINE const VECTOR3 operator*( const VECTOR3 &a, const MATRIX4 &b) {
	return b*a;
};


/**
* Specialization for multiplication by a VECTOR4 structure.
*/
VSINLINE const VECTOR4 operator*( const MATRIX4 &a, const VECTOR4 &b) {
	return VECTOR4(
		b.x*a._11 + b.y*a._21 + b.z*a._31 + b.w*a._41,
		b.x*a._12 + b.y*a._22 + b.z*a._32 + b.w*a._42,
		b.x*a._13 + b.y*a._23 + b.z*a._33 + b.w*a._43,
		b.x*a._14 + b.y*a._24 + b.z*a._34 + b.w*a._44
	);
};


VSINLINE const VECTOR4 operator*( const VECTOR4 &a, const MATRIX4 &b) {
	return b*a;
};

#ifdef LINESEG_DEFINED
//returns MATRIX4*LINESEG
VSINLINE LINESEG operator*( LINESEG const &b, MATRIX4 const &a ) {
	return LINESEG( b.v0 * a, b.v1 * a );
};


//returns MATRIX4*LINESEG
VSINLINE LINESEG operator*( MATRIX4 const &a, LINESEG const &b ) {
	return LINESEG( b.v0 * a, b.v1 * a );
};
#endif



// **************************************************************************************

VSINLINE MATRIX4::MATRIX4(const MATRIX4 &inMat) {
	memcpy(this, &inMat, sizeof(MATRIX4));
}

VSINLINE MATRIX4::MATRIX4(const MATRIX4 *inMat) {
	memcpy(this, inMat, sizeof(MATRIX4));
}

VSINLINE MATRIX4::MATRIX4( const float* pf ) {
	memcpy(this, pf, sizeof(MATRIX4));
}


VSINLINE MATRIX4::MATRIX4( const D3DXMATRIX& inMat ) {
	memcpy(this, &inMat, sizeof(D3DXMATRIX));
}

VSINLINE MATRIX4::MATRIX4( float f11, float f12, float f13, float f14,
							float f21, float f22, float f23, float f24,
							float f31, float f32, float f33, float f34,
							float f41, float f42, float f43, float f44 ) {
	_11 = f11; _12 = f12; _13 = f13; _14 = f14;
	_21 = f21; _22 = f22; _23 = f23; _24 = f24;
	_31 = f31; _32 = f32; _33 = f33; _34 = f34;
	_41 = f41; _42 = f42; _43 = f43; _44 = f44;
}



// access grants
VSINLINE float& MATRIX4::operator () ( UINT iRow, UINT iCol ) {
	return m[iRow][iCol];
}

VSINLINE float MATRIX4::operator () ( UINT iRow, UINT iCol ) const {
	return m[iRow][iCol];
}


// casting operators
VSINLINE MATRIX4::operator float* () {
	return (float *) &_11;
}

VSINLINE MATRIX4::operator const float* () const {
	return (const float *) &_11;
}

/*VSINLINE MATRIX4::operator D3DXMATRIX () {
	return (D3DXMATRIX)*this;
}*/

VSINLINE MATRIX4::operator D3DXMATRIX* () {
	return (D3DXMATRIX*)this;
}

VSINLINE MATRIX4::operator const D3DXMATRIX* () const {
	return (D3DXMATRIX*)this;
}

VSINLINE MATRIX4::operator D3DXMATRIX& () {
	return (D3DXMATRIX&)*this;
}

VSINLINE MATRIX4::operator const D3DXMATRIX& () const {
	return (D3DXMATRIX&)*this;
}

// assignment operators
VSINLINE MATRIX4& MATRIX4::operator *= ( const MATRIX4& mat ) {
	D3DXMatrixMultiply((D3DXMATRIX*)this, (D3DXMATRIX*)this, (D3DXMATRIX*)&mat);
	return *this;
}

VSINLINE MATRIX4& MATRIX4::operator += ( const MATRIX4& mat ) {
	_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
	_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
	_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
	_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
	return *this;
}

VSINLINE MATRIX4& MATRIX4::operator -= ( const MATRIX4& mat ) {
	_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
	_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
	_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
	_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
	return *this;
}


VSINLINE MATRIX4& MATRIX4::operator *= ( float f ) {
	_11 *= f; _12 *= f; _13 *= f; _14 *= f;
	_21 *= f; _22 *= f; _23 *= f; _24 *= f;
	_31 *= f; _32 *= f; _33 *= f; _34 *= f;
	_41 *= f; _42 *= f; _43 *= f; _44 *= f;
	return *this;
}


VSINLINE MATRIX4& MATRIX4::operator /= ( float f ) {
	float fInv = 1.0f / f;
	_11 *= fInv; _12 *= fInv; _13 *= fInv; _14 *= fInv;
	_21 *= fInv; _22 *= fInv; _23 *= fInv; _24 *= fInv;
	_31 *= fInv; _32 *= fInv; _33 *= fInv; _34 *= fInv;
	_41 *= fInv; _42 *= fInv; _43 *= fInv; _44 *= fInv;
	return *this;
}

// unary operators
VSINLINE MATRIX4 MATRIX4::operator + () const {
	return *this;
}

VSINLINE MATRIX4 MATRIX4::operator - () const {
	return MATRIX4(-_11, -_12, -_13, -_14,
					-_21, -_22, -_23, -_24,
					-_31, -_32, -_33, -_34,
					-_41, -_42, -_43, -_44);
}


// binary operators
VSINLINE MATRIX4 MATRIX4::operator * ( const MATRIX4& mat ) const {
	MATRIX4 matT;
	D3DXMatrixMultiply((D3DXMATRIX*)&matT, (D3DXMATRIX*)this, (D3DXMATRIX*)&mat);
	return matT;
}

VSINLINE MATRIX4 MATRIX4::operator + ( const MATRIX4& mat ) const {
	return MATRIX4(_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
					_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
					_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
					_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
}

VSINLINE MATRIX4 MATRIX4::operator - ( const MATRIX4& mat ) const {
	return MATRIX4(_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
					_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
					_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
					_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
}

VSINLINE MATRIX4 MATRIX4::operator * ( float f ) const {
	return MATRIX4(_11 * f, _12 * f, _13 * f, _14 * f,
					_21 * f, _22 * f, _23 * f, _24 * f,
					_31 * f, _32 * f, _33 * f, _34 * f,
					_41 * f, _42 * f, _43 * f, _44 * f);
}

VSINLINE MATRIX4 MATRIX4::operator / ( float f ) const {
	float fInv = 1.0f / f;
	return MATRIX4(_11 * fInv, _12 * fInv, _13 * fInv, _14 * fInv,
					_21 * fInv, _22 * fInv, _23 * fInv, _24 * fInv,
					_31 * fInv, _32 * fInv, _33 * fInv, _34 * fInv,
					_41 * fInv, _42 * fInv, _43 * fInv, _44 * fInv);
}


VSINLINE MATRIX4 operator * ( float f, const MATRIX4& mat ) {
	return MATRIX4(f * mat._11, f * mat._12, f * mat._13, f * mat._14,
					f * mat._21, f * mat._22, f * mat._23, f * mat._24,
					f * mat._31, f * mat._32, f * mat._33, f * mat._34,
					f * mat._41, f * mat._42, f * mat._43, f * mat._44);
}

/*
//Berechnet das Punktprodukt MATRIX4*MATRIX4
VSINLINE MATRIX4 operator * ( MATRIX4 const &a, MATRIX4 const &b ) {
	MATRIX4 ret;
	D3DXMatrixMultiply(&ret, &a, &b);
	return ret;
}
*/


VSINLINE bool MATRIX4::operator == ( const MATRIX4& mat ) const {
	return 0 == memcmp(this, &mat, sizeof(MATRIX4));
}

VSINLINE bool MATRIX4::operator != ( const MATRIX4& mat ) const {
	return 0 != memcmp(this, &mat, sizeof(MATRIX4));
}

//==========--------------------------  

VSINLINE void MATRIX4::ToZero() {
	memset(this, 0, sizeof(D3DXMATRIX));
}

VSINLINE void MATRIX4::Projection(const float fFOV, const float fAspect, const float fNearPlane, const float fFarPlane) {
	float fFOVh = fFOV * 0.5f;
	float fsin = fastsin(fFOVh);
	float fcos = fastcos(fFOVh);
	float farnear = fFarPlane-fNearPlane;
	float f_fsin = 1 / fsin;
	
	memset(this, 0, sizeof(MATRIX4));
	if (ISZERO(fastfabs(farnear))) return;
	if (ISZERO(fastfabs(fsin))) return;

	float w = fAspect * ( fcos * f_fsin );
	float h = /* 1.0f * */ ( fcos * f_fsin );
	float Q = fFarPlane / farnear;

	this->_11 = w;
	this->_22 = h;
	this->_33 = Q;
	this->_34 = 1.0f;
	this->_43 = -Q*fNearPlane;
}

VSINLINE MATRIX4 MATRIX4::GetProjection(const float fFOV, const float fAspect, const float fNearPlane, const float fFarPlane) const {
	MATRIX4 Matrix;
	Matrix.Projection(fFOV, fAspect, fNearPlane, fFarPlane);		
	return Matrix;
}

VSINLINE void MATRIX4::ViewMatrix(const VECTOR3 &vPosition, const VECTOR3 &vFixpunkt, const VECTOR3 &vWeltY) {
	this->Identity();
	D3DXMatrixLookAtLH((D3DXMATRIX*)this, (D3DXVECTOR3*)&vPosition, (D3DXVECTOR3*)&vFixpunkt, (D3DXVECTOR3*)&vWeltY); 
}

VSINLINE MATRIX4 MATRIX4::GetViewMatrix(const VECTOR3 &vPosition, const VECTOR3 &vFixpunkt, const VECTOR3 &vWeltY) const{
	MATRIX4 Matrix;
	Matrix.ViewMatrix(vPosition, vFixpunkt, vWeltY);
	return Matrix;
}

//================------------------- Extended Members, sozusagen ------------------------

VSINLINE void MATRIX4::Assign( const float f11, const float f12, const float f13, const float f14, const float f21, const float f22, const float f23, const float f24, const float f31, const float f32, const float f33, const float f34, const float f41, const float f42, const float f43, const float f44 ) {
	this->_11 = f11;	this->_12 = f12;	this->_13 = f13;	this->_14 = f14;
	this->_21 = f21;	this->_22 = f22;	this->_23 = f23;	this->_24 = f24;
	this->_31 = f31;	this->_32 = f32;	this->_33 = f33;	this->_34 = f34;
	this->_41 = f41;	this->_42 = f42;	this->_43 = f43;	this->_44 = f44;
}

VSINLINE void MATRIX4::Assign( const VECTOR3& rotX, const float wX, const VECTOR3& rotY, const float wY, const VECTOR3& rotZ, const float wZ, const VECTOR3& position, const float wPos ) {
	this->_11 = rotX.x;	this->_12 = rotX.y;	this->_13 = rotX.z;	this->_14 = wX;
	this->_21 = rotY.x;	this->_22 = rotY.y;	this->_23 = rotY.z;	this->_24 = wY;
	this->_31 = rotZ.x;	this->_32 = rotZ.y;	this->_33 = rotZ.z;	this->_34 = wZ;
	this->_41 = position.x;	this->_42 = position.y;	this->_43 = position.z;	this->_44 = wPos;
}

VSINLINE void MATRIX4::Assign( const MATRIX4 *In ) {
	memcpy(this, In, sizeof(MATRIX4));
}

#ifndef QUATERNION_DEFINED
VSINLINE void MATRIX4::AffineTransform(const float Scaling, const VECTOR3& RotationCenter, const QUATERNION& Rotation, const VECTOR3& Translation) {
	D3DXMatrixAffineTransformation((D3DXMATRIX*)this, Scaling, (D3DXVECTOR3*)&RotationCenter, (D3DXQUATERNION*)&Rotation, (D3DXVECTOR3*)&Translation);
}

VSINLINE MATRIX4 MATRIX4::GetAffineTransformed(const float Scaling, const VECTOR3& RotationCenter, const QUATERNION& Rotation, const VECTOR3& Translation) const {
	MATRIX4 Mat;
	D3DXMatrixAffineTransformation((D3DXMATRIX*)&Mat, Scaling, (D3DXVECTOR3*)&RotationCenter, (D3DXQUATERNION*)&Rotation, (D3DXVECTOR3*)&Translation);
	return Mat;
}
#endif

VSINLINE float MATRIX4::GetDeterminant() {
	return D3DXMatrixDeterminant((D3DXMATRIX*)this);
}

VSINLINE void MATRIX4::Identity() {
	memset(this, 0, sizeof(MATRIX4));
	this->_11 = 1.f;
	this->_22 = 1.f;
	this->_33 = 1.f;
	this->_44 = 1.f;
}

VSINLINE MATRIX4 MATRIX4::GetIdentity() const {
	MATRIX4 Mat;
	Mat.Identity();
	return Mat;
}

VSINLINE void MATRIX4::Inverse() {
	D3DXMatrixInverse((D3DXMATRIX*)this, NULL, (D3DXMATRIX*)this);
}

VSINLINE MATRIX4 MATRIX4::GetInversed() const {
	MATRIX4 Mat;
	Mat.Inverse();
	return Mat;
}

VSINLINE void MATRIX4::Inverse(const MATRIX4& in) {
	D3DXMatrixInverse((D3DXMATRIX*)this, NULL, (D3DXMATRIX*)&in);
}

VSINLINE MATRIX4 MATRIX4::GetInversed(const MATRIX4& in) const {
	MATRIX4 Mat;
	Mat.Inverse(in);
	return Mat;
}

VSINLINE void MATRIX4::Inverse(float* Determinant) {
	D3DXMatrixInverse((D3DXMATRIX*)this, Determinant, (D3DXMATRIX*)this);
}

VSINLINE MATRIX4 MATRIX4::GetInversed(float* Determinant) const {
	MATRIX4 Mat;
	Mat.Inverse(Determinant);
	return Mat;
}

VSINLINE BOOL MATRIX4::IsIdentity() {
	return (BOOL)( this->_11 == 1.f && this->_12 == 0.f && this->_13 == 0.f && this->_14 == 0.f
				&& this->_21 == 0.f && this->_22 == 1.f && this->_23 == 0.f && this->_24 == 0.f
				&& this->_31 == 0.f && this->_32 == 0.f && this->_33 == 1.f && this->_34 == 0.f
				&& this->_41 == 0.f && this->_42 == 0.f && this->_43 == 0.f && this->_44 == 1.f );
}

VSINLINE void MATRIX4::Multiply(const MATRIX4& mat) {
	D3DXMatrixMultiply((D3DXMATRIX*)this, (D3DXMATRIX*)this, (D3DXMATRIX*)&mat); 
}

VSINLINE MATRIX4 MATRIX4::GetMultiplied(const MATRIX4& mat) const {
	MATRIX4 Ret;
	D3DXMatrixMultiply((D3DXMATRIX*)&Ret, (D3DXMATRIX*)this, (D3DXMATRIX*)&mat);
	return Ret;
}

VSINLINE void MATRIX4::MultiplyTranspose(const MATRIX4& mat) {
	D3DXMatrixMultiplyTranspose((D3DXMATRIX*)this, (D3DXMATRIX*)this, (D3DXMATRIX*)&mat); 
}

VSINLINE MATRIX4 MATRIX4::GetMultiplyTransposed(const MATRIX4& mat) const {
	MATRIX4 Ret;
	D3DXMatrixMultiplyTranspose((D3DXMATRIX*)&Ret, (D3DXMATRIX*)this, (D3DXMATRIX*)&mat);
	return Ret;
}

#ifdef PLANE_DEFINED
VSINLINE void MATRIX4::Reflect(const PLANE& plane) {
	D3DXMatrixReflect((D3DXMATRIX*)this, (D3DXPLANE*)&plane);
}

VSINLINE MATRIX4 MATRIX4::GetReflected(const PLANE& plane) const {
	MATRIX4 Mat;
	D3DXMatrixReflect((D3DXMATRIX*)&Mat, (D3DXPLANE*)&plane);
	return Mat;
}
#endif

VSINLINE void MATRIX4::Rotate(const VECTOR3& axis, const float angle) {
	D3DXMatrixRotationAxis((D3DXMATRIX*)this, (D3DXVECTOR3*)&axis, angle);
}

VSINLINE MATRIX4 MATRIX4::GetRotated(const VECTOR3& axis, const float angle) const {
	MATRIX4 Mat(*this);
	D3DXMatrixRotationAxis((D3DXMATRIX*)&Mat, (D3DXVECTOR3*)&axis, angle);
	return Mat;
}

#ifndef QUATERNION_DEFINED
VSINLINE void MATRIX4::Rotate(const QUATERNION& quaternion) {
	D3DXMatrixRotationQuaternion((D3DXMATRIX*)this, (D3DXQUATERNION*)&quaternion);
}

VSINLINE MATRIX4 MATRIX4::GetRotated(const QUATERNION& quaternion) const {
	MATRIX4 Mat;
	D3DXMatrixRotationQuaternion((D3DXMATRIX*)&Mat, (D3DXQUATERNION*)&quaternion);
	return Mat;
}
#endif

VSINLINE void MATRIX4::Rotate(const float pitchX, const float yawY, const float rollZ) {
	D3DXMatrixRotationYawPitchRoll((D3DXMATRIX*)this, yawY, pitchX, rollZ);
}

VSINLINE MATRIX4 MATRIX4::GetRotated(const float pitchX, const float yawY, const float rollZ) const {
	MATRIX4 Mat;
	D3DXMatrixRotationYawPitchRoll((D3DXMATRIX*)&Mat, yawY, pitchX, rollZ);
	return Mat;
}

VSINLINE void MATRIX4::RotateX(const float angle) {
	D3DXMatrixRotationX((D3DXMATRIX*)this, angle);
}

VSINLINE MATRIX4 MATRIX4::GetRotateXd(const float angle) const {
	MATRIX4 Mat;
	D3DXMatrixRotationX((D3DXMATRIX*)&Mat, angle);
	return Mat;
}

VSINLINE void MATRIX4::RotateY(const float angle) {
	D3DXMatrixRotationY((D3DXMATRIX*)this, angle);
}

VSINLINE MATRIX4 MATRIX4::GetRotateYd(const float angle) const {
	MATRIX4 Mat;
	D3DXMatrixRotationY((D3DXMATRIX*)&Mat, angle);
	return Mat;
}

VSINLINE void MATRIX4::RotateZ(const float angle) {
	D3DXMatrixRotationZ((D3DXMATRIX*)this, angle);
}

VSINLINE MATRIX4 MATRIX4::GetRotateZd(const float angle) const {
	MATRIX4 Mat;
	D3DXMatrixRotationZ((D3DXMATRIX*)&Mat, angle);
	return Mat;
}

VSINLINE void MATRIX4::Scale(const float sX, const float sY, const float sZ) {
	this->Multiply(this->GetScaling(sX, sY, sZ));
}

VSINLINE MATRIX4 MATRIX4::GetScaled(const float sX, const float sY, const float sZ) const {
	MATRIX4 Mat(*this);
	Mat.Multiply(this->GetScaling(sX, sY, sZ));
	return Mat;
}

VSINLINE void MATRIX4::Scaling(const float sX, const float sY, const float sZ) {
	D3DXMatrixScaling((D3DXMATRIX*)this, sX, sY, sZ);
}

VSINLINE MATRIX4 MATRIX4::GetScaling(const float sX, const float sY, const float sZ) const {
	MATRIX4 Mat;
	D3DXMatrixScaling((D3DXMATRIX*)&Mat, sX, sY, sZ);
	return Mat;
}

#ifdef PLANE_DEFINED
VSINLINE void MATRIX4::Shadow(const VECTOR4& Light, const PLANE& Plane) {
	D3DXMatrixShadow((D3DXMATRIX*)this, (D3DXVECTOR4*)&Light, (D3DXPLANE*)&Plane);		
}

VSINLINE MATRIX4 MATRIX4::GetShadowed(const VECTOR4& Light, const PLANE& Plane) const {
	MATRIX4 Mat;
	D3DXMatrixShadow((D3DXMATRIX*)&Mat, (D3DXVECTOR4*)&Light, (D3DXPLANE*)&Plane);
	return Mat;
}
#endif

#ifndef QUATERNION_DEFINED
VSINLINE void MATRIX4::Transform(const VECTOR3& ScalingCenter, const QUATERNION& ScalingRotation, const VECTOR3& Scaling, const VECTOR3& RotationCenter, const QUATERNION& Rotation, const VECTOR3& Translation) {
	D3DXMatrixTransformation((D3DXMATRIX*)this, (D3DXVECTOR3*)&ScalingCenter, (D3DXQUATERNION*)&ScalingRotation, (D3DXVECTOR3*)&Scaling, (D3DXVECTOR3*)&RotationCenter, (D3DXQUATERNION*)&Rotation, (D3DXVECTOR3*)&Translation);
}

VSINLINE MATRIX4 MATRIX4::GetTransformed(const VECTOR3& ScalingCenter, const QUATERNION& ScalingRotation, const VECTOR3& Scaling, const VECTOR3& RotationCenter, const QUATERNION& Rotation, const VECTOR3& Translation) const {
	MATRIX4 Mat;
	D3DXMatrixTransformation((D3DXMATRIX*)&Mat, (D3DXVECTOR3*)&ScalingCenter, (D3DXQUATERNION*)&ScalingRotation, (D3DXVECTOR3*)&Scaling, (D3DXVECTOR3*)&RotationCenter, (D3DXQUATERNION*)&Rotation, (D3DXVECTOR3*)&Translation);
	return Mat;
}
#endif

VSINLINE void MATRIX4::Translation(const float x, const float y, const float z) {
	D3DXMatrixTranslation((D3DXMATRIX*)this, x, y, z);
}

VSINLINE MATRIX4 MATRIX4::GetTranslationed(const float x, const float y, const float z) const {
	MATRIX4 Mat;
	D3DXMatrixTranslation((D3DXMATRIX*)&Mat, x, y, z);
	return Mat;
}

VSINLINE void  MATRIX4::TranslateMove(const float shiftX, const float shiftY, const float shiftZ) {
	this->_41 += shiftX;
	this->_42 += shiftY;
	this->_43 += shiftZ;
}

VSINLINE MATRIX4 MATRIX4::GetTranslateMoved(const float shiftX, const float shiftY, const float shiftZ) const {
	MATRIX4 Mat(*this);
	Mat._41 += shiftX;
	Mat._42 += shiftY;
	Mat._43 += shiftZ;
	return Mat;
}

VSINLINE void MATRIX4::TranslateSet(const float newX, const float newY, const float newZ) {
	this->_41 = newX;
	this->_42 = newY;
	this->_43 = newZ;
}

VSINLINE MATRIX4 MATRIX4::GetTranslateSet(const float newX, const float newY, const float newZ) const {
	MATRIX4 Mat(*this);
	Mat._41 = newX;
	Mat._42 = newY;
	Mat._43 = newZ;
	return Mat;
}

VSINLINE void MATRIX4::Transpose(const MATRIX4& M) {
	D3DXMatrixTranspose((D3DXMATRIX*)this, (D3DXMATRIX*)&M);
}

VSINLINE MATRIX4 MATRIX4::GetTransposed(const MATRIX4& M) const {
	MATRIX4 Mat;
	D3DXMatrixTranspose((D3DXMATRIX*)&Mat, (D3DXMATRIX*)&M);
	return Mat;
}

VSINLINE VECTOR3 MATRIX4::GetLocation() const {
	return VECTOR3(this->_41, this->_42, this->_43);
}

VSINLINE const MATRIX4& MATRIX4::operator = (const MATRIX4& Matrix) {
	memcpy(this, &Matrix, sizeof(MATRIX4));
	return *this;
}

VSINLINE MATRIX4::MATRIX4() {	
	/* Do nothing. */ 
}


// Funktionen: Winkelbezogen ............................................
VSINLINE void MATRIX4::ClampAngles() {
	for(unsigned int x=0; x<3; x++) {
		for(unsigned int y=0; y<3; y++) {
			while(this->m[x][y] > PIx2)
				this->m[x][y] -= PIx2;
			while(this->m[x][y] < 0.f)
				this->m[x][y] += PIx2;
		}
	}
}

VSINLINE void MATRIX4::GetClampedAngles(MATRIX4 *out_mClamped) {
	memcpy(&out_mClamped, this, sizeof(MATRIX4));
	for(unsigned int x=0; x<3; x++) {
		for(unsigned int y=0; y<3; y++) {
			while(out_mClamped->m[x][y] > PIx2)
				out_mClamped->m[x][y] -= PIx2;
			while(out_mClamped->m[x][y] < 0.f)
				out_mClamped->m[x][y] += PIx2;
		}
	}
}

VSINLINE void MATRIX4::ToValue( const float in_fValue) {
	this->_11 = in_fValue;
	this->_12 = in_fValue;
	this->_13 = in_fValue;
	this->_14 = in_fValue;
	this->_21 = in_fValue;
	this->_22 = in_fValue;
	this->_23 = in_fValue;
	this->_24 = in_fValue;
	this->_31 = in_fValue;
	this->_32 = in_fValue;
	this->_33 = in_fValue;
	this->_34 = in_fValue;
	this->_41 = in_fValue;
	this->_42 = in_fValue;
	this->_43 = in_fValue;
	this->_44 = in_fValue;
}

VSINLINE void MATRIX4::Fill( const float in_fValue) {
	ToValue(in_fValue);
}

VSINLINE void MATRIX4::Assign( const float in_fValue) {
	ToValue(in_fValue);
}