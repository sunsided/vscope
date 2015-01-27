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

	Dateiname:		vector2.h
	Beschreibung:	2D-Vektor Definition
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:37

	Changelog:
	[1]		04. Juli 2002 23:37

===========================================================================*/

#pragma once

#ifndef VECTOR2_DEFINED
#define VECTOR2_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "define-vectorops.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct MATRIX4;
struct VECTOR3;
struct VECTOR4;

/*---------------------------------------------------------------------------
	Struktur für den 2D-Vektor
---------------------------------------------------------------------------*/
struct VECTOR2 {
//:: Die Membervariablen ....................................................
public:		
	union {
		struct { float x, y; };
		float v[2];
	};

//:: Die Konstruktoren ......................................................
public:
						VECTOR2();
						VECTOR2(const VECTOR2 &inVec);
						VECTOR2(const VECTOR2 *inVec);
						VECTOR2(const float inx, const float iny);
						VECTOR2(const float *inv);
						VECTOR2(const D3DXVECTOR2 &inVec);
						VECTOR2(const D3DXVECTOR2 *inVec);
						VECTOR2(const VECTOR3 &inVec);
						VECTOR2(const VECTOR3 *inVec);
						VECTOR2(const VECTOR4 &inVec);
						VECTOR2(const VECTOR4 *inVec);

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
    operator			float* () const;
    operator			const float* () const;
    operator			D3DXVECTOR2 () const;
    operator			const D3DXVECTOR2 () const;

	// Operatoren: Zuweisung ................................................
    VECTOR2&			operator += ( const VECTOR2 &v );
	VECTOR2&			operator += ( const D3DXVECTOR2 &v );
	VECTOR2&			operator -= ( const VECTOR2 &v );
	VECTOR2&			operator -= ( const D3DXVECTOR2 &v );
    VECTOR2&			operator *= ( float f );
    VECTOR2&			operator /= ( float f );
	VECTOR2&			operator =	( const VECTOR2 &v );
	VECTOR2&			operator =	( const D3DXVECTOR2 &v );

    // Operatoren: Unär .....................................................
    VECTOR2				operator + () const;
    VECTOR2				operator - () const;

    // Operatoren: Binär ....................................................
    VECTOR2				operator + ( const VECTOR2 &v ) const;
	VECTOR2				operator + ( const D3DXVECTOR2 &v ) const;
    VECTOR2				operator - ( const VECTOR2 &v ) const;
	VECTOR2				operator - ( const D3DXVECTOR2 &v ) const;
    VECTOR2				operator * ( float f ) const;
    VECTOR2				operator / ( float f ) const;
	float				operator DOT ( const VECTOR2& v ) const;
	float				operator DOT ( const D3DXVECTOR2& v ) const;
	friend VECTOR2		operator * ( float f, const VECTOR2 &v );

	// Operatoren: Vergleich ................................................
    bool				operator == ( const VECTOR2& ) const;
	bool				operator == ( const D3DXVECTOR2& ) const;
	bool				operator != ( const VECTOR2& ) const;
    bool				operator != ( const D3DXVECTOR2& ) const;

	// Funktionen: Zuweisung ................................................
	void				Assign( const float x, const float y );
	void				Assign( const float *v );
	void				Assign( const VECTOR2 &inVec );
	void				Assign( const VECTOR2 *inVec );
	void				Assign( const D3DXVECTOR2 &inVec );
	void				Assign( const D3DXVECTOR2 *inVec );
	void				Assign( const VECTOR3 &inVec );
	void				Assign( const VECTOR3 *inVec );
	void				Assign( const VECTOR4 &inVec );
	void				Assign( const VECTOR4 *inVec );

	// Funktionen: Einfach ..................................................
	void				Negate();											// Negiert den Vektor
	VECTOR2				GetNegated() const;									// Liefert den negierten Vektor
	float				GetMag() const;										// Gibt die Länge (Magnitude) des Vektors zurück
	float				GetMagSquared() const;								// Gibt die quadrierte Länge (Magnitude) des Vektors zurück
	float				GetLength() const;									// Gibt die Länge (Magnitude) des Vektors zurück
	float				GetLengthSquared() const;							// Gibt die quadrierte Länge (Magnitude) des Vektors zurück
	void				Normalize();										// Normalisiert den Vektor
	VECTOR2				GetNormalized() const;								// Liefert den normalisierten Vektor

