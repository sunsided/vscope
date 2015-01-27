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

	Dateiname:		camera2.inl.h
	Beschreibung:	Kamera Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 07. Juni 2003 06:49

	Changelog:
	[1]		07. Juni 2003 06:49
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "camera2.h"
#include "..\vektoren\vector3.h"
#include "..\matrix\matrix4.h"
#include "..\quaternion\quaternion.h"

#include "..\matrix\matrix4.inl.h"
#include "..\vektoren\vector3.inl.h"

#pragma intrinsic(memset)

// Funktionen: relative Rotation: Object Space .............................

/*------------------------------------------------------------
/|	Funktion:		RotateObjectX()
/|	Beschreibung:	Rotiert um die Objekt-X-Achse (Rechtsvektor)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateObjectX(const float in_fXvalue) {
	if(in_fXvalue==0.f) return;
	MATRIX4 matRotX;
	QUATERNION Quat;
	Quat.Rotate(this->m_vRight, in_fXvalue);	// um den Rechtsvektor rotieren
	Quat.ToMatrix(&matRotX);
	this->m_vUp *= matRotX;
	this->m_vDirection *= matRotX;
}

/*------------------------------------------------------------
/|	Funktion:		RotateObjectY()
/|	Beschreibung:	Rotiert um die Objekt-Y-Achse (Hochvektor)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateObjectY(const float in_fYvalue) {
	if(in_fYvalue==0.f) return;
	MATRIX4 matRotY;
	QUATERNION Quat;
	Quat.Rotate(this->m_vUp, in_fYvalue);	// um den Hochsvektor rotieren
	Quat.ToMatrix(&matRotY);
	this->m_vRight *= matRotY;
	this->m_vDirection *= matRotY;
}

/*------------------------------------------------------------
/|	Funktion:		RotateObjectZ()
/|	Beschreibung:	Rotiert um die Objekt-Z-Achse (Vorwärtsvektor)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateObjectZ(const float in_fZvalue) {
	if(in_fZvalue==0.f) return;
	MATRIX4 matRotZ;
	QUATERNION Quat;
	Quat.Rotate(this->m_vDirection, in_fZvalue);	// um den Vorwärtsvektor rotieren
	Quat.ToMatrix(&matRotZ);
	this->m_vRight *= matRotZ;
	this->m_vUp *= matRotZ;
}

/*------------------------------------------------------------
/|	Funktion:		RotateObjectXYZ()
/|	Beschreibung:	Rotiert um die Objekt-X, -Y und -Z-Achsen
/|	Parameter:		Winkel x,y,z (3xfloat) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateObjectXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue) {
	MATRIX4 matRot;
	matRot.Rotate(in_fXvalue, in_fYvalue, in_fZvalue);
	this->m_vUp			*= matRot;
	this->m_vRight		*= matRot;
	this->m_vDirection	*= matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateObjectXYZ()
/|	Beschreibung:	Rotiert um die Objekt-X, -Y und -Z-Achsen
/|	Parameter:		Winkel (VECTOR3) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateObjectXYZ(const VECTOR3 &in_vValues) {
	MATRIX4 matRot;
	matRot.Rotate(in_vValues.x, in_vValues.y, in_vValues.z);
	this->m_vUp			*= matRot;
	this->m_vRight		*= matRot;
	this->m_vDirection	*= matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateObjectAxisAngle()
/|	Beschreibung:	Rotiert um die Objekt-X, -Y und -Z-Achsen
/|	Parameter:		Achse (VECTOR3), Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateObjectAxisAngle(const VECTOR3 &in_vAxis, const float in_fAngle) {
	QUATERNION quat;
	MATRIX4 matRot;
	quat.Rotate(in_vAxis, in_fAngle);
	quat.ToMatrix(&matRot);
	this->m_vUp			*= matRot;
	this->m_vRight		*= matRot;
	this->m_vDirection	*= matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateObjectAxisAngle()
/|	Beschreibung:	Rotiert um die Objekt-X, -Y und -Z-Achsen
/|	Parameter:		Achse und Winkel (QUATERNION) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateObjectAxisAngle(const QUATERNION &in_AxisAngle) {
	MATRIX4 matRot;
	in_AxisAngle.ToMatrix(&matRot);
	this->m_vUp			*= matRot;
	this->m_vRight		*= matRot;
	this->m_vDirection	*= matRot;
}


// Funktionen: relative Rotation: World Space ..............................

/*------------------------------------------------------------
/|	Funktion:		RotateWorldX()
/|	Beschreibung:	Rotiert um die Welt-X-Achse (Rechtsvektor)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:51 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateWorldX(const float in_fXvalue) {
	if(in_fXvalue==0.f) return;
	MATRIX4 matRotX;
	QUATERNION Quat;
	Quat.Rotate(VECTOR3::i, in_fXvalue);	// um den Rechtsvektor rotieren
	Quat.ToMatrix(&matRotX);
	this->m_vPosition *= matRotX;
}

/*------------------------------------------------------------
/|	Funktion:		RotateWorldY()
/|	Beschreibung:	Rotiert um die Welt-Y-Achse (Hochvektor)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:51 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateWorldY(const float in_fYvalue) {
	if(in_fYvalue==0.f) return;
	MATRIX4 matRotY;
	QUATERNION Quat;
	Quat.Rotate(VECTOR3::j, in_fYvalue);	// um den Hochvektor rotieren
	Quat.ToMatrix(&matRotY);
	this->m_vPosition *= matRotY;
}

/*------------------------------------------------------------
/|	Funktion:		RotateWorldZ()
/|	Beschreibung:	Rotiert um die Welt-Z-Achse (Vorwärtsvektor)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:51 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateWorldZ(const float in_fZvalue) {
	if(in_fZvalue==0.f) return;
	MATRIX4 matRotZ;
	QUATERNION Quat;
	Quat.Rotate(VECTOR3::k, in_fZvalue);	// um den Vorwärtsvektor rotieren
	Quat.ToMatrix(&matRotZ);
	this->m_vPosition *= matRotZ;
}

/*------------------------------------------------------------
/|	Funktion:		RotateWorldXYZ()
/|	Beschreibung:	Rotiert um die Welt-X, -Y und -Z-Achsen
/|	Parameter:		Winkel x,y,z (3xfloat) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:52 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateWorldXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue) {
	MATRIX4 matRot;
	matRot.Rotate(in_fXvalue, in_fYvalue, in_fZvalue);
	this->m_vPosition	*= matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateWorldXYZ()
/|	Beschreibung:	Rotiert um die Welt-X, -Y und -Z-Achsen
/|	Parameter:		Winkel (VECTOR3) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:52 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateWorldXYZ(const VECTOR3 &in_vValues) {
	MATRIX4 matRot;
	matRot.Rotate(in_vValues.x, in_vValues.y, in_vValues.z);
	this->m_vPosition	*= matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateWorldAxisAngle()
/|	Beschreibung:	Rotiert um eine beliebige Off-Center-Achse
/|	Parameter:		Achse (VECTOR3), Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:52 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateWorldAxisAngle(const VECTOR3 &in_vAxis, const float in_fAngle) {
	QUATERNION quat;
	MATRIX4 matRot;
	quat.Rotate(in_vAxis, in_fAngle);
	quat.ToMatrix(&matRot);
	this->m_vPosition	*= matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateWorldAxisAngle()
/|	Beschreibung:	Rotiert um eine beliebige Off-Center-Achse
/|	Parameter:		Achse und Winkel (QUATERNION) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:52 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateWorldAxisAngle(const QUATERNION &in_AxisAngle) {
	MATRIX4 matRot;
	in_AxisAngle.ToMatrix(&matRot);
	this->m_vPosition	*= matRot;
}



// Funktionen: absolute Rotation: Object Space .............................

/*------------------------------------------------------------
/|	Funktion:		RotateToObjectX()
/|	Beschreibung:	Rotiert um die Objekt-X-Achse (Rechtsvektor)
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToObjectX(const float in_fXvalue) {
	if(in_fXvalue==0.f) return;
	MATRIX4 matRotX;
	QUATERNION Quat;
	Quat.Rotate(this->m_vRight, in_fXvalue);	// um den Rechtsvektor rotieren
	Quat.ToMatrix(&matRotX);
	this->m_vUp = VECTOR3::j * matRotX;
	this->m_vDirection = VECTOR3::k * matRotX;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToObjectY()
/|	Beschreibung:	Rotiert um die Objekt-Y-Achse (Hochvektor)
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToObjectY(const float in_fYvalue) {
	if(in_fYvalue==0.f) return;
	MATRIX4 matRotY;
	QUATERNION Quat;
	Quat.Rotate(this->m_vUp, in_fYvalue);	// um den Hochsvektor rotieren
	Quat.ToMatrix(&matRotY);
	this->m_vRight = VECTOR3::i * matRotY;
	this->m_vDirection = VECTOR3::k * matRotY;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToObjectZ()
/|	Beschreibung:	Rotiert um die Objekt-Z-Achse (Vorwärtsvektor)
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToObjectZ(const float in_fZvalue) {
	if(in_fZvalue==0.f) return;
	MATRIX4 matRotZ;
	QUATERNION Quat;
	Quat.Rotate(this->m_vDirection, in_fZvalue);	// um den Vorwärtsvektor rotieren
	Quat.ToMatrix(&matRotZ);
	this->m_vRight = VECTOR3::i * matRotZ;
	this->m_vUp = VECTOR3::j * matRotZ;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToObjectXYZ()
/|	Beschreibung:	Rotiert um die Objekt-X, -Y und -Z-Achsen
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel x,y,z (3xfloat) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToObjectXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue) {
	MATRIX4 matRot;
	matRot.Rotate(in_fXvalue, in_fYvalue, in_fZvalue);
	this->m_vUp			= VECTOR3::j * matRot;
	this->m_vRight		= VECTOR3::i * matRot;
	this->m_vDirection	= VECTOR3::k * matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToObjectXYZ()
/|	Beschreibung:	Rotiert um die Objekt-X, -Y und -Z-Achsen
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel (VECTOR3) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToObjectXYZ(const VECTOR3 &in_vValues) {
	MATRIX4 matRot;
	matRot.Rotate(in_vValues.x, in_vValues.y, in_vValues.z);
	this->m_vUp			= VECTOR3::j * matRot;
	this->m_vRight		= VECTOR3::i * matRot;
	this->m_vDirection	= VECTOR3::k * matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToObjectAxisAngle()
/|	Beschreibung:	Rotiert um die Objekt-X, -Y und -Z-Achsen
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Achse (VECTOR3), Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToObjectAxisAngle(const VECTOR3 &in_vAxis, const float in_fAngle) {
	QUATERNION quat;
	MATRIX4 matRot;
	quat.Rotate(&in_vAxis, in_fAngle);
	quat.ToMatrix(&matRot);
	this->m_vUp			= VECTOR3::j * matRot;
	this->m_vRight		= VECTOR3::i * matRot;
	this->m_vDirection	= VECTOR3::k * matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToObjectAxisAngle()
/|	Beschreibung:	Rotiert um die Objekt-X, -Y und -Z-Achsen
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Achse und Winkel (QUATERNION) 
/|	Rückgabe:		n/a
/|  2002-06-07 07:33 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToObjectAxisAngle(const QUATERNION &in_AxisAngle) {
	MATRIX4 matRot;
	in_AxisAngle.ToMatrix(&matRot);
	this->m_vUp			= VECTOR3::j * matRot;
	this->m_vRight		= VECTOR3::i * matRot;
	this->m_vDirection	= VECTOR3::k * matRot;
}



// Funktionen: absolute Rotation: World Space ..............................


/*------------------------------------------------------------
/|	Funktion:		RotateToWorldX()
/|	Beschreibung:	Rotiert um die Welt-X-Achse (Rechtsvektor)
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:51 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToWorldX(const float in_fXvalue) {
	if(in_fXvalue==0.f) return;
	MATRIX4 matRotX;
	QUATERNION Quat;
	Quat.Rotate(this->m_vRight, in_fXvalue);	// um den Rechtsvektor rotieren
	Quat.ToMatrix(&matRotX);
	this->m_vPosition.y = (VECTOR3::j * matRotX).y;
	this->m_vPosition.z = (VECTOR3::k * matRotX).z;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToWorldY()
/|	Beschreibung:	Rotiert um die Welt-Y-Achse (Hochvektor)
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:51 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToWorldY(const float in_fYvalue) {
	if(in_fYvalue==0.f) return;
	MATRIX4 matRotY;
	QUATERNION Quat;
	Quat.Rotate(this->m_vUp, in_fYvalue);	// um den Hochsvektor rotieren
	Quat.ToMatrix(&matRotY);
	this->m_vPosition.x = (VECTOR3::i * matRotY).x;
	this->m_vPosition.z = (VECTOR3::k * matRotY).z;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToWorldZ()
/|	Beschreibung:	Rotiert um die Welt-Z-Achse (Vorwärtsvektor)
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:51 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToWorldZ(const float in_fZvalue) {
	if(in_fZvalue==0.f) return;
	MATRIX4 matRotZ;
	QUATERNION Quat;
	Quat.Rotate(this->m_vDirection, in_fZvalue);	// um den Vorwärtsvektor rotieren
	Quat.ToMatrix(&matRotZ);
	this->m_vPosition.x = (VECTOR3::i * matRotZ).x;
	this->m_vPosition.y = (VECTOR3::j * matRotZ).y;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToWorldXYZ()
/|	Beschreibung:	Rotiert um die Welt-X, -Y und -Z-Achsen
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel x,y,z (3xfloat) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:52 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToWorldXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue) {
	MATRIX4 matRot;
	matRot.Rotate(in_fXvalue, in_fYvalue, in_fZvalue);
	VECTOR3 vHelp;
	vHelp.x = vHelp.y = vHelp.z = 1.f;
	vHelp *= m_vPosition.GetMag();
	this->m_vPosition = vHelp * matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToWorldXYZ()
/|	Beschreibung:	Rotiert um die Welt-X, -Y und -Z-Achsen
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Winkel (VECTOR3) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:52 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToWorldXYZ(const VECTOR3 &in_vValues) {
	MATRIX4 matRot;
	matRot.Rotate(in_vValues.x, in_vValues.y, in_vValues.z);
	VECTOR3 vHelp;
	vHelp.x = vHelp.y = vHelp.z = 1.f;
	vHelp *= m_vPosition.GetMag();
	this->m_vPosition = vHelp * matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToWorldAxisAngle()
/|	Beschreibung:	Rotiert um eine beliebige Off-Center-Achse
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Achse (VECTOR3), Winkel (float) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:52 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToWorldAxisAngle(const VECTOR3 &in_vAxis, const float in_fAngle) {
	QUATERNION quat;
	MATRIX4 matRot;
	quat.Rotate(in_vAxis, in_fAngle);
	quat.ToMatrix(&matRot);
	VECTOR3 vHelp;
	vHelp.x = vHelp.y = vHelp.z = 1.f;
	vHelp *= m_vPosition.GetMag();
	this->m_vPosition = vHelp * matRot;
}

/*------------------------------------------------------------
/|	Funktion:		RotateToWorldAxisAngle()
/|	Beschreibung:	Rotiert um eine beliebige Off-Center-Achse
/|					auf den gegebenen Winkel (absolute Rotation)
/|	Parameter:		Achse und Winkel (QUATERNION) 
/|	Rückgabe:		n/a
/|  2002-06-07 11:52 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::RotateToWorldAxisAngle(const QUATERNION &in_AxisAngle) {
	MATRIX4 matRot;
	in_AxisAngle.ToMatrix(&matRot);
	VECTOR3 vHelp;
	vHelp.x = vHelp.y = vHelp.z = 1.f;
	vHelp *= m_vPosition.GetMag();
	this->m_vPosition = vHelp * matRot;
}


// Funktionen: relative Translation: Object Space .......................

/*------------------------------------------------------------
/|	Funktion:		TranslateObjectZ()
/|	Beschreibung:	Bewegt die Kamera entlang ihrer Z-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateObjectZ(const float in_fDirectionValue) {
	this->m_vPosition.x += this->m_vDirection.x * in_fDirectionValue;
	this->m_vPosition.y += this->m_vDirection.y * in_fDirectionValue;
	this->m_vPosition.z += this->m_vDirection.z * in_fDirectionValue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateObjectX()
/|	Beschreibung:	Bewegt die Kamera entlang ihrer X-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateObjectX(const float in_fRightValue) {
	this->m_vPosition.x += this->m_vRight.x * in_fRightValue;
	this->m_vPosition.y += this->m_vRight.y * in_fRightValue;
	this->m_vPosition.z += this->m_vRight.z * in_fRightValue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateObjectY()
/|	Beschreibung:	Bewegt die Kamera entlang ihrer Y-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateObjectY(const float in_fUpValue) {
	this->m_vPosition.x += this->m_vUp.x * in_fUpValue;
	this->m_vPosition.y += this->m_vUp.y * in_fUpValue;
	this->m_vPosition.z += this->m_vUp.z * in_fUpValue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateObjectXYZ()
/|	Beschreibung:	Bewegt die Kamera entlang ihrer X-, Y- und Z-Achse
/|	Parameter:		Strecken (3*float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateObjectXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue) {
	this->TranslateObjectX(in_fXvalue);
	this->TranslateObjectY(in_fYvalue);
	this->TranslateObjectZ(in_fZvalue);
}

/*------------------------------------------------------------
/|	Funktion:		TranslateObjectXYZ()
/|	Beschreibung:	Bewegt die Kamera entlang ihrer X-, Y- und Z-Achse
/|	Parameter:		Strecke (VECTOR3)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateObjectXYZ(const VECTOR3 &in_vValues) {
	this->TranslateObjectX(in_vValues.x);
	this->TranslateObjectY(in_vValues.y);
	this->TranslateObjectZ(in_vValues.z);
}


// Funktionen: relative Translation: World Space ........................

/*------------------------------------------------------------
/|	Funktion:		TranslateWorldX()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-X-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateWorldX(const float in_fXvalue) {
	this->m_vPosition.x += in_fXvalue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateWorldY()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-Y-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateWorldY(const float in_fYvalue) {
	this->m_vPosition.y += in_fYvalue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateWorldY()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-Y-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateWorldZ(const float in_fZvalue) {
	this->m_vPosition.z += in_fZvalue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateWorldXYZ()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-X, Y- und Z-Achse
/|	Parameter:		Strecken (3*float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateWorldXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue) {
	this->m_vPosition.x += in_fXvalue;
	this->m_vPosition.y += in_fYvalue;
	this->m_vPosition.z += in_fZvalue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateWorldXYZ()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-X, Y- und Z-Achse
/|	Parameter:		Strecken (VECTOR3)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateWorldXYZ(const VECTOR3 &in_vValues) {
	this->m_vPosition.x += in_vValues.x;
	this->m_vPosition.y += in_vValues.y;
	this->m_vPosition.z += in_vValues.z;
}

// Funktionen: absolute Translation: World Space ........................

/*------------------------------------------------------------
/|	Funktion:		TranslateToWorldX()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-X-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateToWorldX(const float in_fXvalue) {
	this->m_vPosition.x = in_fXvalue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateToWorldY()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-Y-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateToWorldY(const float in_fYvalue) {
	this->m_vPosition.y = in_fYvalue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateToWorldZ()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-Y-Achse
/|	Parameter:		Strecke (float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateToWorldZ(const float in_fZvalue) {
	this->m_vPosition.z = in_fZvalue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslatToeWorldXYZ()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-X, Y- und Z-Achse
/|	Parameter:		Strecken (3*float)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateToWorldXYZ(const float in_fXvalue, const float in_fYvalue, const float in_fZvalue) {
	this->m_vPosition.x = in_fXvalue;
	this->m_vPosition.y = in_fYvalue;
	this->m_vPosition.z = in_fZvalue;
}

/*------------------------------------------------------------
/|	Funktion:		TranslateToWorldXYZ()
/|	Beschreibung:	Bewegt die Kamera entlang der Welt-X, Y- und Z-Achse
/|	Parameter:		Strecken (VECTOR3)
/|	Rückgabe:		n/a
/|  2002-06-07 12:11 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::TranslateToWorldXYZ(const VECTOR3 &in_vValues) {
	this->m_vPosition.x = in_vValues.x;
	this->m_vPosition.y = in_vValues.y;
	this->m_vPosition.z = in_vValues.z;
}

// Funktionen: Zugriff und Werte ........................................

/*------------------------------------------------------------
/|	Funktion:		GetObjectDirectionVec()
/|	Beschreibung:	Liefert den Vorwärtsvektor
/|	Parameter:		n/a
/|	Rückgabe:		Vektor (VECTOR3)
/|  2002-06-07 12:23 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 CAMERA2::GetObjectDirectionVec() const {
	return this->m_vDirection;
}

/*------------------------------------------------------------
/|	Funktion:		GetObjectDirectionVec()
/|	Beschreibung:	Liefert den Vorwärtsvektor
/|	Parameter:		OUT: Vektor (VECTOR3)
/|	Rückgabe:		Vektor als Parameter
/|  2002-06-07 12:23 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::GetObjectDirectionVec(VECTOR3 *out_vDir) const {
	out_vDir->Assign(this->m_vDirection.x, this->m_vDirection.y, this->m_vDirection.z);
}

/*------------------------------------------------------------
/|	Funktion:		GetObjectUpVec()
/|	Beschreibung:	Liefert den Hochvektor
/|	Parameter:		n/a
/|	Rückgabe:		Vektor (VECTOR3)
/|  2002-06-07 12:23 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 CAMERA2::GetObjectUpVec() const {
	return this->m_vUp;
}

/*------------------------------------------------------------
/|	Funktion:		GetObjectUpVec()
/|	Beschreibung:	Liefert den Hochvektor
/|	Parameter:		OUT: Vektor (VECTOR3)
/|	Rückgabe:		Vektor als Parameter
/|  2002-06-07 12:23 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::GetObjectUpVec(VECTOR3 *out_vUp) const {
	out_vUp->Assign(this->m_vUp.x, this->m_vUp.y, this->m_vUp.z);
}

/*------------------------------------------------------------
/|	Funktion:		GetObjectRightVec()
/|	Beschreibung:	Liefert den Rechtsvektor
/|	Parameter:		n/a
/|	Rückgabe:		Vektor (VECTOR3)
/|  2002-06-07 12:23 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 CAMERA2::GetObjectRightVec() const {
	return this->m_vRight;
}

/*------------------------------------------------------------
/|	Funktion:		GetObjectRightVec()
/|	Beschreibung:	Liefert den Rechtsvektor
/|	Parameter:		OUT: Vektor (VECTOR3)
/|	Rückgabe:		Vektor als Parameter
/|  2002-06-07 12:23 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::GetObjectRightVec(VECTOR3 *out_vRight) const {
	out_vRight->Assign(this->m_vRight.x, this->m_vRight.y, this->m_vRight.z);
}

/*------------------------------------------------------------
/|	Funktion:		GetPosition()
/|	Beschreibung:	Liefert den Positionsvektor
/|	Parameter:		n/a
/|	Rückgabe:		Position (VECTOR3)
/|  2002-06-07 12:23 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 CAMERA2::GetPosition() const {
	return this->m_vPosition;
}

/*------------------------------------------------------------
/|	Funktion:		GetPosition()
/|	Beschreibung:	Liefert den Positionsvektor
/|	Parameter:		OUT: Position (VECTOR3)
/|	Rückgabe:		Position als Parameter
/|  2002-06-07 12:23 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::GetPosition(VECTOR3 *out_vPosition) {
	//out_vPosition->Assign(this->m_vPosition.x, this->m_vPosition.y, this->m_vPosition.z);
	out_vPosition->x = this->m_vPosition.x;
	out_vPosition->y = this->m_vPosition.y;
	out_vPosition->z = this->m_vPosition.z;
}



/*------------------------------------------------------------
/|	Funktion:		GetObjectRotationX()
/|	Beschreibung:	Liefert den Rotationswinkel um die X-Achse bez. Y
/|	Parameter:		n/a
/|	Rückgabe:		Winkel (float)
/|  2002-06-07 12:26 MMT
/+------------------------------------------------------------*/
VSINLINE float CAMERA2::GetObjectRotationX() const {
	/*
	float fAngle = fastfabs(fastatan(this->m_vUp.z / this->m_vUp.y));
	if(!ISZERO(m_vUp.y) && !ISZERO(m_vUp.z) && (this->m_vUp.y>0) && (this->m_vUp.y<0)) return fAngle+RAD360;
	if(!ISZERO(m_vUp.y) && (this->m_vUp.y<0)) return fAngle+PI;
	return fAngle;*/
	float fAngle = fastfabs(fastatan(this->m_vRight.z / this->m_vRight.y));
	if(ISZERO(this->m_vRight.y)) {
		if(this->m_vRight.z > 0.f) return RAD90;
		if(this->m_vRight.z < 0.f) return RAD270;
	}
	
	if(ISZERO(this->m_vRight.z)) {
		if(this->m_vRight.y > 0.f) return 0.f;
		if(this->m_vRight.y < 0.f) return RAD180;
	}
	
	if(this->m_vRight.y > 0.f) {
		if(this->m_vRight.z > 0.f)
			return fAngle;				// Quadrant 1
		else
			return (RAD360 - fAngle);	// Quadrant 4
	} else {
		if(this->m_vRight.z > 0.f) 
			return (RAD180 - fAngle);	// Quadrant 2
		else
			return (fAngle + RAD180);	// Quadrant 3
	}

	return fAngle;
}

