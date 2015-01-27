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

	Dateiname:		FireEffect.inl.h
	Beschreibung:	FireEffect Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 16:58

	Changelog:
	[1]		16. Juli 2002 16:58
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "FireEffect.h"
#include "..\debug\debug.h"
#include "..\common\common.h"
#include "..\timer\timer.h"
#include "..\timer\timer.inl.h"

#pragma intrinsic(memcpy, memset)

VSINLINE FIREEFFECT::FIREEFFECT() {
	this->m_pd3dDevice = NULL; 
	this->m_FireBuffer1 = NULL; 
	this->m_FireBuffer2 = NULL;
    this->m_pActiveBuffer = NULL; 
	this->m_pScratchBuffer = NULL;
}

VSINLINE FIREEFFECT::~FIREEFFECT() {
	this->Invalidate();
	this->Delete();
}

VSINLINE void FIREEFFECT::SetCoolAmount(const int coolamount) { 
	m_iCoolAmount = coolamount; 
}

VSINLINE int FIREEFFECT::GetCoolAmount() const {
	return m_iCoolAmount; 
}

VSINLINE void FIREEFFECT::GetTexture(LPDIRECT3DTEXTURE9 Texture) const {
	Texture = this->m_pTexture;
}

VSINLINE LPDIRECT3DTEXTURE9	FIREEFFECT::GetTexture() const {
	return this->m_pTexture;
}

VSINLINE FIREEFFECT::operator LPDIRECT3DTEXTURE9 () const {
	return this->m_pTexture;
}

VSINLINE bool FIREEFFECT::LoadPalette(const char *strBMPfile) {
	HRESULT hr;
	LPDIRECT3DTEXTURE9 pTexture = NULL;
	  
	hr = D3DXCreateTextureFromFileExA(m_pd3dDevice,	strBMPfile, 0, 0, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, m_Palette, &pTexture);
	if(FAILED(hr)) {
		dprintf("(FEHLER) FIREEFFECT::LoadPalette fehlgeschlagen. Fehler %X.\n", hr);
		return false; 
	}

	SAFE_RELEASE(pTexture);
	return true;
}

VSINLINE void FIREEFFECT::Update() {
	this->Process();
	this->CopyToTexture();

	// Puffer austauschen.
	unsigned char *temp = m_pActiveBuffer;
	m_pActiveBuffer = m_pScratchBuffer;
	m_pScratchBuffer = temp;
}

VSINLINE void FIREEFFECT::Update(const float fDelayInS) {
	TIMER Timer;
	static float lasthit = Timer.Hit();

	if(Timer.Hit() - lasthit < fDelayInS) return;
	
	this->Update();
}

VSINLINE void FIREEFFECT::SetTextureStages() const {
	// set up our texture stages for a simple texture copy...
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );

	// turning on linear filtering for our fire texture really helps out with
	// the image quality.
	this->m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	this->m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	this->m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

VSINLINE void FIREEFFECT::SetTexture() const {
	this->m_pd3dDevice->SetTexture( 0, this->m_pTexture );
}

VSINLINE void FIREEFFECT::Invalidate() {
	SAFE_RELEASE( m_pTexture );
}

VSINLINE void FIREEFFECT::Delete() {
	// delete fire buffers
	delete[] m_FireBuffer1; m_FireBuffer1 = NULL;
	delete[] m_FireBuffer2; m_FireBuffer2 = NULL;
}

VSINLINE void FIREEFFECT::Restore() {
	HRESULT hr;
	  
	if (FAILED(hr = D3DXCreateTexture(m_pd3dDevice, m_iTextureSize, m_iTextureSize, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture))) {
		dprintf("(FEHLER) FIREEFFECT::Restore. Textur kann nicht erstellt werden. Fehler %X.\n", hr);
		throw("FIREEFFECT::Restore. Textur kann nicht erstellt werden.");
	}
}


