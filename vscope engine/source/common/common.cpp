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

	Dateiname:		common.cpp
	Beschreibung:	Häufig benötigte Makros und Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 15:15

	Changelog:
	[1]		10. Juli 2002 15:15

===========================================================================*/

// Ein Include der Defines bedeutet gleichzeitig den Include der
// common-Bibliothek, und anders herum.

#include "common.h"
#include <math.h>
#include <io.h>
#include <fcntl.h>

/*------------------------------------------------------------
/|	Funktion:		LoadFileIntoString()
/|	Beschreibung:	Lädt eine Datei in einen String
/|	Parameter:		strFilename (char*), &str (std::string)
/|	Rückgabe:		bool
/|  2002-07-10 15:20 MMT
/+------------------------------------------------------------*/
bool LoadFileIntoString(const char *strFilename, std::string &str) {
	int handle = open(strFilename, O_RDONLY | O_BINARY);
	if (handle == -1) return(false);

	int iFilesize = filelength(handle);
	str.reserve(iFilesize);

	int iPos = 0; str = ""; bool bSuccess = true;
	while (iPos < iFilesize) {
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		int iBytesRead = read(handle, buf, sizeof(buf)-1);
		str += buf;
		iPos += iBytesRead;
		if (iBytesRead == 0) { bSuccess = false; break; }
	}
	close(handle);
	return(bSuccess);
}

/*------------------------------------------------------------
/|	Funktion:		CenterWindow()
/|	Beschreibung:	Zentriert ein Fenster auf dem Bildschirm
/|	Parameter:		hwnd (HWND)
/|	Rückgabe:		n/a
/|  2002-07-10 15:20 MMT
/+------------------------------------------------------------*/
void CenterWindow(HWND hwnd) {
	// get the width and height of the screen
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight= GetSystemMetrics(SM_CYFULLSCREEN);

	// get the rectangle of the window
	RECT rectWindow;
	GetWindowRect(hwnd, &rectWindow);

	// do the centering math
	int iDestX = (iScreenWidth-(rectWindow.right-rectWindow.left)) / 2;
	int iDestY = (iScreenHeight-(rectWindow.bottom-rectWindow.top)) / 2;

	// center the window
	MoveWindow(hwnd, iDestX, iDestY, 
		rectWindow.right-rectWindow.left,
		rectWindow.bottom-rectWindow.top,
		true);
}


/*------------------------------------------------------------
/|	Funktion:		ConvertLastErrorToString()
/|	Beschreibung:	Wandelt den letzten Fehler in einen String um
/|	Parameter:		szDest (LPSTR), nMaxStrLen (int)
/|	Rückgabe:		n/a
/|  2002-07-10 15:21 MMT
/+------------------------------------------------------------*/
void ConvertLastErrorToString(LPSTR szDest, int nMaxStrLen) {
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	strncpy(szDest, reinterpret_cast<char *>(lpMsgBuf), nMaxStrLen);
	LocalFree( lpMsgBuf );
}


/*------------------------------------------------------------
/|	Funktion:		PluckFirstField()
/|	Beschreibung:	entfernt den String [0]...'delim' aus str
/|					und gibt ihn in dest zurück
/|	Parameter:		str (char*), dest (char*), maxlen (int), delim (char*)
/|	Rückgabe:		n/a
/|  2002-07-10 15:24 MMT
/+------------------------------------------------------------*/
void PluckFirstField(char *str, char *dest, int maxlen, const char *delim) {
	char *endpos;
	int p;

	if (!strlen(delim)) { strcpy(dest, str); return; }
	endpos = strstr(str, delim);
	if (!endpos) { strcpy(dest, str); return; }
	p = (int)(endpos - str);

	memset(dest, 0, maxlen);
	memcpy(dest, str, p);

	// pluck it off of str...
	strcpy(str, &str[p+strlen(delim)]);
}