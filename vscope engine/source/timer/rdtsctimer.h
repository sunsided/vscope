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

	Dateiname:		rdtsctimer.h
	Beschreibung:	RDTSC-Timer Definition
	Revision:		2
	Erstellt:		MMT, 01. Juni 2003 18:22

	Changelog:
	[1]		01. Juni 2003 18:22
			Erstellt

===========================================================================*/

#pragma once

#ifndef RDTSCTIMER_DEFINED
#define RDTSCTIMER_DEFINED
#endif

#include "..\defines.h"
#include "..\include-windows.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
#define uint64 unsigned __int64
#define uint32 unsigned __int64
#define ulong32 unsigned __int32

#define FLOAT_EPSILON (float)1.19209e-007
#define ticksPerSecond 1000

/*---------------------------------------------------------------------------
	Strukturen für den Timer
---------------------------------------------------------------------------*/
struct RDTSCTIMER {
private:
	bool					isClassInit;

	uint32					framesPerSecond;
	float					hzPerSecondTicks;
	uint64					hzPerSecondRdtsc;

	static uint64			rdtscPerMillesecond;
	static uint64			rdtscPerSecond;
	static bool				usePerformanceCounter;
	
	uint64					startTimeKeyRdtsc;
	ulong32					startTimeKeyTicks;
	uint64					startTimeKeyRdtscFPS;
	ulong32					startTimeKeyTicksFPS;
	uint64					startTimeKeyFPS;
	float					frameCount;
	float					timeElapsed;
	uint64					timeKeyRdtsc;
	ulong32					timeKeyTicks;
	uint64					timeDifferenceRdtsc;
	float					timeDifferenceTicks;
	uint64					timeRdtsc;
	ulong32					timeTicks;

public:
	
							RDTSCTIMER();
							~RDTSCTIMER(){}

	void					TimerInit( uint32 );
	const float&			TimerFPS( );
	bool					TimerAlarm( );
	void					TimerElapsedTime( ulong32* , uint64* = NULL );
};
/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef RDTSCTIMER				*LPRDTSCTIMER;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef _ALIGN_16 RDTSCTIMER		RDTSCTIMERA16;
typedef _ALIGN_16 RDTSCTIMER		*LPRDTSCTIMERA16;

typedef _ALIGN_32 RDTSCTIMER		RDTSCTIMERA32;
typedef _ALIGN_32 RDTSCTIMER		*LPRDTSCTIMERA32;

typedef _CACHEALIGN RDTSCTIMER		RDTSCTIMERAC;
typedef _CACHEALIGN RDTSCTIMER		*LPRDTSCTIMERAC;