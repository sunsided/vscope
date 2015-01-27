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

#include "rdtsctimer.h"
#include "rdtsctimer.inl.h"
#include "..\debug\debug.h"

uint64	RDTSCTIMER::rdtscPerMillesecond		= 0;
uint64	RDTSCTIMER::rdtscPerSecond			= 0;
bool	RDTSCTIMER::usePerformanceCounter	= false;


/*------------------------------------------------------------
/|	Funktion:		RDTSCTIMER()
/|	Beschreibung:	Konstruktor
/|	Rückgabe:		n/a
/+------------------------------------------------------------*/
RDTSCTIMER::RDTSCTIMER() {
	this->isClassInit = false;
}


/*------------------------------------------------------------
/|	Funktion:		TimerInit()
/|	Beschreibung:	Initialisierung
/|	Rückgabe:		n/a
/+------------------------------------------------------------*/
void RDTSCTIMER::TimerInit( uint32 fps ) {
	if( isClassInit ) {
		//ASSERTPRINT( isClassInit != true );
		return;	
	}

	isClassInit = true;	
	static bool isInit = false;
	
	if( !isInit ) {
		__try {
			ulong32 dwLow1, dwHigh1;
			ulong32 dwLow2, dwHigh2;
			uint64	time;
			uint64	time2;
			__asm {
				rdtsc
				mov dwLow1, eax
				mov dwHigh1, edx
			}
			
			Sleep( 50 );

			__asm {
				rdtsc
				mov dwLow2, eax
				mov dwHigh2, edx
			}

			time = ( (unsigned __int64)dwHigh1 << 32 ) | (unsigned __int64)dwLow1;
			time2 = ( (unsigned __int64)dwHigh2 << 32 ) | (unsigned __int64)dwLow2;
			time2 -= time;
			
			rdtscPerSecond = time2;
			
			__asm {
				rdtsc
				mov dwLow1, eax
				mov dwHigh1, edx
			}
			
			Sleep( 50 );

			__asm {
				rdtsc
				mov dwLow2, eax
				mov dwHigh2, edx
			}

			time = ( (unsigned __int64)dwHigh1 << 32 ) | (unsigned __int64)dwLow1;
			time2 = ( (unsigned __int64)dwHigh2 << 32 ) | (unsigned __int64)dwLow2;
			time2 -= time;
				
			rdtscPerSecond += time2;
			rdtscPerSecond *= 10;
			rdtscPerMillesecond = rdtscPerSecond / (uint64)ticksPerSecond;
		
			usePerformanceCounter = true;
			dprintf( "Accurate rdtsc Timer Activated" );
		}
		__except( EXCEPTION_EXECUTE_HANDLER ) {
			usePerformanceCounter = false;
			dprintf( "TimeGetTime Timer Activated" );
		}
		isInit = true;
	}	
	
	framesPerSecond = fps;

	if( framesPerSecond ) {
		hzPerSecondTicks = (float)ticksPerSecond/(float)framesPerSecond;
		if( usePerformanceCounter )
			hzPerSecondRdtsc = rdtscPerSecond / framesPerSecond;
	}

	TimerElapsedTime( &startTimeKeyTicks, &startTimeKeyRdtsc );
	startTimeKeyTicksFPS = startTimeKeyTicks;
	startTimeKeyRdtscFPS = startTimeKeyRdtsc;
}