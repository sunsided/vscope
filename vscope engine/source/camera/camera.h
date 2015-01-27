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

	Dateiname:		camera.h
	Beschreibung:	Viewcone Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 00:57

	Changelog:
	[1]		10. Juli 2002 00:57
			Erstellt

===========================================================================*/

#pragma once

#ifndef CAMERA_DEFINED
#define CAMERA_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vektoren\vector3.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct MATRIX4;

/*---------------------------------------------------------------------------
	Strukturen für die Vertices
---------------------------------------------------------------------------*/
class CAMERA {
//:: Die Membervariablen ....................................................
protected:
		VECTOR3			vRotation;		// temp. Rotationswinkel	(Obj-XYZ)		
public:
		VECTOR3			vDirection;		// Vorwärtsvektor	(Objekt-Z)
		VECTOR3			vRight;			// Rechtsvektor		(Objekt-X)
		VECTOR3			vUp;			// Hochvektor		(Objekt-Y)
		VECTOR3			vPosition;		// Positionsvektor	(Welt-XYZ)
private:
		VECTOR3			vRotationAngles;	// Rotationswinkel

//:: Die Konstruktoren ......................................................
public:
						CAMERA(void);
						CAMERA(const VECTOR3 *Position);
						CAMERA(const VECTOR3 &Position);
						CAMERA(const VECTOR3 *Position, const VECTOR3 *Rotation);
						CAMERA(const VECTOR3 &Position, const VECTOR3 &Rotation);
						CAMERA(const VECTOR3 &Direction, const VECTOR3 &Right, const VECTOR3 &Up);

private:
	void				Initialize();
		
//:: Das Interface ..........................................................
public:
	// Funktionen: Einfach ..................................................
	void				ToRotateX(const float value);		// Rotiert die Kamera um ihre X-Achse
	void				ToRotateY(const float value);		// Rotiert die Kamera um ihre Y-Achse
	void				ToRotateZ(const float value);		// Rotiert die Kamera um ihre Z-Achse
	CAMERA				RotateX(const float value);			// Diese Kamera, um die X-Achse rotiert
	CAMERA				RotateY(const float value);			// Diese Kamera, um die Y-Achse rotiert
	CAMERA				RotateZ(const float value);			// Diese Kamera, um die Z-Achse rotiert

	void				AddRotationX(const float value);	// Speichert den Wert für die spätere Rotation
	void				AddRotationY(const float value);	// Speichert den Wert für die spätere Rotation
	void				AddRotationZ(const float value);	// Speichert den Wert für die spätere Rotation
	void				ToRotate(const float x, const float y, const float z);	// Rotiert die Kamera um die gegebenen Werte
	void				ToRotate();							// Rotiert die Kamera um die gegebenen Werte
	CAMERA				Rotate(const float x, const float y, const float z);	// Rotiert die Kamera um die gespeicherten Werte
	CAMERA				Rotate();							// Liefert die um die gespeicherten Werte rotierte Kamera

	void				ToMoveDirection(const float value);	// Bewegt die Kamera entlang des Richtungsvektors
	void				ToMoveRight(const float value);		// Bewegt die Kamera entlang des Rechtsvektors
	void				ToMoveUp(const float value);		// Bewegt die Kamera entlang des Hochvektors

	void				ToMoveObjectX(const float value);	// Bewegt die Kamera entlang ihrer X-Achse
	void				ToMoveObjectY(const float value);	// Bewegt die Kamera entlang ihrer Y-Achse
	void				ToMoveObjectZ(const float value);	// Bewegt die Kamera entlang ihrer Z-Achse

	void				ToMoveWorldX(const float value);	// Bewegt die Kamera entlang ihrer X-Achse
	void				ToMoveWorldY(const float value);	// Bewegt die Kamera entlang ihrer Y-Achse
	void				ToMoveWorldZ(const float value);	// Bewegt die Kamera entlang ihrer Z-Achse

	MATRIX4				ViewMatrix();						// Liefert die berechnet View-Matrix der Kamera
	void				ViewMatrix(MATRIX4 *out_Matrix);	// Liefert die berechnet View-Matrix der Kamera
	void				ViewMatrixSetzen(LPDIRECT3DDEVICE9 in_Device);	// Berechnet und setzt die View-Matrix

	void				Normalize();						// Normalisiert die Vektoren
	void				ResetRotation();					// Setzt die Rotationswerte zurück

	void				ToPosition(const float x, const float y, const float z);	// Setzt die Kamera an die Weltkoordinaten x,y,z
	void				ToPosition(const VECTOR3 *Position);						// Setzt die Kamera an die Weltkoordinaten x,y,z
	void				ToPosition(const VECTOR3 &Position);						// Setzt die Kamera an die Weltkoordinaten x,y,z

	float				GetRotationX() const;				// Liefert die Rotation um die X-Achse in Radians
	float				GetRotationY() const;				// Liefert die Rotation um die Y-Achse in Radians
	float				GetRotationZ() const;				// Liefert die Rotation um die Z-Achse in Radians
	VECTOR3				GetDirectionVec() const;			// Liefert den Richtungsvektor (Objekt-Z)
	VECTOR3				GetUpVec() const;					// Liefert den Hochvektor (Objekt-Y)
	VECTOR3				GetRightVec() const;				// Liefert den Rechtsvektor (Objekt-X)
	void				GetDirectionVec(VECTOR3 *Vektor) const;	// Liefert den Richtungsvektor (Objekt-Z)
	void				GetUpVec(VECTOR3 *Vektor) const;			// Liefert den Hochvektor (Objekt-Y)
	void				GetRightVec(VECTOR3 *Vektor) const;		// Liefert den Rechtsvektor (Objekt-X)

};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef CAMERA					*LPCAMERA;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 CAMERA		CAMERAA16;
typedef _ALIGN_16 CAMERA		*LPCAMERAA16;

typedef _ALIGN_32 CAMERA		CAMERAA32;
typedef _ALIGN_32 CAMERA		*LPCAMERAA32;

typedef _CACHEALIGN CAMERA		CAMERAAC;
typedef _CACHEALIGN CAMERA		*LPCAMERAAC;*/