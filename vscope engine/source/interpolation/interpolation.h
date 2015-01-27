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

	Dateiname:		interpolation.h
	Beschreibung:	Funktionen für float-Interpolation
	Revision:		1
	Erstellt:		MMT, 07. Juli 2002 14:55

	Changelog:
	[1]		07. Juli 2002 14:55
			Erstellt (lineare, Kosinus- und kubische Interpolation

===========================================================================*/

#pragma once

#ifndef INTERPOLATE_DEFINED
#define INTERPOLATE_DEFINED
#endif

#include <math.h>
#include "..\defines.h"
#include "..\fastmath\fasttrig.h"
#include "..\fastmath\fastassort.h"

namespace INTERPOLATION {

/*------------------------------------------------------------
/|	Funktion:		InterpolateLinear()
/|	Beschreibung:	Interpoliert linear zwischen a und b
/|	Parameter:		(float) a, b, x
/|	Benutzung:		a ist der Startwert, b der Endwert
/|					x ist eine Zahl 0..1, die den zu berechnenden
/|					Punkt zwischen a und b beschreibt.
/|					Für x=0 gilt f(x)=a, für x=1 --> f(x)=b.
/|	Pro/Con:		Die Funktion ist schnell, aber scharfkantig.
/|	Rückgabe:		float
/|  2002-07-07 16:39 MMT
/+------------------------------------------------------------*/
VSINLINE float InterpolateLinear(const float a, const float b, const float x) {
	return a*(1-x) + b*x;
}

/*------------------------------------------------------------
/|	Funktion:		InterpolateCosine()
/|	Beschreibung:	Kosinus-Interpolation zwischen a und b
/|	Parameter:		(float) a, b, x
/|	Benutzung:		a ist der Startwert, b der Endwert
/|					x ist eine Zahl 0..1, die den zu berechnenden
/|					Punkt zwischen a und b beschreibt.
/|					Für x=0 gilt f(x)=a, für x=1 --> f(x)=b.
/|	Pro/Con:		Die Funktion ist langsamer als interpolate_linear(),
/|					erzeugt aber weichere Ergebnisse.
/|	Rückgabe:		float
/|  2002-07-07 16:39 MMT
/+------------------------------------------------------------*/
VSINLINE float InterpolateCosine(const float a, const float b, const float x) {
	float ft = x * PI;
	float f = (1.f - fastcos(ft)) * 0.5f;
	return  a*(1.f-f) + b*f;
}

/*------------------------------------------------------------
/|	Funktion:		InterpolateCubic()
/|	Beschreibung:	Kubische Interpolation zwischen a und b
/|	Parameter:		(float) v1, a, b, vb, x
/|	Benutzung:		Die kubische Interpolation benötigt einen
/|					Wert vor a (va), a, b, und einen Wert nach b,
/|					und interpoliert mit dem gewohnten x zwischen
/|					a und b, wobei x=0 --> f(x)=a und x=1 --> f(x)=b.
/|	Pro/Con:		Die Funktion ist langsamer als interpolate_cosine(),
/|					erzeugt aber ein weitaus weicheres Ergebnis.
/|	Rückgabe:		float
/|  2002-07-07 16:39 MMT
/+------------------------------------------------------------*/
VSINLINE float InterpolateCubic(const float va, const float a, const float b, const float vb, const float x) {
	float f1 = va - a;
	float f2 = vb - b;
	float x2 = x * x;

	float P = (vb - b) - f1;			// (vb - b) - (va - a)
	float Q = (2.f * f1) - f2;			// (va - a) - P
	float R = b - va;					// b - va

	return P*x2*x + Q*x2 + R*x + a;		// Px³ + Qx² + Rx + S
}

} // namespace
using namespace INTERPOLATION;