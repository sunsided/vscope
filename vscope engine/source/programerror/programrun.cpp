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

	Dateiname:		programrun.cpp
	Beschreibung:	Hilfsfunktionen für den Programmlauf
	Revision:		1
	Erstellt:		MMT, 22. Juli 2003 15:12

	Changelog:
	[1]		22. Juli 2003 15:12
			Erstellt

===========================================================================*/

#include "programrun.h"

#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include "..\include-windows.h"
#include "..\include-direct3d.h"
#include "..\debug\debug.h"
#include "..\dxcommon\dxcommon.h"
#include "..\random\random.h"


/*------------------------------------------------------------
/|	Funktion:		ApplicationStart()
/|	Beschreibung:	Start der Anwendung
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  22. Juli 2003 15:12
/+------------------------------------------------------------*/
void ApplicationStart(unsigned int in_vsver) {
	// Zufallszahlen-Generator
	srand( (unsigned)time( NULL ) );

	// SSE2
	//_set_SSE2_enable(1);

	// Für einen frischen Speicherbereich sorgen
	unsigned int iSize = (int)((frand_1((unsigned)time( NULL )) + 1) * 25000);
	void* m_memMover = malloc(iSize);
	free(m_memMover); m_memMover = NULL;

	// Infos ausspucken
	dprinttimestamp();
	dprintf(" - Anwendung gestartet.\n");
	dprintf("\tengine build:        %d\n", in_vsver);
	dprintf("\tDirectX-SDK:         0x%04x\n", DIRECT3D_VERSION);
	dprintf("\tInitial mem bounce:  %d Byte\n", iSize);
}

/*------------------------------------------------------------
/|	Funktion:		ApplicationEnd()
/|	Beschreibung:	Ende der Anwendung
/|	Parameter:		n/a
/|	Rückgabe:		signed int
/|  22. Juli 2003 15:12
/+------------------------------------------------------------*/
signed int ApplicationEnd() {
	// SSE2
	//_set_SSE2_enable(0);
	
	// Der Rest
	DWORD dwLastError = GetLastError();

	dprinttimestamp();
	dprintf(" - Anwendung beendet.\n");

	if(dwLastError!=0) { 
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwLastError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		dprintf("\tDer zuletzt gemeldete Fehler ist: \n\tID: %d, Text: %s\n", dwLastError, lpMsgBuf);
		LocalFree( lpMsgBuf );		
	}

	return dwLastError;	
}