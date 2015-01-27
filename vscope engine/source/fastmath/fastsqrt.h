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

	Dateiname:		fastsqrt.h
	Beschreibung:	Fastmath-Header für Wurzelberechnungen, intrinsisch
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:31

	Changelog:
	[1]		04. Juli 2002 23:06
			Erstellt

===========================================================================*/

#pragma once

#ifndef FASTSQRT_DEFINED
#define FASTSQRT_DEFINED
#endif

#include <math.h>
#include "..\defines.h"

#pragma intrinsic(sqrt)

/*------------------------------------------------------------
/|	Funktion:		fastisqrt()
/|	Beschreibung:	Berechnet die inverse Wurzel von x
/|	Parameter:		x (float)
/|	Rückgabe:		float
/|  2002-07-04 23:07 MMT
/+------------------------------------------------------------*/
#ifndef _DEBUG
VSINLINE __declspec(deprecated) float fastisqrt(const float x) {
	return 1.f/(float)sqrt((double)x);
}
#else
VSINLINE __declspec(naked) float __fastcall fastisqrt(const float x) {
	__asm {
		mov		eax, 0be6eb508h
		mov		dword ptr[esp-12],03fc00000h
		sub		eax, dword ptr[esp + 4]
		sub		dword ptr[esp+4], 800000h
		shr		eax, 1
		mov		dword ptr[esp -  8], eax

		fld		dword ptr[esp -  8]
		fmul	st, st
		fld		dword ptr[esp -  8]
		fxch	st(1)
		fmul	dword ptr[esp +  4]
		fld		dword ptr[esp - 12]
		fld		st(0)
		fsub	st,st(2)

		fld		st(1)
		fxch	st(1)
		fmul	st(3),st
		fmul	st(3),st
		fmulp	st(4),st
		fsub	st,st(2)

		fmul	st(2),st
		fmul	st(3),st
		fmulp	st(2),st
		fxch	st(1)
		fsubp	st(1),st

		fmulp	st(1), st
		ret 4
	}
}
#endif

/*------------------------------------------------------------
/|	Funktion:		fastisqrt()
/|	Beschreibung:	Berechnet die inverse Wurzel von x
/|	Parameter:		x (double)
/|	Rückgabe:		float
/|  2002-07-04 23:07 MMT
/+------------------------------------------------------------*/
VSINLINE __declspec(deprecated) float fastisqrt(const double x) {
	return 1.f/(float)sqrt(x);
}

/*------------------------------------------------------------
/|	Funktion:		fastisqrtd()
/|	Beschreibung:	Berechnet die inverse Wurzel von x
/|	Parameter:		x (float)
/|	Rückgabe:		double
/|  2002-07-04 23:07 MMT
/+------------------------------------------------------------*/
VSINLINE __declspec(deprecated) double fastisqrtd(const float x) {
	return 1.f/sqrt((double)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastisqrtd()
/|	Beschreibung:	Berechnet die inverse Wurzel von x
/|	Parameter:		x (double)
/|	Rückgabe:		double
/|  2002-07-04 23:07 MMT
/+------------------------------------------------------------*/
VSINLINE __declspec(deprecated) double fastisqrtd(const double& x) {
	return 1.f/sqrt(x);
}

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fastsqrt()
/|	Beschreibung:	Berechnet die Wurzel von x
/|	Parameter:		x (float)
/|	Rückgabe:		float
/|  2002-07-04 23:07 MMT
/+------------------------------------------------------------*/
#ifndef _DEBUG
VSINLINE float fastsqrt(const float x) {
	return (float)sqrt((double)x);
}
#else
VSINLINE float fastsqrt(const float x) {
	//return x * fastisqrt(x);
	return (float)sqrt((double)x);
}
#endif

/*------------------------------------------------------------
/|	Funktion:		fastsqrt()
/|	Beschreibung:	Berechnet die Wurzel von x
/|	Parameter:		x (double)
/|	Rückgabe:		float
/|  2002-07-04 23:07 MMT
/+------------------------------------------------------------*/
VSINLINE float fastsqrt(const double& x) {
	return (float)sqrt(x);
}

/*------------------------------------------------------------
/|	Funktion:		fastsqrtd()
/|	Beschreibung:	Berechnet die Wurzel von x
/|	Parameter:		x (float)
/|	Rückgabe:		double
/|  2002-07-04 23:07 MMT
/+------------------------------------------------------------*/
VSINLINE double fastsqrtd(const float x) {
	return sqrt((double)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastsqrtd()
/|	Beschreibung:	Berechnet die Wurzel von x
/|	Parameter:		x (double)
/|	Rückgabe:		double
/|  2002-07-04 23:07 MMT
/+------------------------------------------------------------*/
VSINLINE double fastsqrtd(const double& x) {
	return sqrt(x);
}