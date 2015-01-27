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

	Dateiname:		timer.h
	Beschreibung:	Timer Definition
	Revision:		2
	Erstellt:		MMT, 10. Juli 2002 19:52

	Changelog:
	[2]		16. Juli 2002 18:55
			Umgestellt auf single-precision und Korrektur der Zeitrückgabe
	[1]		10. Juli 2002 19:52
			Erstellt

===========================================================================*/

#pragma once

#ifndef TIMER_DEFINED
#define TIMER_DEFINED
#endif

#include "..\defines.h"
#include "..\include-windows.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
#ifndef TIMER_DEFAULTFREQ
#define TIMER_DEFAULTFREQ 0.001f
#endif

/*---------------------------------------------------------------------------
	Strukturen für den Timer
---------------------------------------------------------------------------*/
struct TIMER {
//:: Die Membervariablen ....................................................
protected:
		bool				m_bIsPerformance;		// Haben wir einen Performance-Timer?
		float				m_dScaling;				// Scaling-Faktor
		bool				m_bHitAllowed;			// Überprüft, ob die Hit-Funktion verwendet werden darf
		LONGLONG			m_llLastHit;			// Speichert einen Zeitwert
		LONGLONG			m_llTicksPerSec;		// Ticks per second

//:: Die Konstruktoren ......................................................
public:
							TIMER();				// Konstruktor

//:: Das Interface ..........................................................
public:
		float				GetTimerValue();		// Liefert den aktuellen Wert des Timers
		float				GetElapsedTime();		// Liefert die Zeit, die seit lLastHit vergangen ist (Sekunden)
		float				Hit();					// Speichert die derzeitige Zeit und gibt sie zurück
		float				GetScaling();			// Liefert die Skalierung des Timers
};


/*---------------------------------------------------------------------------
	Einzelne Funktionen zum Thema
---------------------------------------------------------------------------*/

bool	TimerIsPerformance();

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef TIMER				*LPTIMER;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 TIMER		TIMERA16;
typedef _ALIGN_16 TIMER		*LPTIMERA16;

typedef _ALIGN_32 TIMER		TIMERA32;
typedef _ALIGN_32 TIMER		*LPTIMERA32;

typedef _CACHEALIGN TIMER	TIMERAC;
typedef _CACHEALIGN TIMER	*LPTIMERAC;*/