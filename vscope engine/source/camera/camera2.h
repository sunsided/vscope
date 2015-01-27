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

	Dateiname:		camera2.h
	Beschreibung:	Kamera Header
	Revision:		1
	Erstellt:		MMT, 07. Juni 2003 06:49

	Changelog:
	[1]		07. Juni 2003 06:49
			Erstellt

===========================================================================*/

#pragma once

#ifndef CAMERA2_DEFINED
#define CAMERA2_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\vektoren\vector3.h"
#include "..\matrix\matrix4.h"
#include "..\piped3d2\piped3d2.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct QUATERNION;

/*---------------------------------------------------------------------------
	Strukturen für die Vertices
---------------------------------------------------------------------------*/
class CAMERA2 {
//:: Die Membervariablen ....................................................
protected:
		VECTOR3			m_vDirection;		// Vorwärtsvektor	(Objekt-Z)
		VECTOR3			m_vRight;			// Rechtsvektor		(Objekt-X)
		VECTOR3			m_vUp;				// Hochvektor		(Objekt-Y)
		VECTOR3			m_vPosition;		// Positionsvektor	(Welt-XYZ)
private:
		LPPIPED3D2		m_pPipe;			// Die Pipeline

//:: Die Konstruktoren ......................................................
public:
						CAMERA2(PIPED3D2 &in_pPipe);
						CAMERA2(const VECTOR3 &in_vPosition, PIPED3D2 &in_pPipe);
						CAMERA2(const VECTOR3 &in_vPosition, const VECTOR3 &in_vRotation, PIPED3D2 &in_pPipe);
						CAMERA2(const VECTOR3 &in_vDirection, const VECTOR3 &in_vRight, const VECTOR3 &in_vUp, PIPED3D2 &in_pPipe);
						CAMERA2(const VECTOR3 &in_vPosition, const VECTOR3 &in_vDirection, const VECTOR3 &in_vRight, const VECTOR3 &in_vUp, PIPED3D2 &in_pPipe);

private:
	void				Initialize();
	
//:: Das Interface ..........................................................
public:
	// Funktionen: relative Rotation: Object Space ..........................
	void				RotateObjectX(const float in_fXvalue);
	void				RotateObjectY(const float in_fYvalue);
	void				RotateObjectZ(const float in_fZvalue);
	void				RotateObjectXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue);
	void				RotateObjectXYZ(const VECTOR3 &in_vValues);
	void				RotateObjectAxisAngle(const VECTOR3 &in_vAxis, const float in_fAngle);
	void				RotateObjectAxisAngle(const QUATERNION &in_AxisAngle);
	// Funktionen: relative Rotation: World Space ...........................
	void				RotateWorldX(const float in_fXvalue);
	void				RotateWorldY(const float in_fYvalue);
	void				RotateWorldZ(const float in_fZvalue);
	void				RotateWorldXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue);
	void				RotateWorldXYZ(const VECTOR3 &in_vValues);
	void				RotateWorldAxisAngle(const VECTOR3 &in_vAxis, const float in_fAngle);
	void				RotateWorldAxisAngle(const QUATERNION &in_AxisAngle);
	// Funktionen: absolute Rotation: Object Space ..........................
	void				RotateToObjectX(const float in_fXvalue);
	void				RotateToObjectY(const float in_fYvalue);
	void				RotateToObjectZ(const float in_fZvalue);
	void				RotateToObjectXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue);
	void				RotateToObjectXYZ(const VECTOR3 &in_vValues);
	void				RotateToObjectAxisAngle(const VECTOR3 &in_vAxis, const float in_fAngle);
	void				RotateToObjectAxisAngle(const QUATERNION &in_AxisAngle);
	// Funktionen: absolute Rotation: World Space ...........................
	void				RotateToWorldX(const float in_fXvalue);
	void				RotateToWorldY(const float in_fYvalue);
	void				RotateToWorldZ(const float in_fZvalue);
	void				RotateToWorldXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue);
	void				RotateToWorldXYZ(const VECTOR3 &in_vValues);
	void				RotateToWorldAxisAngle(const VECTOR3 &in_vAxis, const float in_fAngle);
	void				RotateToWorldAxisAngle(const QUATERNION &in_AxisAngle);

	// Funktionen: relative Translation: Object Space .......................
	void				TranslateObjectX(const float in_fRightValue);
	void				TranslateObjectY(const float in_fUpValue);
	void				TranslateObjectZ(const float in_fDirectionValue);
	void				TranslateObjectXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue);
	void				TranslateObjectXYZ(const VECTOR3 &in_vValues);
	// Funktionen: relative Translation: World Space ........................
	void				TranslateWorldX(const float in_fXvalue);
	void				TranslateWorldY(const float in_fYvalue);
	void				TranslateWorldZ(const float in_fZvalue);
	void				TranslateWorldXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue);
	void				TranslateWorldXYZ(const VECTOR3 &in_vValues);
	// Funktionen: absolute Translation: World Space ........................
	void				TranslateToWorldX(const float in_fXvalue);
	void				TranslateToWorldY(const float in_fYvalue);
	void				TranslateToWorldZ(const float in_fZvalue);
	void				TranslateToWorldXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue);
	void				TranslateToWorldXYZ(const VECTOR3 &in_vValues);

	// Funktionen: Zugriff und Werte ........................................

	float				GetObjectRotationX() const;				// Liefert die Objekt-Rotation um die Welt-X-Achse in Radians bez. X
	float				GetObjectRotationY() const;				// Liefert die Objekt-Rotation um die Welt-Y-Achse in Radians bez. Z
	float				GetObjectRotationZ() const;				// Liefert die Objekt-Rotation um die Welt-Z-Achse in Radians bez. X
	
	float				GetWorldRotationX() const;				// Liefert die Positions-Rotation um die Welt-X-Achse in Radians bez. X
	float				GetWorldRotationY() const;				// Liefert die Positions-Rotation um die Welt-Y-Achse in Radians bez. Z
	float				GetWorldRotationZ() const;				// Liefert die Positions-Rotation um die Welt-Z-Achse in Radians bez. X

	VECTOR3				GetObjectDirectionVec() const;			// Liefert den Richtungsvektor (Objekt-Z)
	void				GetObjectDirectionVec(VECTOR3 *out_vDir) const;	// Liefert den Richtungsvektor (Objekt-Z)
	VECTOR3				GetObjectUpVec() const;					// Liefert den Hochvektor (Objekt-Y)
	void				GetObjectUpVec(VECTOR3 *out_vUp) const;			// Liefert den Hochvektor (Objekt-Y)
	VECTOR3				GetObjectRightVec() const;				// Liefert den Rechtsvektor (Objekt-X)
	void				GetObjectRightVec(VECTOR3 *out_vRight) const;		// Liefert den Rechtsvektor (Objekt-X)
	VECTOR3				GetPosition() const;
	void				GetPosition(VECTOR3 *out_vPosition);

	// Funktionen: Erweiterte ...............................................

	void				Normalize();						// Normalisiert die Vektoren
	void				LookAt(const VECTOR3 &in_vTarget);

	// Funktionen: Pointer-Übernahme ........................................
	void				SetPipe(PIPED3D2 &in_pPipe);

	// Funktionen: View-Matrix ..............................................

	MATRIX4				GenerateViewMatrix();						// Liefert die berechnete View-Matrix der Kamera - ohne sie zu setzen
	void				GenerateViewMatrix(MATRIX4 *out_Matrix);	// Liefert die berechnete View-Matrix der Kamera - ohne sie zu setzen
	void				SetViewMatrix();							// Schickt die Viewmatrix an die Pipe
	void				SetViewMatrix(PIPED3D2 &in_pPipe);			// Schickt die Viewmatrix an eine Pipe

	// Funktionen: Billboard-Matrix .........................................

	MATRIX4				GenerateBillboardMatrix();						// Liefert die berechnete Billboard-Matrix
	void				GenerateBillboardMatrix(MATRIX4 *out_Matrix);	// Liefert die berechnete Billboard-Matrix

};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef CAMERA2					*LPCAMERA2;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 CAMERA2		CAMERA2A16;
typedef _ALIGN_16 CAMERA2		*LPCAMERA2A16;

typedef _ALIGN_32 CAMERA2		CAMERA2A32;
typedef _ALIGN_32 CAMERA2		*LPCAMERA2A32;

typedef _CACHEALIGN CAMERA2		CAMERA2AC;
typedef _CACHEALIGN CAMERA2		*LPCAMERA2AC;*/