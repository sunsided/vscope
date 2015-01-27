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

	Dateiname:		vector3.h
	Beschreibung:	3D-Vektor Definition
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:37

	Changelog:
	[1]		04. Juli 2002 23:37

===========================================================================*/

#pragma once

#ifndef VECTOR3_DEFINED
#define VECTOR3_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "define-vectorops.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct MATRIX4;
struct VECTOR2;
struct VECTOR4;

/*---------------------------------------------------------------------------
	Struktur für den 3D-Vektor
---------------------------------------------------------------------------*/
typedef struct VECTOR3 {
//:: Die Membervariablen ....................................................
public:		
	union {
		struct { float x, y, z; };
		float v[3];
	};

//:: Die Konstruktoren ......................................................
public:
						VECTOR3();
						VECTOR3(const VECTOR3 &inVec);
						VECTOR3(const VECTOR3 *inVec);
						VECTOR3(const float inx, const float iny, const float inz);
						VECTOR3(const float *inv);
						VECTOR3(const VECTOR2 &inVec);
						VECTOR3(const VECTOR2 *inVec);
						VECTOR3(const VECTOR4 &inVec);
						VECTOR3(const VECTOR4 *inVec);
						VECTOR3(const D3DXVECTOR3 &inVec);
						VECTOR3(const D3DXVECTOR3 *inVec);

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
    operator			float* () const;
    operator			const float* () const;
    operator			D3DXVECTOR3 () const;
    operator			const D3DXVECTOR3 () const;
    operator			VECTOR2 () const;
    operator			const VECTOR2 () const;
    operator			VECTOR4 () const;
    operator			const VECTOR4 () const;

	// Operatoren: Zuweisung ................................................
    VECTOR3&			operator += ( const VECTOR3 &v );
	VECTOR3&			operator += ( const D3DXVECTOR3 &v );
	VECTOR3&			operator -= ( const VECTOR3 &v );
	VECTOR3&			operator -= ( const D3DXVECTOR3 &v );
    VECTOR3&			operator *= ( float f );
	VECTOR3&			operator *= ( const MATRIX4& m );
    VECTOR3&			operator /= ( float f );
	// TODO: Cross für Vektor3
	VECTOR3&			operator ^= ( const VECTOR3& Vector);	// Cross
	VECTOR3&			operator =	( const VECTOR3 &v );
	VECTOR3&			operator =	( const D3DXVECTOR3 &v );

    // Operatoren: Unär .....................................................
    VECTOR3				operator + () const;
    VECTOR3				operator - () const;

    // Operatoren: Binär ....................................................
    VECTOR3				operator + ( const VECTOR3 &v ) const;
	VECTOR3				operator + ( const D3DXVECTOR3 &v ) const;
    VECTOR3				operator - ( const VECTOR3 &v ) const;
	VECTOR3				operator - ( const D3DXVECTOR3 &v ) const;
    VECTOR3				operator * ( float f ) const;
    VECTOR3				operator / ( float f ) const;
	float				operator DOT ( const VECTOR3& v ) const;
	float				operator DOT ( const D3DXVECTOR3& v ) const;
	VECTOR3				operator CROSS ( const VECTOR3 &b) const;
	VECTOR3				operator CROSS ( const D3DXVECTOR3 &b) const;
	friend VECTOR3		operator * ( float f, const VECTOR3 &v );

	// Operatoren: Vergleich ................................................
    bool				operator == ( const VECTOR3& ) const;
	bool				operator == ( const D3DXVECTOR3& ) const;
	bool				operator != ( const VECTOR3& ) const;
    bool				operator != ( const D3DXVECTOR3& ) const;

	// Funktionen: Zuweisung ................................................
	void				Assign( const float x, const float y, const float z );
	void				Assign( const float *v );
	void				Assign( const VECTOR3 &inVec );
	void				Assign( const VECTOR3 *inVec );
	void				Assign( const D3DXVECTOR3 &inVec );
	void				Assign( const D3DXVECTOR3 *inVec );
	void				Assign( const VECTOR2 &inVec );
	void				Assign( const VECTOR2 *inVec );
	void				Assign( const VECTOR4 &inVec );
	void				Assign( const VECTOR4 *inVec );

	// Funktionen: Einfach ..................................................
	void				Negate();											// Negiert den Vektor
	VECTOR3				GetNegated() const;									// Liefert den negierten Vektor
	float				GetMag() const;										// Gibt die Länge (Magnitude) des Vektors zurück
	float				GetMagSquared() const;								// Gibt die quadrierte Länge (Magnitude) des Vektors zurück
	float				GetLength() const;									// Gibt die Länge (Magnitude) des Vektors zurück
	float				GetLengthSquared() const;							// Gibt die quadrierte Länge (Magnitude) des Vektors zurück
	void				Normalize();										// Normalisiert den Vektor
	VECTOR3				GetNormalized() const;								// Liefert den normalisierten Vektor

	// Funktionen: Erweitert ................................................
	float				GetDistance( const VECTOR3 &v ) const;				// Liefert die Distanz zum gegebenen Vektor
	float				GetDistance( const D3DXVECTOR3 &v ) const;			// Liefert die Distanz zum gegebenen Vektor
	float				Dot( const VECTOR3 &v ) const;						// Berechnet das Punktprodukt
	float				Dot( const D3DXVECTOR3 &v ) const;					// Berechnet das Punktprodukt
	// TODO: Cross für Vektor3
	VECTOR3				Cross(const VECTOR3& v)  const;						// Berechnet das Kreuzprodukt
	void				ToCross(const VECTOR3& v);							// Berechnet das Kreuzprodukt und übernimmt das Ergebnis
	VECTOR3				Cross(const D3DXVECTOR3& v)  const;					// Berechnet das Kreuzprodukt
	void				ToCross(const D3DXVECTOR3& v);						// Berechnet das Kreuzprodukt und übernimmt das Ergebnis
	void				Lerp( const VECTOR3 &v, const float s ) const;		// Führt eine lineare Interpolation durch
	VECTOR3				GetLerped( const VECTOR3 &v, const float s ) const;	// Führt eine lineare Interpolation durch

	void				Maximise( const VECTOR3 &v );						// Übernimmt die größten Komponenten beider Vektoren
	VECTOR3				GetMaximised( const VECTOR3 &v ) const;				// Liefert einen Vektor der größten Komponenten
	void				Minimise( const VECTOR3 &v );						// Übernimmt die kleinsten Komponenten beider Vektoren
	VECTOR3				GetMinimised( const VECTOR3 &v ) const;				// Liefert einen Vektor der kleinsten Komponenten

	void				Scale( const float s );								// Skaliert den Vektor
	VECTOR3				GetScaled( const float s ) const;					// Liefert den skalierten Vektor zurück

	void				Add( const VECTOR3 &v );							// Addiert den Vektor
	VECTOR3				GetAdded( const VECTOR3 &v ) const;					// Liefert den resultierenden Vektor der Addition
	void				Subtract( const VECTOR3 &v );						// Subtrahiert den Vektor
	VECTOR3				GetSubtracted( const VECTOR3 &v ) const;			// Liefert den resultierenden Vektor der Addition

	void				Transform( const MATRIX4 &m );						// Transformiert den Vektor (x,y,0,1) und übernimmt die X- und Y-Komponente
	VECTOR3				GetTransformed( const MATRIX4 &m ) const;			// Liefert den transformierten Vektor
	void				TransformCoord( const MATRIX4 &m );					// Transformiert den Vektor (x,y,0,1) und projiziert ihn zurück auf w
	VECTOR3				GetTransformCoord( const MATRIX4 &m ) const;		// Liefert den transformierten Vektor
	void				TransformNormal( const MATRIX4 &m );				// Transformiert die Vektornormale (x,y,0,0) und übernimmt das Ergebnis
	VECTOR3				GetTransformNormal( const MATRIX4 &m ) const;		// Liefert den transformierten Vektor

	void				BaryCentric( const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &v3, const float f, const float g );				// Berechnet einen Punkt in baryzentrischen Koordinaten
	VECTOR3				GetBaryCentric( const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &v3, const float f, const float g ) const;

	void				CatmullRom( const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &v3, const VECTOR3 &v4, const float s );			// Führt eine Catmull-Rom-Interpolation durch und behält das Ergebnis
	VECTOR3				GetCatmullRom( const VECTOR3 &v1, const VECTOR3 &v2, const VECTOR3 &v3, const VECTOR3 &v4, const float s ) const;	// Liefert dieses Ergebnis zurück
	void				Hermite( const VECTOR3 &v1, const VECTOR3 &t1, const VECTOR3 &v2, const VECTOR3 &t2, const float s );				// Führt eine Catmull-Rom-Interpolation durch und behält das Ergebnis
	VECTOR3				GetHermite( const VECTOR3 &v1, const VECTOR3 &t1, const VECTOR3 &v2, const VECTOR3 &t2, const float s ) const;		// Liefert dieses Ergebnis zurück

	// TODO: Projektion für Vektor3
	void				Project(VECTOR3& pV, D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world);		// Object space to Screen Space
	void				Project(D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world);
	VECTOR3				GetProjected(D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world)  const;
	void				Unproject(VECTOR3& pV, D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world);	// Screen space to object space
	void				Unproject(D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world);
	VECTOR3				GetUnprojected(D3DVIEWPORT9& pViewport, MATRIX4& projection, MATRIX4& view, MATRIX4& world) const;

	// Statische Membervariablen ............................................
	static const VECTOR3 Zero; // <0,0,0>
	static const VECTOR3 i; // <1,0,0>
	static const VECTOR3 j; // <0,1,0>
	static const VECTOR3 k; // <0,0,1>
} VECTOR3;


/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef VECTOR3					*LPVECTOR3;
typedef VECTOR3					POINT3;
typedef VECTOR3					*LPPOINT3;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 VECTOR3		VECTOR3A16;
typedef _ALIGN_16 VECTOR3		*LPVECTOR3A16;
typedef _ALIGN_16 VECTOR3		POINT3A16;
typedef _ALIGN_16 VECTOR3		*LPPOINT3A16;

typedef _ALIGN_32 VECTOR3		VECTOR3A32;
typedef _ALIGN_32 VECTOR3		*LPVECTOR3A32;
typedef _ALIGN_32 VECTOR3		POINT3A32;
typedef _ALIGN_32 VECTOR3		*LPPOINT3A32;

typedef _CACHEALIGN VECTOR3		VECTOR3AC;
typedef _CACHEALIGN VECTOR3		*LPVECTOR3AC;
typedef _CACHEALIGN VECTOR3		POINT3AC;
typedef _CACHEALIGN VECTOR3		*LPPOINT3AC;*/