/*------------------------------------------------------------
/|	Funktion:		GetObjectRotationY()
/|	Beschreibung:	Liefert den Rotationswinkel um die Y-Achse bez. X
/|	Parameter:		n/a
/|	Rückgabe:		Winkel (float)
/|  2002-06-07 12:26 MMT
/+------------------------------------------------------------*/
VSINLINE float CAMERA2::GetObjectRotationY() const {
	float fAngle = fastfabs(fastatan(this->m_vRight.z / this->m_vRight.x));
	if(ISZERO(this->m_vRight.x)) {
		if(this->m_vRight.z > 0.f) return RAD90;
		if(this->m_vRight.z < 0.f) return RAD270;
	}
	
	if(ISZERO(this->m_vRight.z)) {
		if(this->m_vRight.x > 0.f) return 0.f;
		if(this->m_vRight.x < 0.f) return RAD180;
	}
	
	if(this->m_vRight.x > 0.f) {
		if(this->m_vRight.z > 0.f)
			return fAngle;				// Quadrant 1
		else
			return (RAD360 - fAngle);	// Quadrant 4
	} else {
		if(this->m_vRight.z > 0.f) 
			return (RAD180 - fAngle);	// Quadrant 2
		else
			return (fAngle + RAD180);	// Quadrant 3
	}

	return fAngle;
}

