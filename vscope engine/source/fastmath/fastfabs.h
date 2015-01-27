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

	Dateiname:		fastfabs.h
	Beschreibung:	Fastmath-Header für absolute Zahlen, intrinsisch
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:31

	Changelog:
	[1]		04. Juli 2002 23:06
			Erstellt

===========================================================================*/

#pragma once

#ifndef FASTFABS_DEFINED
#define FASTFABS_DEFINED
#endif

#include <math.h>
#include "..\defines.h"

#pragma intrinsic(fabs, labs)

/*------------------------------------------------------------
/|	Funktion:		fastfabs()
/|	Beschreibung:	Berechnet den Absolutwert einer Zahl x
/|	Parameter:		x (float) 
/|	Rückgabe:		float
/|  2002-07-04 18:23 MMT
/+------------------------------------------------------------*/
VSINLINE float fastfabs(const float &x) {
	return (float)fabs((double)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastfabs()
/|	Beschreibung:	Berechnet den Absolutwert einer Zahl x
/|	Parameter:		x (double) 
/|	Rückgabe:		float
/|  2002-07-04 18:23 MMT
/+------------------------------------------------------------*/
VSINLINE float fastfabs(const double &x) {
	return (float)fabs(x);
}

/*------------------------------------------------------------
/|	Funktion:		fastfabsd()
/|	Beschreibung:	Berechnet den Absolutwert einer Zahl x
/|	Parameter:		x (float) 
/|	Rückgabe:		double
/|  2002-07-04 18:23 MMT
/+------------------------------------------------------------*/
VSINLINE double fastfabsd(const float &x) {
	return fabs((double)x);
}

/*------------------------------------------------------------
/|	Funktion:		fastfabs()
/|	Beschreibung:	Berechnet den Absolutwert einer Zahl x
/|	Parameter:		x (double) 
/|	Rückgabe:		double
/|  2002-07-04 18:23 MMT
/+------------------------------------------------------------*/
VSINLINE double fastfabsd(const double &x) {
	return fabs(x);
}

/*------------------------------------------------------------
/|	Funktion:		fastlabs()
/|	Beschreibung:	Berechnet den Absolutwert einer Zahl x
/|	Parameter:		x (long) 
/|	Rückgabe:		long
/|  2002-07-04 18:23 MMT
/+------------------------------------------------------------*/
VSINLINE long fastlabs(const long &x) {
	return labs(x);
}