	// Funktionen: Erweitert ................................................
	float				GetDistance( const VECTOR2 &v ) const;				// Liefert die Distanz zum gegebenen Vektor
	float				GetDistance( const D3DXVECTOR2 &v ) const;			// Liefert die Distanz zum gegebenen Vektor
	float				Dot( const VECTOR2 &v ) const;						// Berechnet das Punktprodukt
	float				Dot( const D3DXVECTOR2 &v ) const;					// Berechnet das Punktprodukt
	void				Lerp( const VECTOR2 &v, const float s ) const;		// Führt eine lineare Interpolation durch
	VECTOR2				GetLerped( const VECTOR2 &v, const float s ) const;	// Führt eine lineare Interpolation durch

	void				Maximise( const VECTOR2 &v );						// Übernimmt die größten Komponenten beider Vektoren
	VECTOR2				GetMaximised( const VECTOR2 &v ) const;				// Liefert einen Vektor der größten Komponenten
	void				Minimise( const VECTOR2 &v );						// Übernimmt die kleinsten Komponenten beider Vektoren
	VECTOR2				GetMinimised( const VECTOR2 &v ) const;				// Liefert einen Vektor der kleinsten Komponenten

	void				Scale( const float s );								// Skaliert den Vektor
	VECTOR2				GetScaled( const float s ) const;					// Liefert den skalierten Vektor zurück

	void				Add( const VECTOR2 &v );							// Addiert den Vektor
	VECTOR2				GetAdded( const VECTOR2 &v ) const;					// Liefert den resultierenden Vektor der Addition
	void				Subtract( const VECTOR2 &v );						// Subtrahiert den Vektor
	VECTOR2				GetSubtracted( const VECTOR2 &v ) const;			// Liefert den resultierenden Vektor der Addition

	void				Transform( const MATRIX4 &m );						// Transformiert den Vektor (x,y,0,1) und übernimmt die X- und Y-Komponente
	VECTOR2				GetTransformed( const MATRIX4 &m ) const;			// Liefert den transformierten Vektor
	void				TransformCoord( const MATRIX4 &m );					// Transformiert den Vektor (x,y,0,1) und projiziert ihn zurück auf w
	VECTOR2				GetTransformCoord( const MATRIX4 &m ) const;		// Liefert den transformierten Vektor
	void				TransformNormal( const MATRIX4 &m );				// Transformiert die Vektornormale (x,y,0,0) und übernimmt das Ergebnis
	VECTOR2				GetTransformNormal( const MATRIX4 &m ) const;		// Liefert den transformierten Vektor

	void				BaryCentric( const VECTOR2 &v1, const VECTOR2 &v2, const VECTOR2 &v3, const float f, const float g );				// Berechnet einen Punkt in baryzentrischen Koordinaten
	VECTOR2				GetBaryCentric( const VECTOR2 &v1, const VECTOR2 &v2, const VECTOR2 &v3, const float f, const float g ) const;

	void				CatmullRom( const VECTOR2 &v1, const VECTOR2 &v2, const VECTOR2 &v3, const VECTOR2 &v4, const float s );			// Führt eine Catmull-Rom-Interpolation durch und behält das Ergebnis
	VECTOR2				GetCatmullRom( const VECTOR2 &v1, const VECTOR2 &v2, const VECTOR2 &v3, const VECTOR2 &v4, const float s ) const;	// Liefert dieses Ergebnis zurück
	void				Hermite( const VECTOR2 &v1, const VECTOR2 &t1, const VECTOR2 &v2, const VECTOR2 &t2, const float s );				// Führt eine Catmull-Rom-Interpolation durch und behält das Ergebnis
	VECTOR2				GetHermite( const VECTOR2 &v1, const VECTOR2 &t1, const VECTOR2 &v2, const VECTOR2 &t2, const float s ) const;		// Liefert dieses Ergebnis zurück

};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef VECTOR2					*LPVECTOR2;
typedef VECTOR2					POINT2;
typedef VECTOR2					*LPPOINT2;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*
typedef _ALIGN_16 VECTOR2		VECTOR2A16;
typedef _ALIGN_16 VECTOR2		*LPVECTOR2A16;
typedef _ALIGN_16 VECTOR2		POINT2A16;
typedef _ALIGN_16 VECTOR2		*LPPOINT2A16;

typedef _ALIGN_32 VECTOR2		VECTOR2A32;
typedef _ALIGN_32 VECTOR2		*LPVECTOR2A32;
typedef _ALIGN_32 VECTOR2		POINT2A32;
typedef _ALIGN_32 VECTOR2		*LPPOINT2A32;

typedef _CACHEALIGN VECTOR2		VECTOR2AC;
typedef _CACHEALIGN VECTOR2		*LPVECTOR2AC;
typedef _CACHEALIGN VECTOR2		POINT2AC;
typedef _CACHEALIGN VECTOR2		*LPPOINT2AC;*/