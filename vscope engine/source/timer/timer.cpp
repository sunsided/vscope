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
	Beschreibung:	Timer
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 19:52

	Changelog:
	[1]		10. Juli 2002 19:52
			Erstellt

===========================================================================*/

#include "timer.h"
#include "timer.inl.h"

/*------------------------------------------------------------
/|	Funktion:		TimerIsPerformance()
/|	Beschreibung:	Prüft, ob der Performance-Timer verfügbar ist
/|	Rückgabe:		bool
/|  2002-07-10 21:06 MMT
/+------------------------------------------------------------*/
bool TimerIsPerformance() {
	LARGE_INTEGER lFreqCount;
	if (QueryPerformanceFrequency(&lFreqCount)) {
		return TRUE;
	}
	return FALSE;
}

/*------------------------------------------------------------
/|	Funktion:		TIMER()
/|	Beschreibung:	Konstruktor
/|	Rückgabe:		n/a
/|  2002-07-10 21:06 MMT
/+------------------------------------------------------------*/
TIMER::TIMER() {
	LARGE_INTEGER lFreqCount, lLH;

	if (QueryPerformanceFrequency(&lFreqCount)) {
		// Initialisierung Frequenz
		this->m_bIsPerformance = TRUE;
		this->m_dScaling = 1.0f / lFreqCount.QuadPart;
		this->m_llTicksPerSec = lFreqCount.QuadPart;
		// Ersten Timer-Wert vorgeben
		QueryPerformanceCounter(&lLH);
		this->m_llLastHit = lLH.QuadPart;
	} else {
		this->m_bIsPerformance = FALSE;
		this->m_dScaling = TIMER_DEFAULTFREQ;
		this->m_llLastHit = 0; // timeGetTime();
	}

	this->m_bHitAllowed = TRUE;
}