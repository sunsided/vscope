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
	Beschreibung:	Timer Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 19:52

	Changelog:
	[1]		10. Juli 2002 19:52
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-windows.h"
#include "timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")
#pragma comment(lib, "kernel32")


/*------------------------------------------------------------
/|	Funktion:		GetTimerValue()
/|	Beschreibung:	Liefert die aktuelle Zeit zurück
/|					zu interpretieren je nach Timertyp
/|	Rückgabe:		LONGLONG
/|  2002-07-10 21:07 MMT
/+------------------------------------------------------------*/
VSINLINE float TIMER::GetTimerValue() {
	LARGE_INTEGER lNow;
	if (this->m_bIsPerformance) {
		QueryPerformanceCounter(&lNow);
		return (float)lNow.QuadPart;
	}
	//return (float)timeGetTime();	
	return 0;
}

/*------------------------------------------------------------
/|	Funktion:		GetElapsedTime()
/|	Beschreibung:	Liefert die vergangene Zeit seit dem
/|					letzten Hit() zurück
/|	Rückgabe:		float
/|  2002-07-10 21:07 MMT
/+------------------------------------------------------------*/
VSINLINE float TIMER::GetElapsedTime() {
	return (this->GetTimerValue() - (float)this->m_llLastHit) * this->m_dScaling;
}

/*------------------------------------------------------------
/|	Funktion:		Hit()
/|	Beschreibung:	Merkt sich die aktuelle Zeit als Referenz
/|	Rückgabe:		LONGLONG (die aktuelle Zeit)
/|  2002-07-10 21:07 MMT
/+------------------------------------------------------------*/
VSINLINE float TIMER::Hit() {
	if(!this->m_bHitAllowed) 
		return (float)this->m_llLastHit;

	if (this->m_bIsPerformance) {
		LARGE_INTEGER lLH;
		QueryPerformanceCounter(&lLH);
		this->m_llLastHit = lLH.QuadPart;
	} else
		//this->m_llLastHit=timeGetTime();	
		this->m_llLastHit = 0;

	return (float)this->m_llLastHit;
}

/*------------------------------------------------------------
/|	Funktion:		GetScaling()
/|	Beschreibung:	Liefert die Skalierung des Timers
/|	Rückgabe:		float
/|  2002-07-16 18:57 MMT
/+------------------------------------------------------------*/
VSINLINE float TIMER::GetScaling() {
	return this->m_dScaling;
}