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

	Dateiname:		fastexp.h
	Beschreibung:	Fastmath-Header für trigonometrisches, intrinsisch
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:31

	Changelog:
	[1]		04. Juli 2002 23:06
			Erstellt

===========================================================================*/

#pragma once

#ifndef FASTTRIG_DEFINED
#define FASTTRIG_DEFINED
#endif

#include <math.h>
#include "..\defines.h"

#pragma intrinsic(sin, cos, tan, asin, acos, atan, sinh, cosh, tanh)

/*------------------------------------------------------------
/|	Funktion:		fastsin()
/|	Beschreibung:	Berechnet den Sinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
#ifndef _DEBUG
VSINLINE float fastsin(const float a) {
	return (float)sin((double)a);
}
#else
VSINLINE __declspec(naked) float __fastcall fastsin(const float a) {
	__asm {
		fld		dword ptr[esp + 4] 
		fsin
		ret 4
	};
}
#endif

/*------------------------------------------------------------
/|	Funktion:		fastasin()
/|	Beschreibung:	Berechnet den Arkussinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-14 21:38 MMT
/+------------------------------------------------------------*/
/*VSINLINE float fastasin(const float a) {
	float fneg = -a;
	return (float)atan(fneg / fastsqrt(fneg * a + 1));
}*/

/*------------------------------------------------------------
/|	Funktion:		fastsin()
/|	Beschreibung:	Berechnet den Sinus eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastsin(const double a) {
	return (float)sin(a);
}

/*------------------------------------------------------------
/|	Funktion:		fastsind()
/|	Beschreibung:	Berechnet den Sinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastsind(const float a) {
	return sin((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fastsind()
/|	Beschreibung:	Berechnet den Sinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastsind(const double a) {
	return sin(a);
}

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fastcos()
/|	Beschreibung:	Berechnet den Kosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
#ifndef _DEBUG
VSINLINE float fastcos(const float a) {
	return (float)cos((double)a);
}
#else
VSINLINE __declspec(naked) float __fastcall fastcos(const float a) {
	__asm {
		fld		dword ptr[esp + 4] 
		fcos
		ret 4
	};
}
#endif


/*------------------------------------------------------------
/|	Funktion:		fastacos()
/|	Beschreibung:	Berechnet den Arkuskosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-14 21:38 MMT
/+------------------------------------------------------------*/
/*VSINLINE float fastacos(const float a) {
	float fneg = -a;
	return (float)atan(fneg / fastsqrt(fneg * a + 1)) + VAL2ATAN1;
}*/

/*------------------------------------------------------------
/|	Funktion:		fastcos()
/|	Beschreibung:	Berechnet den Kosinus eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastcos(const double a) {
	return (float)cos(a);
}

/*------------------------------------------------------------
/|	Funktion:		fastcosd()
/|	Beschreibung:	Berechnet den Kosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastcosd(const float a) {
	return cos((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fastcosd()
/|	Beschreibung:	Berechnet den Kosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastcosd(const double a) {
	return cos(a);
}

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fastasin()
/|	Beschreibung:	Berechnet den Arkussinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastasin(const float a) {
	return (float)asin((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fastasin()
/|	Beschreibung:	Berechnet den Arkussinus eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastasin(const double a) {
	return (float)asin(a);
}

/*------------------------------------------------------------
/|	Funktion:		fastasind()
/|	Beschreibung:	Berechnet den Arkussinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastasind(const float a) {
	return asin((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fastasind()
/|	Beschreibung:	Berechnet den Arkussinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastasind(const double a) {
	return asin(a);
}

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fastacos()
/|	Beschreibung:	Berechnet den Arkuskosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastacos(const float a) {
	return (float)acos((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fastacos()
/|	Beschreibung:	Berechnet den Arkuskosinus eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastacos(const double a) {
	return (float)acos(a);
}

/*------------------------------------------------------------
/|	Funktion:		fastacosd()
/|	Beschreibung:	Berechnet den Arkuskosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastacosd(const float a) {
	return acos((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fastacosd()
/|	Beschreibung:	Berechnet den Arkuskosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastacosd(const double a) {
	return acos(a);
}

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fasthsin()
/|	Beschreibung:	Berechnet den hyberbolischen Sinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fasthsin(const float a) {
	return (float)sinh((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthsin()
/|	Beschreibung:	Berechnet den hyberbolischen Sinus eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fasthsin(const double a) {
	return (float)sinh(a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthsind()
/|	Beschreibung:	Berechnet den hyberbolischen Sinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fasthsind(const float a) {
	return sinh((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthsind()
/|	Beschreibung:	Berechnet den hyberbolischen Sinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fasthsind(const double a) {
	return sinh(a);
}

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fasthcos()
/|	Beschreibung:	Berechnet den hyberbolischen Kosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fasthcos(const float a) {
	return (float)cosh((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthcos()
/|	Beschreibung:	Berechnet den hyberbolischen Kosinus eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fasthcos(const double a) {
	return (float)cosh(a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthcosd()
/|	Beschreibung:	Berechnet den hyberbolischen Kosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fasthcosd(const float a) {
	return cosh((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthcosd()
/|	Beschreibung:	Berechnet den hyberbolischen Kosinus eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fasthcosd(const double a) {
	return cosh(a);
}

/****************************************************************************************/

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fasttan()
/|	Beschreibung:	Berechnet den Tangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
#ifndef _DEBUG
VSINLINE float fasttan(const float a) {
	return (float)tan((double)a);
}
#else
VSINLINE float fasttan(const float a) {
	return (fastsin(a) / fastcos(a));
}
#endif

/*------------------------------------------------------------
/|	Funktion:		fasttan()
/|	Beschreibung:	Berechnet den Tangens eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fasttan(const double a) {
	return (float)tan(a);
}

/*------------------------------------------------------------
/|	Funktion:		fasttand()
/|	Beschreibung:	Berechnet den Tangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fasttand(const float a) {
	return tan((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fasttand()
/|	Beschreibung:	Berechnet den Tangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fasttand(const double a) {
	return tan(a);
}

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fastatan()
/|	Beschreibung:	Berechnet den Arkustangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastatan(const float a) {
	return (float)atan((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fastatan()
/|	Beschreibung:	Berechnet den Arkustangens eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastatan(const double a) {
	return (float)atan(a);
}

/*------------------------------------------------------------
/|	Funktion:		fastatand()
/|	Beschreibung:	Berechnet den Arkustangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastatand(const float a) {
	return atan((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fastatand()
/|	Beschreibung:	Berechnet den Arkustangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastatand(const double a) {
	return atan(a);
}

/****************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fasthtan()
/|	Beschreibung:	Berechnet den hyberbolischen Tangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fasthtan(const float a) {
	return (float)tanh((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthtan()
/|	Beschreibung:	Berechnet den hyberbolischen Tangens eines Winkels a
/|	Parameter:		a (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fasthtan(const double a) {
	return (float)tanh(a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthtand()
/|	Beschreibung:	Berechnet den hyberbolischen Tangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fasthtand(const float a) {
	return tanh((double)a);
}

/*------------------------------------------------------------
/|	Funktion:		fasthtand()
/|	Beschreibung:	Berechnet den hyberbolischen Tangens eines Winkels a
/|	Parameter:		a (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fasthtand(const double a) {
	return tanh(a);
}