/*------------------------------------------------------------
/|	Funktion:		GetObjectRotationZ()
/|	Beschreibung:	Liefert den Rotationswinkel um die Z-Achse bez. X
/|	Parameter:		n/a
/|	Rückgabe:		Winkel (float)
/|  2002-06-07 12:26 MMT
/+------------------------------------------------------------*/
VSINLINE float CAMERA2::GetObjectRotationZ() const {
	/*
	float fAngle = fastfabs(fastatan(this->m_vRight.y / this->m_vRight.x));
	if(!ISZERO(m_vRight.y) && !ISZERO(m_vRight.z) && (this->m_vRight.y>0) && (this->m_vRight.z<0)) return fAngle+RAD360;
	if(!ISZERO(m_vRight.y) && this->m_vRight.y<0) return fAngle+PI;
	return fAngle;*/
	float fAngle = fastfabs(fastatan(this->m_vRight.y / this->m_vRight.x));
	if(ISZERO(this->m_vRight.x)) {
		if(this->m_vRight.y > 0.f) return RAD90;
		if(this->m_vRight.y < 0.f) return RAD270;
	}
	
	if(ISZERO(this->m_vRight.y)) {
		if(this->m_vRight.x > 0.f) return 0.f;
		if(this->m_vRight.x < 0.f) return RAD180;
	}
	
	if(this->m_vRight.x > 0.f) {
		if(this->m_vRight.y > 0.f)
			return fAngle;				// Quadrant 1
		else
			return (RAD360 - fAngle);	// Quadrant 4
	} else {
		if(this->m_vRight.y > 0.f) 
			return (RAD180 - fAngle);	// Quadrant 2
		else
			return (fAngle + RAD180);	// Quadrant 3
	}

	return fAngle;
}


