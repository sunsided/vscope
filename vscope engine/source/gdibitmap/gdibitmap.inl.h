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

	Dateiname:		gdibitmap.inl.h
	Beschreibung:	BDI Bitmap Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 14:36

	Changelog:
	[1]		10. Juli 2002 14:36

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "gdibitmap.h"

VSINLINE UINT GDIBITMAP::GetWidth() const {
	return this->m_iWidth;
}

VSINLINE UINT GDIBITMAP::GetHeight() const {
	return this->m_iHeight;
}

VSINLINE HDC GDIBITMAP::GetBitmapDC() const {
	return this->m_hdcBitmap;
}

VSINLINE GDIBITMAP::operator HDC () const {
	return this->m_hdcBitmap;
}

VSINLINE void GDIBITMAP::Init() {
	m_hdcBitmap=NULL;
	m_hBitmap=NULL;
	m_hOldBitmap=NULL;
	m_iWidth=0;
	m_iHeight=0;	
}

VSINLINE void GDIBITMAP::UnInit() {
	if (m_hdcBitmap == NULL) return;
	SelectObject(m_hdcBitmap,m_hOldBitmap);		// restore old bitmap
	DeleteObject(m_hBitmap);					// delete new bitmap
	DeleteDC(m_hdcBitmap);						// delete device context
}

VSINLINE GDIBITMAP::GDIBITMAP() {
	this->Init();
}

VSINLINE GDIBITMAP::~GDIBITMAP() {
	if(this->m_hBitmap) this->UnInit();
}