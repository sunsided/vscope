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

	Dateiname:		fastassort.h
	Beschreibung:	Unsortiertes
	Revision:		2
	Erstellt:		MMT, 05. Juli 2002 17:03

	Changelog:
	[2]		07. Juli 2002 15:30 MMT
			Konstanten hinzugefügt, Makros für Rad2Deg und Deg2Rad
	[1]		05. Juli 2002 17:03
			Erstellt

===========================================================================*/

#pragma once

#ifndef FASTASSORT_DEFINED
#define FASTASSORT_DEFINED
#endif

#include <math.h>
#include "..\defines.h"

#ifndef SIGNBIT
#define SIGNBIT 0x80000000
#endif

#ifndef INVSIGNBIT
#define INVSIGNBIT 0x7FFFFFFF
#endif

#define PI				  3.141592653589793238462643383279500f
#define PIx2			  6.283185307179586476925286766559000f
#define PIx5d4			  3.926990816987241548078304229099400f	/* 225°, 1.25PI */
#define PIx180			565.486677646162782923275808990310000f
#define PId180			  0.017453292519943295769236907684886f
#define PId1d180		 57.295779513082320876798154814105000f
#define PId2			  1.570796326794896619231321691639800f
#define PId4			  0.785398163397448309615660845819880f
#define PIUNDER180		PId1d180
#define VALRAD2DEG		PIUNDER180
#define VALDEG2RAD		PId180
#define PIOVER180		PId180
#define E				  2.71828182845904523536f
#define EULER			E

#define VAL2ATAN1		  1.570796326794896619231321691639800f
#define VALATAN1		  0.785398163397448309615660845819880f

#define RAD90			  1.570796326794896619231321691560000f
#define RAD180			  3.141592653589793238462643383279500f
#define RAD270			  4.712388980384689857693965074919300f
#define RAD360			  6.283185307179586476925286766559000f

#define RAD2DEG(x)		(x * VALRAD2DEG)
#define DEG2RAD(x)		(x * VALDEG2RAD)

#define VAL1d1			  1.f /* die Rechnung sparen wir uns */
#define VAL1d2			  0.5f
#define VAL1d3			  0.333333333333333333333333333333333f
#define VAL1d4			  0.25f
#define VAL1d5			  0.2f
#define VAL1d6			  0.166666666666666666666666666666666f
#define VAL1d7			  0.142857142857142857142857142857140f
#define VAL1d8			  0.125f
#define VAL1d9			  0.111111111111111111111111111111111f
#define VAL1d10			  0.1f
#define VAL1d255		  0.003921568627450980392156862745098f

#define VAL2d1			  2.f
#define VAL2d2			  1.f /* die Rechnung sparen wir uns */
#define VAL2d3			  0.666666666666666666666666666666666f
#define VAL2d4			  0.5f
#define VAL2d5			  0.4f
#define VAL2d6			  0.333333333333333333333333333333333f
#define VAL2d7			  0.285714285714285714285714285714290f
#define VAL2d8			  0.25f
#define VAL2d9			  0.222222222222222222222222222222222f
#define VAL2d10			  0.2f

#define EPSILON			0.000001f
#ifndef OVERRIDE_EPSILON
#define EQUALS(x, y)	(((x - y) <= EPSILON) && ((x - y) > -EPSILON))
#else
#define EQUALS(x, y)	(((x - y) <= OVERRIDE_EPSILON) && ((x - y) > -OVERRIDE_EPSILON))
#endif

#ifndef OVERRIDE_EPSILON
#define ISZERO(x)		((x < EPSILON) && (x > -EPSILON))
#else
#define ISZERO(x)		((x < OVERRIDE_EPSILON) && (x > -OVERRIDE_EPSILON))
#endif

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b
#define MIN3(a, b, c) ((((a)<(b))&&((a)<(c))) ? (a) : (((b)<(c)) ? (b) : (c)))
#define MAX3(a, b, c) ((((a)>(b))&&((a)>(c))) ? (a) : (((b)>(c)) ? (b) : (c)))

#define SIGN3( A ) (((A).x<0)?4:0 | ((A).y<0)?2:0 | ((A).z<0)?1:0)