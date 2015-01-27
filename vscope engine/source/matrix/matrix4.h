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

	Dateiname:		matrix4.h
	Beschreibung:	4D-Matrix Definition
	Revision:		1
	Erstellt:		MMT, 05. Juli 2002 18:55

	Changelog:
	[1]		05. Juli 2002 18:55

===========================================================================*/

#pragma once

#ifndef MATRIX4_DEFINED
#define MATRIX4_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct VECTOR2;
struct VECTOR3;
struct VECTOR4;
struct QUATERNION;
struct PLANE;

/*---------------------------------------------------------------------------
	Struktur für die 4D-Matrix
---------------------------------------------------------------------------*/
struct MATRIX4 {
//:: Die Membervariablen ....................................................
public:		
	union {
		struct { float	_11, _12, _13, _14,
						_21, _22, _23, _24,
						_31, _32, _33, _34,
						_41, _42, _43, _44; };
		float m[4][4];
		float m16[16];
	};

	//:: Die Konstruktoren ......................................................
public:
						MATRIX4();
						MATRIX4(const MATRIX4 &inMat);
						MATRIX4(const MATRIX4 *inMat);
						MATRIX4(const float f11, const float f12, const float f13, const float f14,
								const float f21, const float f22, const float f23, const float f24,
								const float f31, const float f32, const float f33, const float f34,
								const float f41, const float f42, const float f43, const float f44 );
						MATRIX4(const D3DXMATRIX &inMat);
						MATRIX4(const D3DXMATRIX *inMat);
						MATRIX4(const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const VECTOR4 &v4);
						MATRIX4(const VECTOR3 &x, const float wx, const VECTOR3 &y, const float wy, const VECTOR3 &z, const float wz, const VECTOR3 &pos, const float wpos);
						MATRIX4(const float *f);

//:: Das Interface ..........................................................
public:
	// Operatoren: Zugriff ..................................................
						float& operator () ( UINT iRow, UINT iCol );
						float operator () ( UINT iRow, UINT iCol ) const;
	
	// Operatoren: Casting ..................................................
						operator float* ();
						operator const float* () const;
						operator D3DXMATRIX ();
						operator D3DXMATRIX* ();
						operator const D3DXMATRIX* () const;
						operator D3DXMATRIX& ();
						operator const D3DXMATRIX& () const;

	// Operatoren: Zuweisung ................................................
	MATRIX4&			operator *= ( const MATRIX4& mat );
	MATRIX4&			operator += ( const MATRIX4& mat );
	MATRIX4&			operator -= ( const MATRIX4& mat );
	MATRIX4&			operator *= ( float f );
	MATRIX4&			operator /= ( float f );
	
	// Operatoren: Unär .....................................................
	MATRIX4				operator + () const;
	MATRIX4				operator - () const;
	
	// Operatoren: Binär ....................................................
	MATRIX4				operator + ( const MATRIX4& mat ) const;
	MATRIX4				operator - ( const MATRIX4& mat ) const;
	MATRIX4				operator * ( float f ) const;
	MATRIX4				operator / ( float f ) const;
	MATRIX4					operator * ( const MATRIX4& mat ) const;
	
	// Operatoren: Vergleich ................................................
	bool				operator == ( const MATRIX4& mat ) const;
	bool				operator != ( const MATRIX4& mat ) const;

	// Operatoren: Kopie ....................................................
	const MATRIX4&		operator = (const MATRIX4& Matrix);

	// Funktionen: Einfache .................................................
	void				Assign( const float f11, const float f12, const float f13, const float f14, const float f21, const float f22, const float f23, const float f24, const float f31, const float f32, const float f33, const float f34, const float f41, const float f42, const float f43, const float f44 );
	void				Assign( const VECTOR3& rotX, const float wX, const VECTOR3& rotY, const float wY, const VECTOR3& rotZ, const float wZ, const VECTOR3& position, const float wPos );
	void				Assign( const MATRIX4 *In );
	void				Assign( const float in_fValue);

	// Funktionen: Winkelbezogen ............................................
	void				ClampAngles();	// Setzt die Rotationswinkel auf den Bereich 0..PIx2
	void				GetClampedAngles(MATRIX4 *out_mClamped);	// Gibt eine Matrix zurück, die die "geclampten" Winkel enthält

