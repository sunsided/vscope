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

	Dateiname:		texturelockkit.inl.h
	Beschreibung:	TextureLock Kit Definition
	Revision:		1
	Erstellt:		MMT, 17. Juli 2002 21:03

	Changelog:
	[1]		17. Juli 2002 21:03
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "texturelockkit.h"
#include "..\debug\debug.h"
#include "..\common\common.h"
#include "..\fastmath\fastassort.h"
#include "..\fastmath\fasttrig.h"
#include "..\blit\blit2d.h"

VSINLINE TEXTURELOCKKIT::TEXTURELOCKKIT() {
	this->m_bLocked = true;
	this->m_Texture = NULL;
	memset(&this->LockedRect, 0, sizeof(this->LockedRect));
	this->PitchOverhead = 0;
	this->m_iLockLevel = 0;
	memset(&this->SurfaceDesc, 0, sizeof(this->SurfaceDesc));
	this->BytesPerPixel = 0;
}

VSINLINE TEXTURELOCKKIT::~TEXTURELOCKKIT() {
	if(this->m_bLocked == true) {
		this->m_Texture->UnlockRect(this->m_iLockLevel);	
		this->m_Texture = NULL;
	}
}

VSINLINE HRESULT TEXTURELOCKKIT::Lock(LPDIRECT3DTEXTURE9 Texture, const unsigned int iMIPlevel, const RECT *LockRect, const DWORD lLockFlags) {
	if(this->m_bLocked) {
		dprintf("TEXTURELOCKKIT::Lock: Textur &X ist noch gelockt!\n", &this->m_Texture);
		return E_FAIL;
	}

	HRESULT hr;
	this->m_Texture = Texture;
	this->m_iLockLevel = iMIPlevel;
	memset(&this->LockedRect, 0, sizeof(this->LockedRect));
	hr = Texture->LockRect(iMIPlevel, &this->LockedRect, LockRect, lLockFlags);
	if(FAILED(hr)) {
		dprintf("TEXTURELOCKKIT::Lock: Fehler &X.\n", hr);
		return hr;
	}

	memset(&this->SurfaceDesc, 0, sizeof(this->SurfaceDesc));
	Texture->GetLevelDesc(iMIPlevel, &SurfaceDesc);

	this->BytesPerPixel = GetPixelByteCount(SurfaceDesc.Format);

	// Angaben in Bytes
	this->Pitch = LockedRect.Pitch;
	this->PitchOverhead = (LockedRect.Pitch - (SurfaceDesc.Width*this->BytesPerPixel));

	return hr;
}

VSINLINE HRESULT TEXTURELOCKKIT::Unlock() {
	if(!this->m_bLocked) {
		dprintf("TEXTURELOCKKIT::Unlock: Nicht gelockt.\n");
		return E_FAIL;
	}

	HRESULT hr;
	hr = this->m_Texture->UnlockRect(this->m_iLockLevel);
	if(FAILED(hr)) {
		dprintf("TEXTURELOCKKIT::Unlock: Fehler &X.\n", hr);
		return hr;
	}

	this->m_bLocked = true;
	this->m_Texture = NULL;
	memset(&this->LockedRect, 0, sizeof(this->LockedRect));
	this->PitchOverhead = 0;
	this->m_iLockLevel = 0;
	memset(&this->SurfaceDesc, 0, sizeof(this->SurfaceDesc));
	this->BytesPerPixel = 0;

	return hr;
}

VSINLINE void TEXTURELOCKKIT::AccessArrayDWORD(DWORD *pData) {
	if(!pData) {
		dprintf("TEXTURELOCKKIT::AccessArrayDWORD: *pData muss auf einen %d byte Speicherbereich verweisen!\n", SurfaceDesc.Width * SurfaceDesc.Width * this->BytesPerPixel);
		throw("TEXTURELOCKKIT::AccessArrayDWORD: *pData muss auf einen gültigen Speicherbereich verweisen!\n");
	}	
	if(!this->m_bLocked) {
		dprintf("TEXTURELOCKKIT::AccessArrayDWORD: Nicht gelockt!\n");
		throw("TEXTURELOCKKIT::AccessArrayDWORD: Nicht gelockt!\n");
	}
	// Angaben in DWORD
	this->Pitch = LockedRect.Pitch / sizeof(DWORD);
	this->PitchOverhead = (LockedRect.Pitch - (SurfaceDesc.Width*this->BytesPerPixel)) / sizeof(DWORD);
	pData = (DWORD *)(LockedRect.pBits);
}

VSINLINE void TEXTURELOCKKIT::AccessArrayWORD(WORD *pData) {
	if(!pData) {
		dprintf("TEXTURELOCKKIT::AccessArrayWORD: *pData muss auf einen %d byte Speicherbereich verweisen!\n", SurfaceDesc.Width * SurfaceDesc.Width * this->BytesPerPixel);
		throw("TEXTURELOCKKIT::AccessArrayWORD: *pData muss auf einen gültigen Speicherbereich verweisen!\n");
	}
	if(!this->m_bLocked) {
		dprintf("TEXTURELOCKKIT::AccessArrayWORD: Nicht gelockt!\n");
		throw("TEXTURELOCKKIT::AccessArrayWORD: Nicht gelockt!\n");
	}
	// Angaben in WORD
	this->Pitch = LockedRect.Pitch / sizeof(WORD);
	this->PitchOverhead = (LockedRect.Pitch - (SurfaceDesc.Width*this->BytesPerPixel)) / sizeof(WORD);
	pData = (WORD *)(LockedRect.pBits);
}

VSINLINE void TEXTURELOCKKIT::AccessArrayChar(unsigned char *pData) {
	if(!pData) {
		dprintf("TEXTURELOCKKIT::AccessArrayChar: *pData muss auf einen %d byte Speicherbereich verweisen!\n", SurfaceDesc.Width * SurfaceDesc.Width * this->BytesPerPixel);
		throw("TEXTURELOCKKIT::AccessArrayChar: *pData muss auf einen gültigen Speicherbereich verweisen!\n");
	}
	if(!this->m_bLocked) {
		dprintf("TEXTURELOCKKIT::AccessArrayChar: Nicht gelockt!\n");
		throw("TEXTURELOCKKIT::AccessArrayChar: Nicht gelockt!\n");
	}
	// Angaben in CHAR
	this->Pitch = LockedRect.Pitch;
	this->PitchOverhead = (LockedRect.Pitch - (SurfaceDesc.Width*this->BytesPerPixel));
	pData = (unsigned char *)(LockedRect.pBits);
}