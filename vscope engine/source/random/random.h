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

	Dateiname:		random.h
	Beschreibung:	Funktionen für Zufallszahlen
	Revision:		2
	Erstellt:		MMT, 07. Juli 2002 16:10

	Changelog:
	[3]		17. Juli 2002 17:30
			RandomNumber() hinzugefügt
	[2]		10. Juli 2002 15:14
			frand_1 überarbeitet, 3D-Version und Makros hinzugefügt.
	[1]		07. Juli 2002 16:10

===========================================================================*/

#pragma once

#ifndef RANDOM_DEFINED
#define RANDOM_DEFINED
#endif

#include <stdlib.h>
#include <math.h>
#include "..\defines.h"
#include "..\fastmath\fastassort.h"

namespace RANDOM {


/*------------------------------------------------------------
/|	Funktion:		frand_std()
/|	Beschreibung:	Liefert eine Zufallszahl zwischen -1 und 1
/|	Parameter:		n/a
/|	Benutzung:		Diese Funktion liefert eine zufällige Zahl
/|					zwischen -1 und 1.
/|					Der Zufallszahlengenerator wird über srand()
/|					initialisiert (ANSI-C).
/|	Pro/Con:		Die Funktion verwendet das Standard-rand()
/|	Rückgabe:		float
/|  2002-07-07 16:39 MMT
/+------------------------------------------------------------*/
VSINLINE float frand_std() {
	return (float)(rand()-RAND_MAX/2) / (RAND_MAX/2);
}


/*------------------------------------------------------------
/|	Funktion:		frand_1()
/|	Beschreibung:	Liefert eine Zufallszahl zwischen -1 und 1
/|	Parameter:		seed (unsigned int)
/|	Benutzung:		Diese Funktion liefert eine zufällige Zahl
/|					zwischen -1 und 1.
/|					Als seed wird x verwendet. Ein gleiches x
/|					bewirkt ein gleiches Ergebnis.
/|	Rückgabe:		float
/|  2002-07-07 16:39 MMT
/+------------------------------------------------------------*/
VSINLINE float frand_1(const unsigned int seed) {
	unsigned int ix = (seed<<13) ^ seed;
	return (float)( 1.0 - ( (ix * (ix * ix * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);    
}

VSINLINE float frandl_1(const unsigned long &seed) {
	unsigned long ix = (seed<<13) ^ seed;
	return (float)( 1.0 - ( (ix * (ix * ix * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);    
}


/*------------------------------------------------------------
/|	Funktion:		frand_1()
/|					Überladene Funktion
/|	Beschreibung:	Liefert eine Zufallszahl zwischen -1 und 1
/|	Parameter:		seed_x (unsigned int), seed_y (unsigned int)
/|	Benutzung:		Diese Funktion liefert eine zufällige Zahl
/|					zwischen -1 und 1.
/|					Verwendet 2D-Seeds, so dass die Funktion
/|					für eine Heightmap verwendet werden kann.
/|	Pro/Con:		Einfache Verwendung, etwas langsamer.
/|	Copyright:		Dies ist modifizierter Code, ursprünglich von
/|					Hugo Elias und Kim Pallister (Procedural Clouds Demo)
/|	Rückgabe:		float
/|  2002-07-07 16:39 MMT
/+------------------------------------------------------------*/
#define Noise2D(x, y) frand_1(x, y)
VSINLINE float frand_1(const int seed_x, const int seed_y) {
	unsigned int seed = seed_x + seed_y * 57;
	unsigned int ix = (seed<<13) ^ seed;
	return (float)( 1.0 - ( (ix * (ix * ix * 15731 + 789221) + 1376312589) & 0x7fffffff) * 0.000000000931322574615478515625f);
}

#define Noise3D(x, y, z) frand_1(x, y, z)
VSINLINE float frand_1(const int seed_x, const int seed_y, const int seed_z) {
	unsigned int seed = seed_x + seed_y * 57 + seed_z * 131;
	unsigned int ix = (seed<<13) ^ seed;
	return (float)( 1.0 - ( (ix * (ix * ix * 15731 + 789221) + 1376312589) & 0x7fffffff) * 0.000000000931322574615478515625f);
}


/*------------------------------------------------------------
/|	Funktion:		RandomNumber()
/|	Beschreibung:	Liefert eine Zufallszahl zwischen Min und Max
/|	Parameter:		fMin/iMin (float/int), fMax/iMax (float/int)
/|	Copyright:		Ursprünglich von Mason McKuskey, Spin Studios
/|	Rückgabe:		float/int
/|  2002-07-17 17:30 MMT
/+------------------------------------------------------------*/
VSINLINE float RandomNumber(float fMin, float fMax) {
  if (fMin == fMax) return(fMin);
  float fRandom = (float)rand() / (float)RAND_MAX;
  return((fRandom * (float)fabs(fMax-fMin))+fMin);
}

VSINLINE int RandomNumber(int iMin, int iMax) {
  if (iMin == iMax) return(iMin);
  return((rand() % (abs(iMax-iMin)+1))+iMin);
}

} // namespace
using namespace RANDOM;