	// Funktionen: Erweiterte ...............................................
	void				AffineTransform(const float Scaling, const VECTOR3& RotationCenter, const QUATERNION& Rotation, const VECTOR3& Translation);
	MATRIX4				GetAffineTransformed(const float Scaling, const VECTOR3& RotationCenter, const QUATERNION& Rotation, const VECTOR3& Translation) const;
	float				GetDeterminant();
	void				Identity();
	MATRIX4				GetIdentity() const;
	BOOL				IsIdentity();
	void				Inverse();
	MATRIX4				GetInversed() const;		
	void				Inverse(const MATRIX4& in);
	MATRIX4				GetInversed(const MATRIX4& in) const;		
	void				Inverse(float* Determinant);
	MATRIX4				GetInversed(float* Determinant) const;		
	void				Multiply(const MATRIX4& mat);
	MATRIX4				GetMultiplied(const MATRIX4& mat) const;
	void				MultiplyTranspose(const MATRIX4& mat);
	MATRIX4				GetMultiplyTransposed(const MATRIX4& mat) const;
	void				Reflect(const PLANE& plane);
	MATRIX4				GetReflected(const PLANE& plane) const;
	void				Rotate(const VECTOR3& axis, const float angle);
	MATRIX4				GetRotated(const VECTOR3& axis, const float angle) const;
	void				Rotate(const QUATERNION& quaternion);
	MATRIX4				GetRotated(const QUATERNION& quaternion) const;
	void				Rotate(const float pitchX, const float yawY, const float rollZ);
	MATRIX4				GetRotated(const float pitchX, const float yawY, const float rollZ) const;
	void				RotateX(const float angle);
	MATRIX4				GetRotateXd(const float angle) const;
	void				RotateY(const float angle);
	MATRIX4				GetRotateYd(const float angle) const;
	void				RotateZ(const float angle);
	MATRIX4				GetRotateZd(const float angle) const;
	void				Scale(const float sX, const float sY, const float sZ);
	MATRIX4				GetScaled(const float sX, const float sY, const float sZ) const;
	void				Scaling(const float sX, const float sY, const float sZ);
	MATRIX4				GetScaling(const float sX, const float sY, const float sZ) const;
	void				Shadow(const VECTOR4& Light, const PLANE& Plane);
	MATRIX4				GetShadowed(const VECTOR4& Light, const PLANE& Plane) const;
	void				Transform(const VECTOR3& ScalingCenter, const QUATERNION& ScalingRotation, const VECTOR3& Scaling, const VECTOR3& RotationCenter, const QUATERNION& Rotation, const VECTOR3& Translation);
	MATRIX4				GetTransformed(const VECTOR3& ScalingCenter, const QUATERNION& ScalingRotation, const VECTOR3& Scaling, const VECTOR3& RotationCenter, const QUATERNION& Rotation, const VECTOR3& Translation) const;
	void				Translation(const float x, const float y, const float z);
	MATRIX4				GetTranslationed(const float x, const float y, const float z) const;
	void				TranslateMove(const float shiftX, const float shiftY, const float shiftZ);
	MATRIX4				GetTranslateMoved(const float shiftX, const float shiftY, const float shiftZ) const;
	void				TranslateSet(const float newX, const float newY, const float newZ);
	MATRIX4				GetTranslateSet(const float newX, const float newY, const float newZ) const;
	void				Transpose(const MATRIX4& M);
	MATRIX4				GetTransposed(const MATRIX4& M) const;
	void				Projection(const float fFOV, const float fAspect, const float fNearPlane, const float fFarPlane);
	MATRIX4				GetProjection(const float fFOV, const float fAspect, const float fNearPlane, const float fFarPlane) const;
	void				ViewMatrix(const VECTOR3 &vPosition, const VECTOR3 &vFixpunkt, const VECTOR3 &vWeltY);
	MATRIX4				GetViewMatrix(const VECTOR3 &vPosition, const VECTOR3 &vFixpunkt, const VECTOR3 &vWeltY) const;
	VECTOR3				GetLocation() const;
	void				ToZero();

	void				ToValue( const float in_fValue);
	void				Fill( const float in_fValue);
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef MATRIX4					*LPMATRIX4;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 MATRIX4		MATRIX4A16;
typedef _ALIGN_16 MATRIX4		*LPMATRIX4A16;

typedef _ALIGN_32 MATRIX4		MATRIX4A32;
typedef _ALIGN_32 MATRIX4		*LPMATRIX4A32;

typedef _CACHEALIGN MATRIX4		MATRIX4AC;
typedef _CACHEALIGN MATRIX4		*LPMATRIX4AC;*/