/*------------------------------------------------------------
/|	Funktion:		GetWorldRotationX()
/|	Beschreibung:	Liefert den Rotationswinkel des Objektes als ganzes um die X-Achse bez. Y
/|	Parameter:		n/a
/|	Rückgabe:		Winkel (float)
/|  2002-06-07 12:26 MMT
/+------------------------------------------------------------*/
VSINLINE float CAMERA2::GetWorldRotationX() const {
	/*
	float fAngle = fastfabs(fastatan(this->m_vPosition.z / this->m_vPosition.y));
	if(!ISZERO(m_vPosition.y) && !ISZERO(m_vPosition.z) && (this->m_vPosition.y>0) && (this->m_vPosition.z<0)) return fAngle+RAD360;
	if(!ISZERO(m_vPosition.y) && this->m_vPosition.y<0) return fAngle+PI;
	return fAngle;*/
	float fAngle = fastfabs(fastatan(this->m_vPosition.z / this->m_vPosition.y));
	if(ISZERO(this->m_vPosition.y)) {
		if(this->m_vPosition.z > 0.f) return RAD90;
		if(this->m_vPosition.z < 0.f) return RAD270;
	}
	
	if(ISZERO(this->m_vPosition.z)) {
		if(this->m_vPosition.y > 0.f) return 0.f;
		if(this->m_vPosition.y < 0.f) return RAD180;
	}
	
	if(this->m_vPosition.y > 0.f) {
		if(this->m_vPosition.z > 0.f)
			return fAngle;				// Quadrant 1
		else
			return (RAD360 - fAngle);	// Quadrant 4
	} else {
		if(this->m_vPosition.z > 0.f) 
			return (RAD180 - fAngle);	// Quadrant 2
		else
			return (fAngle + RAD180);	// Quadrant 3
	}

	return fAngle;
}

