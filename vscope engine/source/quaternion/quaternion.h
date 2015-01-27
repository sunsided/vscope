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

	Dateiname:		quaternion.h
	Beschreibung:	Quaternion Definition
	Revision:		2
	Erstellt:		MMT, 07. Juli 2002 18:56

	Changelog:
	[2]		14. Juli 2002 22:05
			GetRotation() hinzugefügt
	[1]		07. Juli 2002 18:56

===========================================================================*/

#pragma once

#ifndef QUATERNION_DEFINED
#define QUATERNION_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vektoren\define-vectorops.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct MATRIX4;
struct VECTOR3;

/*---------------------------------------------------------------------------
	Struktur für den Quaternion
---------------------------------------------------------------------------*/
struct QUATERNION {
//:: Die Membervariablen ....................................................
public:
	float x, y, z, w;

	//:: Die Konstruktoren ......................................................
public:
						QUATERNION() {}
						QUATERNION( const float X, const float Y, const float Z, const float W );
						QUATERNION( const float roll, const float pitch, const float yaw );
						QUATERNION( const VECTOR3& axis, const float angle );
						QUATERNION( const float* pf );
						QUATERNION( const MATRIX4& inMat );

//:: Das Interface ..........................................................
public:
	// Operatoren: Zugriff ..................................................
						float& operator () ( UINT iRow, UINT iCol );
						float operator () ( UINT iRow, UINT iCol ) const;
	
	// Operatoren: Casting ..................................................
						operator float* ();
						operator const float* () const;

	// Operatoren: Zuweisung ................................................
	QUATERNION&		operator += ( const QUATERNION& q );
	QUATERNION&		operator -= ( const QUATERNION& q );
	QUATERNION&		operator *= ( const QUATERNION& q );
	QUATERNION&		operator *= ( float f );
	QUATERNION&		operator /= ( float f );
	
	// Operatoren: Unär .....................................................
	QUATERNION		operator + () const;
	QUATERNION		operator - () const;
	
	// Operatoren: Binär ....................................................
	QUATERNION		operator + ( const QUATERNION& q ) const;
	QUATERNION		operator - ( const QUATERNION& q ) const;
	QUATERNION		operator * ( const QUATERNION& q ) const;
	float			operator DOT ( const QUATERNION& q ) const;
	QUATERNION		operator * ( float f ) const;
	QUATERNION		operator / ( float f ) const;

	// Operatoren: Vergleich ................................................
	bool			operator == ( const QUATERNION& q ) const;
	bool			operator != ( const QUATERNION& q ) const;

	// Operatoren: Kopie ....................................................
	const QUATERNION&	operator = (const QUATERNION& Quaternion);

	// Funktionen: Einfache .................................................
	void			Assign( float X, float Y, float Z, float W );
	void			Assign( QUATERNION *In );
	void			Negate();
	QUATERNION		GetNegated() const;
	float			GetMag() const;
	float			GetMagSquared() const;
	float			GetLength() const;
	float			GetLengthSquared() const;
	void			Normalize();
	QUATERNION		GetNormalized() const;

	float			GetDistance( const QUATERNION& v ) const;

	// Funktionen: Erweiterte ...............................................
	void			Conjugate() const;
	QUATERNION		GetConjugated() const;
	void			Exponential() const;
	QUATERNION		GetExponential() const;
	void			Identity();
	QUATERNION		GetIdentity() const;
	void			Inverse() const;
	QUATERNION		GetInversed() const;
	BOOL			IsIdentity() const;
	void			Ln() const;
	QUATERNION		GetLn() const;

	float			Dot(const QUATERNION& v) const;
	void			Multiply(const QUATERNION& v);
	QUATERNION		GetMultiplied(const QUATERNION& v) const;

	void			Rotate(const VECTOR3& v, const float angle);
	QUATERNION		GetRotated(const VECTOR3& v, const float angle);
	void			Rotate(const MATRIX4& m);
	QUATERNION		GetRotated(const MATRIX4& m) const;
	void			Rotate(const float x, const float y, const float z);
	QUATERNION		GetRotated(const float x, const float y, const float z) const;
	void			GetRotationAxisAngle(VECTOR3 *axis, float* angle) const;

	void			Slerp(const QUATERNION& v, const float s);
	QUATERNION		GetSlerped(const QUATERNION& v, const float s) const;
	void			Squad(const QUATERNION& Q1, const QUATERNION& A, const QUATERNION& B, const QUATERNION& C, const float t);
	QUATERNION		GetSquaded(const QUATERNION& Q1, const QUATERNION& A, const QUATERNION& B, const QUATERNION& C, const float t) const;
	void			GetSquadSetup(const QUATERNION* outA, const QUATERNION* outB, const QUATERNION* outC, const QUATERNION& Q0, const QUATERNION& Q1, const QUATERNION& Q2, const QUATERNION& Q3) const;

	void			BaryCentric(const QUATERNION& v1, const QUATERNION& v2, const QUATERNION& v3, const float f, const float g);
	QUATERNION		GetBaryCentric(const QUATERNION& v1, const QUATERNION& v2, const QUATERNION& v3, const float f, const float g) const;

	void			ToMatrix(MATRIX4* mat) const;
	MATRIX4			ToMatrix() const;

	void			GetRotation(float& fX, float& fY, float& fZ) const;
	void			GetRotation(VECTOR3* vRotation) const;
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef QUATERNION				*LPQUATERNION;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 QUATERNION	QUATERNIONA16;
typedef _ALIGN_16 QUATERNION	*LPQUATERNIONA16;

typedef _ALIGN_32 QUATERNION	QUATERNIONA32;
typedef _ALIGN_32 QUATERNION	*LPQUATERNIONA32;

typedef _CACHEALIGN QUATERNION	QUATERNIONAC;
typedef _CACHEALIGN QUATERNION	*LPQUATERNIONAC;*/