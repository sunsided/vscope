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

	Dateiname:		circularcontroller.inl.h
	Beschreibung:	Circular Controller 2D Inline Definition
	Revision:		1
	Erstellt:		MMT, 16. Oktober 2002 22:35

	Changelog:
	[1]		16. Oktober 2002 22:35

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-windows.h"
#include "..\fastmath\fasttrig.h"
#include "..\fastmath\fastfabs.h"
#include "..\fastmath\fastassort.h"
#include "..\vektoren\vector2.inl.h"
#include "circularcontroller.h"

/*------------------------------------------------------------
/|	Funktion:		CalculatePosition()
/|	Beschreibung:	Berechnet die aktuelle Schlittenposition aus
/|					dem gegebenen Winkel			
/|	Rückgabe:		n/a
/|  2002-10-13 22:57 MMT
/+------------------------------------------------------------*/
VSINLINE void CIRCULARCONTROLLER2D::CalculatePosition() {
	vPosition.x = fastcos(fAngle)*this->fRadius + vCenter.x ;
	vPosition.y = fastsin(fAngle)*this->fRadius + vCenter.y;
	vPosition.z = vCenter.z;
}


/*------------------------------------------------------------
/|	Funktion:		Init()
/|	Beschreibung:	Initialisiert das System
/|	Rückgabe:		n/a
/|  2002-10-13 22:57 MMT
/+------------------------------------------------------------*/
VSINLINE void CIRCULARCONTROLLER2D::Init(const VECTOR3 vCenter, const float fRadius, const float fSpeed) {
	this->vCenter = vCenter;
	this->fRadius = fRadius;
	this->fSpeed = fSpeed;
	this->fAngleStep = 0.01f * fSpeed;
}

/*------------------------------------------------------------
/|	Funktion:		Update()
/|	Beschreibung:	Aktualisiert das System
/|	Rückgabe:		n/a
/|  2002-10-13 22:57 MMT
/+------------------------------------------------------------*/
VSINLINE void CIRCULARCONTROLLER2D::Update() {
	this->fAngle += this->fAngleStep;
	if(fastfabs(this->fAngle) >= PIx2) fAngle = 0.f;
}


/*------------------------------------------------------------
/|	Funktion:		GetPosition()
/|	Beschreibung:	Liefert den richtigen Wert zurück
/|	Rückgabe:		n/a
/|  2002-10-13 22:57 MMT
/+------------------------------------------------------------*/
VSINLINE VECTOR3 CIRCULARCONTROLLER2D::GetPosition() {
	this->CalculatePosition();
	return vPosition;
}