/*------------------------------------------------------------
/|	Funktion:		GetWorldRotationY()
/|	Beschreibung:	Liefert den Rotationswinkel des Objektes als ganzes um die Y-Achse bez. X
/|	Parameter:		n/a
/|	Rückgabe:		Winkel (float)
/|  2002-06-07 12:26 MMT
/+------------------------------------------------------------*/
VSINLINE float CAMERA2::GetWorldRotationY() const {
	/*
	float fAngle = fastfabs(fastatan(this->m_vPosition.z / this->m_vPosition.x));
	if(!ISZERO(m_vPosition.x) && !ISZERO(m_vPosition.z) && (this->m_vPosition.x>0) && (this->m_vPosition.z<0)) return fAngle+RAD360;
	if(!ISZERO(m_vPosition.x) && this->m_vPosition.x<0) return fAngle+PI;
	return fAngle;*/
	float fAngle = fastfabs(fastatan(this->m_vPosition.z / this->m_vPosition.x));
	if(ISZERO(this->m_vPosition.x)) {
		if(this->m_vPosition.z > 0.f) return RAD90;
		if(this->m_vPosition.z < 0.f) return RAD270;
	}
	
	if(ISZERO(this->m_vPosition.z)) {
		if(this->m_vPosition.x > 0.f) return 0.f;
		if(this->m_vPosition.x < 0.f) return RAD180;
	}
	
	if(this->m_vPosition.x > 0.f) {
		if(this->m_vPosition.z > 0.f)
			return fAngle;				// Quadrant 1
		else
			return (RAD360 - fAngle);	// Quadrant 4
	} else {
		if(this->m_vPosition.z > 0.f) 
			return (RAD180 - fAngle);	// Quadrant 2
		else
			return (fAngle + RAD180);	// Quadrant 3
	}

	return fAngle;
}

