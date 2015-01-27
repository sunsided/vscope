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
	Beschreibung:	FPS-Timer Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 21:07

	Changelog:
	[1]		10. Juli 2002 21:07
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-windows.h"
#include "fpstimer.h"


/*------------------------------------------------------------
/|	Funktion:		FPSTIMER()
/|	Beschreibung:	Konstruktor
/|	Rückgabe:		n/a
/|  2002-07-10 21:10 MMT
/+------------------------------------------------------------*/
VSINLINE FPSTIMER::FPSTIMER(const unsigned int FPS) {
	this->wWantedFPS = FPS;
	this->dwFPSdelay = 1000 / FPS;	// Millisekunden (bei 25 FPS -> 40 ms)
	this->m_bHitAllowed = FALSE;
	this->lNextRenderTime = 0;
}

/*------------------------------------------------------------
/|	Funktion:		RenderEncouraged()
/|	Beschreibung:	Gibt an, ob ein Rendern zum Erhalten der
/|					gewünschten Framerate durchgeführt werden
/|					sollte.
/|	Rückgabe:		bool
/|  2002-07-10 21:10 MMT
/+------------------------------------------------------------*/
VSINLINE bool FPSTIMER::RenderEncouraged() {
	LONGLONG lNow;
	
	if (this->m_bIsPerformance)
		QueryPerformanceCounter((LARGE_INTEGER *) &lNow);
	else
		//lNow=timeGetTime();	
		;

	if(lNow>this->lNextRenderTime) {
		// Neue Zeit berechnen	
		this->lNextRenderTime += this->dwFPSdelay;

		// Wenn die Zeit vor unserer liegt, überspringen wir ein paar Frames
		if(this->lNextRenderTime<lNow)
			this->lNextRenderTime = lNow + this->dwFPSdelay;
		
		// Berechnung der Framerate
		this->fRealFPS = 1000.0f / (lNow - this->m_llLastHit);
		this->m_llLastHit = lNow;

		return TRUE;
	}
	return FALSE;
}
/*------------------------------------------------------------
/|	Funktion:		GetFPS()
/|	Beschreibung:	liefert die derzeitigen, tatsächlichen FPS zurück
/|	Rückgabe:		float
/|  2002-07-10 21:10 MMT
/+------------------------------------------------------------*/
VSINLINE float FPSTIMER::GetFPS() {
	return this->fRealFPS;
}