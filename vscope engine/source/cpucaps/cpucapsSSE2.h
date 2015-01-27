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

	Dateiname:		cpucapsSSE2.h
	Beschreibung:	Funktionen zum Aktivieren/Deaktivieren der internen
					SSE2-Unterstützung.
	Revision:		1
	Erstellt:		MMT, 04. Juli 2002 23:43

	Changelog:
	[1]		04. Juli 2002 23:43
			Erstellt

===========================================================================*/

#pragma once
#include <math.h>

/*------------------------------------------------------------
/|	Funktion:		enableSSE2()
/|	Beschreibung:	Aktiviert die Streaming SIMD Extensions 2 (SSE2)
/|	Parameter:		-
/|	Rückgabe:		bool (aktiviert/deaktiviert)
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
__forceinline bool enableSSE2() {
	return _set_SSE2_enable(1)==0?false:true;
}

/*------------------------------------------------------------
/|	Funktion:		disableSSE2()
/|	Beschreibung:	Deaktiviert die Streaming SIMD Extensions 2 (SSE2)
/|	Parameter:		-
/|	Rückgabe:		-
/|  2002-07-04 18:35 MMT
/+------------------------------------------------------------*/
__forceinline void disableSSE2() {
	_set_SSE2_enable(0);
}