/*------------------------------------------------------------
/|	Funktion:		GetWorldRotationZ()
/|	Beschreibung:	Liefert den Rotationswinkel des Objektes als ganzes um die Z-Achse bez. X
/|	Parameter:		n/a
/|	Rückgabe:		Winkel (float)
/|  2002-06-07 12:26 MMT
/+------------------------------------------------------------*/
VSINLINE float CAMERA2::GetWorldRotationZ() const {
	/*
	float fAngle = fastfabs(fastatan(this->m_vPosition.y / this->m_vPosition.x));
	if(!ISZERO(m_vPosition.x) && !ISZERO(m_vPosition.y) && (this->m_vPosition.x>0) && (this->m_vPosition.y<0)) return fAngle+RAD360;
	if(!ISZERO(m_vPosition.x) && this->m_vPosition.x<0) return fAngle+PI;
	return fAngle;*/
	float fAngle = fastfabs(fastatan(this->m_vPosition.y / this->m_vPosition.x));
	if(ISZERO(this->m_vPosition.x)) {
		if(this->m_vPosition.y > 0.f) return RAD90;
		if(this->m_vPosition.y < 0.f) return RAD270;
	}
	
	if(ISZERO(this->m_vPosition.y)) {
		if(this->m_vPosition.x > 0.f) return 0.f;
		if(this->m_vPosition.x < 0.f) return RAD180;
	}
	
	if(this->m_vPosition.x > 0.f) {
		if(this->m_vPosition.y > 0.f)
			return fAngle;				// Quadrant 1
		else
			return (RAD360 - fAngle);	// Quadrant 4
	} else {
		if(this->m_vPosition.y > 0.f) 
			return (RAD180 - fAngle);	// Quadrant 2
		else
			return (fAngle + RAD180);	// Quadrant 3
	}

	return fAngle;
}

