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

	Dateiname:		common.h
	Beschreibung:	Häufig benötigte Makros und Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 15:15

	Changelog:
	[1]		10. Juli 2002 15:15

===========================================================================*/

#pragma once

#include <string>
#include "..\defines.h"
#include "..\random\random.h"
#include "..\include-windows.h"
#include "..\fastmath\fastassort.h"

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_UNACQUIRE(p)    { if(p) { (p)->Unacquire();         } }

/*------------------------------------------------------------
/|	Funktion:		FtoDW()
/|	Beschreibung:	Wandelt einen float in ein DWORD um
/|	Parameter:		f (float)
/|	Rückgabe:		DWORD
/|  2002-07-10 15:20 MMT
/+------------------------------------------------------------*/
VSINLINE DWORD FtoDW( float f ) { 
	return *((DWORD*)&f); 
}

/*------------------------------------------------------------
/|	Funktion:		LoadFileIntoString()
/|	Beschreibung:	Lädt eine Datei in einen String
/|	Parameter:		strFilename (char*), &str (std::string)
/|	Rückgabe:		bool
/|  2002-07-10 15:20 MMT
/+------------------------------------------------------------*/
bool LoadFileIntoString(const char *strFilename, std::string &str);

/*------------------------------------------------------------
/|	Funktion:		CenterWindow()
/|	Beschreibung:	Zentriert ein Fenster auf dem Bildschirm
/|	Parameter:		hwnd (HWND)
/|	Rückgabe:		n/a
/|  2002-07-10 15:20 MMT
/+------------------------------------------------------------*/
void CenterWindow(HWND hwnd);

/*------------------------------------------------------------
/|	Funktion:		ConvertLastErrorToString()
/|	Beschreibung:	Wandelt den letzten Fehler in einen String um
/|	Parameter:		szDest (LPSTR), nMaxStrLen (int)
/|	Rückgabe:		n/a
/|  2002-07-10 15:21 MMT
/+------------------------------------------------------------*/
#define LastErrorToString(szDest, nMaxStrLen) ConvertLastErrorToString(szDest, nMaxStrLen)
void ConvertLastErrorToString(LPSTR szDest, int nMaxStrLen);

/*------------------------------------------------------------
/|	Funktion:		IsPowerOf2()
/|	Beschreibung:	Booleesch, ob n eine power von 2 ist...? *g*
/|	Parameter:		n (int)
/|	Rückgabe:		bool
/|  2002-07-10 15:22 MMT
/+------------------------------------------------------------*/
VSINLINE bool IsPowerOf2(int n) { 
	return (!(n & (n - 1))); 
}

/*------------------------------------------------------------
/|	Funktion:		GetLowestPowerOf2()
/|	Beschreibung:	Gibt die kleinste Power von 2 unter n zurück
/|	Parameter:		n (int)
/|	Rückgabe:		int
/|  2002-07-10 15:24 MMT
/+------------------------------------------------------------*/
#define LowestPowerOf2(n) GetLowestPowerOf2(n)
VSINLINE int GetLowestPowerOf2(int n) {
	int lowest = 1;
	while(lowest < n) lowest <<= 1;
	return lowest;
}

/*------------------------------------------------------------
/|	Funktion:		PluckFirstField()
/|	Beschreibung:	entfernt den String [0]...'delim' aus str
/|					und gibt ihn in dest zurück
/|	Parameter:		str (char*), dest (char*), maxlen (int), delim (char*)
/|	Rückgabe:		n/a
/|  2002-07-10 15:24 MMT
/+------------------------------------------------------------*/
void PluckFirstField(char *str, char *dest, int maxlen, const char *delim);

/*------------------------------------------------------------
/|	Funktion:		MakeUpperCase()
/|	Beschreibung:	Wandelt eine String in Upper Case um
/|	Parameter:		str (std::string)
/|	Rückgabe:		n/a
/|  2002-07-10 15:24 MMT
/+------------------------------------------------------------*/
VSINLINE void MakeUpperCase(std::string &str) {
  for (std::string::iterator i = str.begin(); i != str.end(); i++) {
    *i = toupper(*i);
  }
}

/*------------------------------------------------------------
/|	Funktion:		RemoveQuotes()
/|	Beschreibung:	Entfernt Anführungszeichen aus einem String
/|	Parameter:		str (std::string)
/|	Rückgabe:		std::string
/|  2002-07-10 15:24 MMT
/+------------------------------------------------------------*/
VSINLINE std::string RemoveQuotes(std::string &str) {
  for (std::string::iterator i = str.begin(); i != str.end(); i++) {
    if (*i == '\"') {
      i = str.erase(i); if (i == str.end()) break;
    }
  }
  return(str);
}