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

	Dateiname:		vector4.h
	Beschreibung:	4D-Vektor Definition
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:37

	Changelog:
	[1]		04. Juli 2002 23:37

===========================================================================*/

#pragma once

#ifndef VECTOR4_DEFINED
#define VECTOR4_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "define-vectorops.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct MATRIX4;
struct VECTOR2;
struct VECTOR3;

/*---------------------------------------------------------------------------
	Struktur für den 4D-Vektor
---------------------------------------------------------------------------*/
struct VECTOR4 {
//:: Die Membervariablen ....................................................
public:		
	union {
		struct { float x, y, z, w; };
		float v[4];
	};

//:: Die Konstruktoren ......................................................
public:
						VECTOR4();
						VECTOR4(const VECTOR4 &inVec);
						VECTOR4(const VECTOR4 *inVec);
						VECTOR4(const float inx, const float iny, const float inz, const float inw);
						VECTOR4(const float *inv);
						VECTOR4(const VECTOR2 &inVec);
						VECTOR4(const VECTOR2 *inVec);
						VECTOR4(const VECTOR3 &inVec);
						VECTOR4(const VECTOR3 *inVec);
						VECTOR4(const D3DXVECTOR4 &inVec);
						VECTOR4(const D3DXVECTOR4 *inVec);

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
    operator			float* () const;
    operator			const float* () const;
    operator			D3DXVECTOR4 () const;
    operator			const D3DXVECTOR4 () const;
    operator			D3DXVECTOR3 () const;
    operator			const D3DXVECTOR3 () const;
	operator			VECTOR3 () const;
    operator			const VECTOR3 () const;

	// Operatoren: Zuweisung ................................................
    VECTOR4&			operator += ( const VECTOR4 &v );
	VECTOR4&			operator += ( const D3DXVECTOR4 &v );
	VECTOR4&			operator -= ( const VECTOR4 &v );
	VECTOR4&			operator -= ( const D3DXVECTOR4 &v );
    VECTOR4&			operator *= ( float f );
	VECTOR4&			operator *= ( const MATRIX4& a );
    VECTOR4&			operator /= ( float f );
	// TODO: Cross für Vektor4
	VECTOR4&			operator ^= ( const VECTOR4& Vector);	// Cross
	VECTOR4&			operator =	( const VECTOR4 &v );
	VECTOR4&			operator =	( const D3DXVECTOR4 &v );

    // Operatoren: Unär .....................................................
    VECTOR4				operator + () const;
    VECTOR4				operator - () const;

    // Operatoren: Binär ....................................................
    VECTOR4				operator + ( const VECTOR4 &v ) const;
	VECTOR4				operator + ( const D3DXVECTOR4 &v ) const;
    VECTOR4				operator - ( const VECTOR4 &v ) const;
	VECTOR4				operator - ( const D3DXVECTOR4 &v ) const;
    VECTOR4				operator * ( float f ) const;
    VECTOR4				operator / ( float f ) const;
	float				operator DOT ( const VECTOR4& v ) const;
	float				operator DOT ( const D3DXVECTOR4& v ) const;
	/*
	VECTOR4				operator CROSS ( const VECTOR4 &b) const;
	VECTOR4				operator CROSS ( const D3DXVECTOR4 &b) const;
	*/
	friend VECTOR4		operator * ( float f, const VECTOR4 &v );

	// Operatoren: Vergleich ................................................
    bool				operator == ( const VECTOR4& ) const;
	bool				operator == ( const D3DXVECTOR4& ) const;
	bool				operator != ( const VECTOR4& ) const;
    bool				operator != ( const D3DXVECTOR4& ) const;

	// Funktionen: Zuweisung ................................................
	void				Assign( const float x, const float y, const float z, const float w );
	void				Assign( const float *v );
	void				Assign( const VECTOR4 &inVec );
	void				Assign( const VECTOR4 *inVec );
	void				Assign( const D3DXVECTOR4 &inVec );
	void				Assign( const D3DXVECTOR4 *inVec );
	void				Assign( const VECTOR2 &inVec );
	void				Assign( const VECTOR2 *inVec );
	void				Assign( const VECTOR3 &inVec );
	void				Assign( const VECTOR3 *inVec );

	// Funktionen: Einfach ..................................................
	void				Negate();											// Negiert den Vektor
	VECTOR4				GetNegated() const;									// Liefert den negierten Vektor
	float				GetMag() const;										// Gibt die Länge (Magnitude) des Vektors zurück
	float				GetMagSquared() const;								// Gibt die quadrierte Länge (Magnitude) des Vektors zurück
	float				GetLength() const;									// Gibt die Länge (Magnitude) des Vektors zurück
	float				GetLengthSquared() const;							// Gibt die quadrierte Länge (Magnitude) des Vektors zurück
	void				Normalize();										// Normalisiert den Vektor
	VECTOR4				GetNormalized() const;								// Liefert den normalisierten Vektor

