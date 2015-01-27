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

	Dateiname:		gdibitmap.cpp
	Beschreibung:	BDI Bitmap
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 14:36

	Changelog:
	[1]		10. Juli 2002 14:36

===========================================================================*/

#include "gdibitmap.h"
#include "gdibitmap.inl.h"
#include "..\common\common.h"
#include "..\debug\debug.h"
#include <stdio.h>

void GDIBITMAP::Load(HDC hdcCompatible, LPCSTR lpszFilename) {
	// if we've already got a bitmap loaded, UnInit it so we can load a new one.
	if(m_hdcBitmap) UnInit();

	// create the memory dc
	m_hdcBitmap = CreateCompatibleDC(hdcCompatible);

	// load the BMP file
	m_hBitmap = (HBITMAP)LoadImage( NULL, lpszFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	 // if the load failed, throw an error.
	if (m_hBitmap == NULL) {
		// TODO: Debugger-Implementation
		char debugmsg[512];
		char errormsg[128];
		ConvertLastErrorToString( errormsg, sizeof(errormsg));
		sprintf(debugmsg, "GDIBITMAP: Error while trying to load \"%s\": %s", lpszFilename, errormsg);
		//::MessageBox(NULL, debugmsg, "Bitmap Loader", MB_ICONSTOP);
		dprintf(debugmsg);
		dmsgbox(debugmsg);
	}

	// select our new bitmap into the dc
	m_hOldBitmap = static_cast<HBITMAP>(SelectObject(m_hdcBitmap,m_hBitmap));

	// query the bitmap's properties
	BITMAP bmp;
	GetObject( m_hBitmap, sizeof(BITMAP), (LPVOID)&bmp );

	// assign height and width from those properties
	m_iWidth = bmp.bmWidth;
	m_iHeight = bmp.bmHeight;
}


void GDIBITMAP::CreateBlank(HDC hdcCompatible, UINT width, UINT height) {
	// if we've already got a bitmap loaded, UnInit it so we can load a new
	 // one.
	if(m_hdcBitmap) UnInit();

	// create the memory dc
	m_hdcBitmap = CreateCompatibleDC( hdcCompatible );

	// create the image
	m_hBitmap = CreateCompatibleBitmap( hdcCompatible, width, height );

	// select the image into the dc
	m_hOldBitmap = (HBITMAP)SelectObject( m_hdcBitmap, m_hBitmap );

	// assign height and width from those properties
	m_iWidth = width;
	m_iHeight = height;
}