// Funktionen: Pointer-Übernahme ........................................

/*------------------------------------------------------------
/|	Funktion:		SetPipe()
/|	Beschreibung:	Speichert den Pipeline-Pointer
/|	Parameter:		PIPED3D2
/|	Rückgabe:		n/a
/|  2002-06-09 11:20 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::SetPipe(PIPED3D2 &in_pPipe) {
	this->m_pPipe = &in_pPipe;
}

// Funktionen: Billboard-Matrix .........................................

/*------------------------------------------------------------
/|	Funktion:		GenerateBillboardMatrix()
/|	Beschreibung:	Erzeugt eine Billboard-Rotationsmatrix
/|	Parameter:		n/a
/|	Rückgabe:		MATRIX4
/|  2002-06-09 12:27 MMT
/+------------------------------------------------------------*/
VSINLINE MATRIX4 CAMERA2::GenerateBillboardMatrix() {
	MATRIX4 matBillboard, matView, matTranspose;
	GenerateViewMatrix(&matView);
	matTranspose.Transpose(matView);
	matBillboard.Identity();
	matBillboard._11 = matTranspose._11;	matBillboard._12 = matTranspose._12;	matBillboard._13 = matTranspose._13;
	matBillboard._21 = matTranspose._21;	matBillboard._22 = matTranspose._22;	matBillboard._23 = matTranspose._23;
	matBillboard._31 = matTranspose._31;	matBillboard._32 = matTranspose._32;	matBillboard._33 = matTranspose._33;
	return matBillboard;
}

/*------------------------------------------------------------
/|	Funktion:		GenerateBillboardMatrix()
/|	Beschreibung:	Erzeugt eine Billboard-Rotationsmatrix
/|	Parameter:		out: Matrix (MATRIX4)
/|	Rückgabe:		n/a
/|  2002-06-09 12:27 MMT
/+------------------------------------------------------------*/
VSINLINE void CAMERA2::GenerateBillboardMatrix(MATRIX4 *out_Matrix) {
	MATRIX4 matView, matTranspose;
	GenerateViewMatrix(&matView);
	matTranspose.Transpose(matView);
	out_Matrix->Identity();
	out_Matrix->_11 = matTranspose._11;	out_Matrix->_12 = matTranspose._12;	out_Matrix->_13 = matTranspose._13;
	out_Matrix->_21 = matTranspose._21;	out_Matrix->_22 = matTranspose._22;	out_Matrix->_23 = matTranspose._23;
	out_Matrix->_31 = matTranspose._31;	out_Matrix->_32 = matTranspose._32;	out_Matrix->_33 = matTranspose._33;
}