VSINLINE void FIREEFFECT::LoadPalette() {
	int q = 255;
	do {
		m_Palette[q].peRed   = m_FireRed[q];
		m_Palette[q].peGreen = m_FireGreen[q];
		m_Palette[q].peBlue  = m_FireBlue[q];
		m_Palette[q].peFlags = 0;
		q--;
	} while (q>=0);
}

VSINLINE void FIREEFFECT::LoadPalette(const PALETTEENTRY *Palette) {
	memcpy(m_Palette, Palette, 256);
}

VSINLINE void FIREEFFECT::LoadPaletteBRG() {
	int q = 255;
	do {
		m_Palette[q].peRed   = m_FireBlue[q];
		m_Palette[q].peGreen = m_FireRed[q];
		m_Palette[q].peBlue  = m_FireGreen[q];
		m_Palette[q].peFlags = 0;
		q--;
	} while (q>=0);
}

VSINLINE void FIREEFFECT::LoadPaletteBGR() {
	int q = 255;
	do {
		m_Palette[q].peRed   = m_FireBlue[q];
		m_Palette[q].peGreen = m_FireGreen[q];
		m_Palette[q].peBlue  = m_FireRed[q];
		m_Palette[q].peFlags = 0;
		q--;
	} while (q>=0);
}

VSINLINE void FIREEFFECT::LoadPaletteGBR() {
	int q = 255;
	do {
		m_Palette[q].peRed   = m_FireGreen[q];
		m_Palette[q].peGreen = m_FireBlue[q];
		m_Palette[q].peBlue  = m_FireRed[q];
		m_Palette[q].peFlags = 0;
		q--;
	} while (q>=0);
}

VSINLINE void FIREEFFECT::LoadPaletteGRB() {
	int q = 255;
	do {
		m_Palette[q].peRed   = m_FireGreen[q];
		m_Palette[q].peGreen = m_FireRed[q];
		m_Palette[q].peBlue  = m_FireBlue[q];
		m_Palette[q].peFlags = 0;
		q--;
	} while (q>=0);
}

VSINLINE void FIREEFFECT::LoadPaletteRBG() {
	int q = 255;
	do {
		m_Palette[q].peRed   = m_FireRed[q];
		m_Palette[q].peGreen = m_FireBlue[q];
		m_Palette[q].peBlue  = m_FireGreen[q];
		m_Palette[q].peFlags = 0;
		q--;
	} while (q>=0);
}

VSINLINE void FIREEFFECT::Create(const LPDIRECT3DDEVICE9 pDevice, const unsigned int iTextureSize, const int iCoolAmount) {
	if (!pDevice) { 
		dprintf("(FEHLER) FIREEFFECT::Create: Ungültiges Direct3D-Objekt. (!pDevice)\n");
		throw("FIREEFFECT::Create: Ungültiges Direct3D-Objekt."); 
	}
	if (iTextureSize < 2 || iTextureSize > 512 || !IsPowerOf2(iTextureSize)) {
		dprintf("(FEHLER) FIREEFFECT::Create: Ungültige Texturgröße.\n");
		throw("FIREEFFECT::Create: Ungültige Texturgröße.");
	}

	m_iCoolAmount = iCoolAmount;
	m_pd3dDevice = pDevice;
	m_iTextureSize = iTextureSize;

	// allocate fire buffers
	unsigned int isize = iTextureSize * iTextureSize;
	m_FireBuffer1 = new unsigned char[isize];
	m_FireBuffer2 = new unsigned char[isize];

	// set the first fire buffer active, 2nd one as scratch surface
	m_pActiveBuffer = m_FireBuffer1;
	m_pScratchBuffer = m_FireBuffer2;

	// clear the buffers
	memset(m_FireBuffer1, 0, isize);
	memset(m_FireBuffer2, 0, isize);

	this->LoadPalette();
	
	this->Restore(); // Die Zieltextur erstellen
}