	// Funktionen: Erweitert ................................................
	float				GetDistance( const VECTOR4 &v ) const;				// Liefert die Distanz zum gegebenen Vektor
	float				GetDistance( const D3DXVECTOR4 &v ) const;			// Liefert die Distanz zum gegebenen Vektor
	float				Dot( const VECTOR4 &v ) const;						// Berechnet das Punktprodukt
	float				Dot( const D3DXVECTOR4 &v ) const;					// Berechnet das Punktprodukt
	/*
	VECTOR4				Cross(const VECTOR4& v)  const;						// Berechnet das Kreuzprodukt
	void				ToCross(const VECTOR4& v);							// Berechnet das Kreuzprodukt und übernimmt das Ergebnis
	VECTOR4				Cross(const D3DXVECTOR4& v)  const;					// Berechnet das Kreuzprodukt
	void				ToCross(const D3DXVECTOR4& v);						// Berechnet das Kreuzprodukt und übernimmt das Ergebnis
	*/
	void				Lerp( const VECTOR4 &v, const float s ) const;		// Führt eine lineare Interpolation durch
	VECTOR4				GetLerped( const VECTOR4 &v, const float s ) const;	// Führt eine lineare Interpolation durch

	void				Maximise( const VECTOR4 &v );						// Übernimmt die größten Komponenten beider Vektoren
	VECTOR4				GetMaximised( const VECTOR4 &v ) const;				// Liefert einen Vektor der größten Komponenten
	void				Minimise( const VECTOR4 &v );						// Übernimmt die kleinsten Komponenten beider Vektoren
	VECTOR4				GetMinimised( const VECTOR4 &v ) const;				// Liefert einen Vektor der kleinsten Komponenten

	void				Scale( const float s );								// Skaliert den Vektor
	VECTOR4				GetScaled( const float s ) const;					// Liefert den skalierten Vektor zurück

	void				Add( const VECTOR4 &v );							// Addiert den Vektor
	VECTOR4				GetAdded( const VECTOR4 &v ) const;					// Liefert den resultierenden Vektor der Addition
	void				Subtract( const VECTOR4 &v );						// Subtrahiert den Vektor
	VECTOR4				GetSubtracted( const VECTOR4 &v ) const;			// Liefert den resultierenden Vektor der Addition

	void				Transform( const MATRIX4 &m );						// Transformiert den Vektor (x,y,0,1) und übernimmt die X- und Y-Komponente
	VECTOR4				GetTransformed( const MATRIX4 &m ) const;			// Liefert den transformierten Vektor

	void				BaryCentric( const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const float f, const float g );				// Berechnet einen Punkt in baryzentrischen Koordinaten
	VECTOR4				GetBaryCentric( const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const float f, const float g ) const;

	void				CatmullRom( const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const VECTOR4 &v4, const float s );			// Führt eine Catmull-Rom-Interpolation durch und behält das Ergebnis
	VECTOR4				GetCatmullRom( const VECTOR4 &v1, const VECTOR4 &v2, const VECTOR4 &v3, const VECTOR4 &v4, const float s ) const;	// Liefert dieses Ergebnis zurück
	void				Hermite( const VECTOR4 &v1, const VECTOR4 &t1, const VECTOR4 &v2, const VECTOR4 &t2, const float s );				// Führt eine Catmull-Rom-Interpolation durch und behält das Ergebnis
	VECTOR4				GetHermite( const VECTOR4 &v1, const VECTOR4 &t1, const VECTOR4 &v2, const VECTOR4 &t2, const float s ) const;		// Liefert dieses Ergebnis zurück

	// TODO: Projektion für Vektor4
	void				Project(VECTOR4& pV, D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world);		// Object space to Screen Space
	void				Project(D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world);
	VECTOR4				GetProjected(D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world)  const;
	void				Unproject(VECTOR4& pV, D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world);	// Screen space to object space
	void				Unproject(D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world);
	VECTOR4				GetUnprojected(D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world) const;
};


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef VECTOR4					*LPVECTOR4;
typedef VECTOR4					POINT4;
typedef VECTOR4					*LPPOINT4;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 VECTOR4		VECTOR4A16;
typedef _ALIGN_16 VECTOR4		*LPVECTOR4A16;
typedef _ALIGN_16 VECTOR4		POINT4A16;
typedef _ALIGN_16 VECTOR4		*LPPOINT4A16;

typedef _ALIGN_32 VECTOR4		VECTOR4A32;
typedef _ALIGN_32 VECTOR4		*LPVECTOR4A32;
typedef _ALIGN_32 VECTOR4		POINT4A32;
typedef _ALIGN_32 VECTOR4		*LPPOINT4A32;

typedef _CACHEALIGN VECTOR4		VECTOR4AC;
typedef _CACHEALIGN VECTOR4		*LPVECTOR4AC;
typedef _CACHEALIGN VECTOR4		POINT4AC;
typedef _CACHEALIGN VECTOR4		*LPPOINT4AC;*/