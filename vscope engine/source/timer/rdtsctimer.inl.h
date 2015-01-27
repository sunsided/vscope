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

#include "..\defines.h"
#include "..\include-windows.h"
#include "rdtsctimer.h"

/*------------------------------------------------------------
/|	Funktion:		TimerAlarm()
/+------------------------------------------------------------*/
VSINLINE bool RDTSCTIMER::TimerAlarm( ) {
	if( !isClassInit ) {
		//ASSERTPRINT( isClassInit != false );
		return false;	
	}

	if( framesPerSecond ) {
		if( usePerformanceCounter )	{
			TimerElapsedTime( NULL, &timeKeyRdtsc );
			timeDifferenceRdtsc = timeKeyRdtsc - startTimeKeyRdtsc;
			if( timeDifferenceRdtsc >= hzPerSecondRdtsc ) {
				startTimeKeyRdtsc = timeKeyRdtsc;
				return true;
			} else
				return false;
		} else {
			TimerElapsedTime( &timeKeyTicks );
			if( timeKeyTicks < startTimeKeyTicks )
				startTimeKeyTicks = 0;
			timeDifferenceTicks = (float)(timeKeyTicks - startTimeKeyTicks);
			if( timeDifferenceTicks >= hzPerSecondTicks ) {
				startTimeKeyTicks = timeKeyTicks;
				return true;
			} else
				return false;
		}
	} else
		return true;
}

/*------------------------------------------------------------
/|	Funktion:		TimerFPS()
/+------------------------------------------------------------*/
VSINLINE const float& RDTSCTIMER::TimerFPS() {
	if( !isClassInit ) {
		//ASSERTPRINT( isClassInit != false );
		return frameCount;	
	}

	if( usePerformanceCounter )	{
		TimerElapsedTime( NULL, &timeKeyRdtsc );
		timeDifferenceRdtsc = timeKeyRdtsc - startTimeKeyRdtscFPS;
		if( timeDifferenceRdtsc == 0 ) {
			//ASSERTPRINT( timeDifferenceRdtsc == 0 );
			timeDifferenceRdtsc = 1;
		}
		frameCount = (float)rdtscPerSecond / timeDifferenceRdtsc;
		startTimeKeyRdtscFPS = timeKeyRdtsc;
	} else {
		TimerElapsedTime( &timeKeyTicks );
		if( timeKeyTicks < startTimeKeyTicksFPS )
			startTimeKeyTicksFPS = 0;
		timeDifferenceTicks = (float)( timeKeyTicks - startTimeKeyTicksFPS );
		if( timeDifferenceTicks < FLOAT_EPSILON )	{
			//ASSERTPRINT( timeDifferenceTicks >= FLOAT32_EPSILON );
			timeDifferenceTicks = FLOAT_EPSILON;
		}
		frameCount = (float)ticksPerSecond / timeDifferenceTicks;
		startTimeKeyTicksFPS = timeKeyTicks;
	}
	return frameCount;
}

/*------------------------------------------------------------
/|	Funktion:		TimerElapsedTime()
/+------------------------------------------------------------*/
VSINLINE void RDTSCTIMER::TimerElapsedTime( ulong32* timeTicks, uint64* timeRdtsc ) {
	if( !isClassInit ) {
		//ASSERTPRINT( isClassInit != false );
		return;	
	}
	if( timeRdtsc && usePerformanceCounter ) {		
		ulong32 dwLow, dwHigh;
		__asm {
			rdtsc
			mov dwLow, eax
			mov dwHigh, edx
		}
		*timeRdtsc = ( (uint64)dwHigh << 32 ) | (uint64)dwLow;
	}
	if( timeTicks )	{
		timeBeginPeriod( 1 );
		*timeTicks = timeGetTime( );
		timeEndPeriod( 1 );
	}
}