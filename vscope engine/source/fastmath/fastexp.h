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
	Beschreibung:	Fastmath-Header für exponentiales, intrinsisch
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:31

	Changelog:
	[1]		04. Juli 2002 23:06
			Erstellt

===========================================================================*/

#pragma once

#ifndef FASTEXP_DEFINED
#define FASTEXP_DEFINED
#endif

#include <math.h>
#include "..\defines.h"

#pragma intrinsic(pow, exp, log10, log)

/*------------------------------------------------------------
/|	Funktion:		fastpow()
/|	Beschreibung:	Berechnet x hoch y
/|	Parameter:		x (float), y (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastpow(const float &x, const float &y) {
	return (float)pow((double)x, (double)y);
}

/*------------------------------------------------------------
/|	Funktion:		fastpow()
/|	Beschreibung:	Berechnet x hoch y
/|	Parameter:		x (double), y (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastpow(const double &x, const double &y) {
	return (float)pow(x, y);
}

/*------------------------------------------------------------
/|	Funktion:		fastpowd()
/|	Beschreibung:	Berechnet x hoch y
/|	Parameter:		x (float), y (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastpowd(const float &x, const float &y) {
	return (double)pow((double)x, (double)y);
}

/*------------------------------------------------------------
/|	Funktion:		fastpowd()
/|	Beschreibung:	Berechnet x hoch y
/|	Parameter:		x (double), y (double)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastpowd(const double &x, const double &y) {
	return pow(x, y);
}

/**************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fastexp()
/|	Beschreibung:	Berechnet den Exponenten von x
/|	Parameter:		x (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastexp(const float &x) {
	return (float)exp((double)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastexp()
/|	Beschreibung:	Berechnet den Exponenten von x
/|	Parameter:		x (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastexp(const double &x) {
	return (float)exp(x);
}

/*------------------------------------------------------------
/|	Funktion:		fastexpd()
/|	Beschreibung:	Berechnet den Exponenten von x
/|	Parameter:		x (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastexpd(const float &x) {
	return exp((double)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastexpd()
/|	Beschreibung:	Berechnet den Exponenten von x
/|	Parameter:		x (double)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastexpd(const double &x) {
	return exp(x);
}

/**************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fastlog10()
/|	Beschreibung:	Berechnet den Basis 10-Logarithmus von x
/|	Parameter:		x (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastlog10(const float &x) {
	return log10f(x);
}

/*------------------------------------------------------------
/|	Funktion:		fastlog10()
/|	Beschreibung:	Berechnet den Basis 10-Logarithmus von x
/|	Parameter:		x (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastlog10(const double &x) {
	return log10f((float)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastlog10d()
/|	Beschreibung:	Berechnet den Basis 10-Logarithmus von x
/|	Parameter:		x (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastlog10d(const float &x) {
	return log10((double)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastlog10d()
/|	Beschreibung:	Berechnet den Basis 10-Logarithmus von x
/|	Parameter:		x (double)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastlog10d(const double &x) {
	return log10(x);
}

/**************************************************************************************/

/*------------------------------------------------------------
/|	Funktion:		fastlog()
/|	Beschreibung:	Berechnet den Logarithmus von x
/|	Parameter:		x (float)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastlog(const float &x) {
	return logf(x);
}

/*------------------------------------------------------------
/|	Funktion:		fastlog()
/|	Beschreibung:	Berechnet den Logarithmus von x
/|	Parameter:		x (double)
/|	Rückgabe:		float
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE float fastlog(const double &x) {
	return logf((float)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastlogd()
/|	Beschreibung:	Berechnet den Logarithmus von x
/|	Parameter:		x (float)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastlogd(const float &x) {
	return log((double)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastlogd()
/|	Beschreibung:	Berechnet den Logarithmus von x
/|	Parameter:		x (double)
/|	Rückgabe:		double
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
VSINLINE double fastlogd(const double &x) {
	return log(x);
}