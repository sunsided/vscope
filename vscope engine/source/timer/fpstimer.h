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

	Dateiname:		fpstimer.h
	Beschreibung:	FPS-Timer Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 21:07

	Changelog:
	[1]		10. Juli 2002 21:07
			Erstellt

===========================================================================*/

#pragma once

#ifndef FPSTIMER_DEFINED
#define FPSTIMER_DEFINED
#endif

#include "..\defines.h"
#include "..\include-windows.h"
#include "timer.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
#ifndef TIMER_DEFAULTFREQ
#define TIMER_DEFAULTFREQ 0.001
#endif

/*---------------------------------------------------------------------------
	Strukturen für den FPS-Timer
---------------------------------------------------------------------------*/
class FPSTIMER : public TIMER {
//:: Die Membervariablen ....................................................
private:
	WORD				wWantedFPS;				// gewünschte Framerate
	FLOAT				fRealFPS;				// tatsächliche Framerate
	DWORD				dwFPSdelay;				// Anzahl der Millisekunden zwischen den Frames
	LONGLONG			lNextRenderTime;		// Wann wird das nächste Mal gerendert?

//:: Die Konstruktoren ......................................................
public:
						FPSTIMER(const unsigned int FPS);				// Konstruktor

//:: Das Interface ..........................................................
public:
	bool				RenderEncouraged();		// Ist die richtige Zeit gekommen?
	float				GetFPS();				// Liefert die aktuelle Framerate
};


/*---------------------------------------------------------------------------
	Einzelne Funktionen zum Thema
---------------------------------------------------------------------------*/

bool	TimerIsPerformance();

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef FPSTIMER				*LPFPSTIMER;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 FPSTIMER		FPSTIMERA16;
typedef _ALIGN_16 FPSTIMER		*LPFPSTIMERA16;

typedef _ALIGN_32 FPSTIMER		FPSTIMERA32;
typedef _ALIGN_32 FPSTIMER		*LPFPSTIMERA32;

typedef _CACHEALIGN FPSTIMER	FPSTIMERAC;
typedef _CACHEALIGN FPSTIMER	*LPFPSTIMERAC;*/