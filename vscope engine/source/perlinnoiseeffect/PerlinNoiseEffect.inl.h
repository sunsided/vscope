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

	Dateiname:		PerlinNoiseEffect.inl.h
	Beschreibung:	PerlinNoiseEffect Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 21:25

	Changelog:
	[1]		16. Juli 2002 21:25
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "PerlinNoiseEffect.h"
#include "..\common\common.h"
#include "..\debug\debug.h"

#include "..\perlinnoise\perlinnoise.h"
#include "..\perlinnoise\perlinnoise.inl.h"

VSINLINE PERLINNOISEEFFECT::PERLINNOISEEFFECT() {
	this->m_pd3dDevice = NULL; 
	this->m_NoiseBuffer1 = NULL; 
	this->m_NoiseBuffer2 = NULL;
    this->m_pActiveBuffer = NULL; 
	this->m_pScratchBuffer = NULL;
	this->m_fOctaves = 4.f;
	this->m_fPersistence = 0.25f;
}

VSINLINE PERLINNOISEEFFECT::~PERLINNOISEEFFECT() {
	this->Invalidate();
	this->Delete();
}

VSINLINE void PERLINNOISEEFFECT::SetOctaves(const float& octaves) { 
	this->m_fOctaves = octaves;
}

VSINLINE float PERLINNOISEEFFECT::GetOctaves() const {
	return this->m_fOctaves; 
}

VSINLINE void PERLINNOISEEFFECT::SetPersistence(const float& persistence) { 
	this->m_fPersistence = persistence;
}

VSINLINE float PERLINNOISEEFFECT::GetPersistence() const {
	return this->m_fPersistence; 
}

VSINLINE void PERLINNOISEEFFECT::SetSeed(const float& seed) { 
	this->m_fSeed = seed;
}

VSINLINE float PERLINNOISEEFFECT::GetSeed() const {
	return this->m_fSeed; 
}

VSINLINE void PERLINNOISEEFFECT::GetTexture(LPDIRECT3DTEXTURE9 Texture) const {
	Texture = this->m_pTexture;
}

VSINLINE LPDIRECT3DTEXTURE9	PERLINNOISEEFFECT::GetTexture() const {
	return this->m_pTexture;
}

VSINLINE PERLINNOISEEFFECT::operator LPDIRECT3DTEXTURE9 () const {
	return this->m_pTexture;
}

VSINLINE bool PERLINNOISEEFFECT::LoadPalette(const char *strBMPfile) {
	HRESULT hr;
	LPDIRECT3DTEXTURE9 pTexture = NULL;
	  
	hr = D3DXCreateTextureFromFileExA(m_pd3dDevice,	strBMPfile, 0, 0, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, m_Palette, &pTexture);
	if(FAILED(hr)) {
		dprintf("(FEHLER) PERLINNOISEEFFECT::LoadPalette fehlgeschlagen. Fehler %X.\n", hr);
		return false; 
	}

	SAFE_RELEASE(pTexture);
	return true;
}

VSINLINE void PERLINNOISEEFFECT::Update() {
	this->Process();

	// Puffer austauschen.
	unsigned char *temp = m_pActiveBuffer;
	m_pActiveBuffer = m_pScratchBuffer;
	m_pScratchBuffer = temp;

	this->CopyToTexture();
}

VSINLINE void PERLINNOISEEFFECT::Update(const float fTreshold) {
	this->Process(fTreshold);

	// Puffer austauschen.
	unsigned char *temp = m_pActiveBuffer;
	m_pActiveBuffer = m_pScratchBuffer;
	m_pScratchBuffer = temp;

	this->CopyToTexture();
}

VSINLINE void PERLINNOISEEFFECT::SetTextureStages() const {
	// set up our texture stages for a simple texture copy...
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );

	// turning on linear filtering for our fire texture really helps out with
	// the image quality.
	//this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	//this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
	//this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	this->m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	this->m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	this->m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

VSINLINE void PERLINNOISEEFFECT::SetTexture() const {
	this->m_pd3dDevice->SetTexture( 0, this->m_pTexture );
}

VSINLINE void PERLINNOISEEFFECT::Invalidate() {
	SAFE_RELEASE( m_pTexture );
}

VSINLINE void PERLINNOISEEFFECT::Delete() {
	// delete fire buffers
	delete[] this->m_NoiseBuffer1; this->m_NoiseBuffer1 = NULL;
	delete[] this->m_NoiseBuffer2; this->m_NoiseBuffer2 = NULL;
}

VSINLINE void PERLINNOISEEFFECT::Restore() {
	HRESULT hr;
	  
	if (FAILED(hr = D3DXCreateTexture(m_pd3dDevice, m_iTextureSize, m_iTextureSize, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture))) {
		dprintf("(FEHLER) PERLINNOISEEFFECT::Restore. Textur kann nicht erstellt werden. Fehler %X.\n", hr);
		throw("PERLINNOISEEFFECT::Restore. Textur kann nicht erstellt werden.");
	}
}


VSINLINE bool PERLINNOISEEFFECT::LoadPalette() {
	int q = 255;
	do {
		m_Palette[q].peRed   = q;
		m_Palette[q].peGreen = q;
		m_Palette[q].peBlue  = q;
		m_Palette[q].peFlags = 0;
		q--;
	} while (q>=0);
	return true;
}

VSINLINE bool PERLINNOISEEFFECT::LoadPalette(const PALETTEENTRY *Palette) {
	memcpy(m_Palette, Palette, 256);
	return true;
}

VSINLINE bool PERLINNOISEEFFECT::LoadPaletteInverse() {
	int q = 255;
	int iq;
	do {
		iq = 255 - q;
		m_Palette[q].peRed   = iq;
		m_Palette[q].peGreen = iq;
		m_Palette[q].peBlue  = iq;
		m_Palette[q].peFlags = 0;
		q--;
	} while (q>=0);
	return true;
}

VSINLINE void PERLINNOISEEFFECT::Create(const LPDIRECT3DDEVICE9 pDevice, const unsigned int iTextureSize, const float &seed, const float &persistence, const float &octaves) {
	if (!pDevice) { 
		dprintf("(FEHLER) PERLINNOISEEFFECT::Create: Ungültiges Direct3D-Objekt. (!pDevice)\n");
		throw("PERLINNOISEEFFECT::Create: Ungültiges Direct3D-Objekt."); 
	}
	if (iTextureSize < 2 || iTextureSize > 512 || !IsPowerOf2(iTextureSize)) {
		dprintf("(FEHLER) PERLINNOISEEFFECT::Create: Ungültige Texturgröße.\n");
		throw("PERLINNOISEEFFECT::Create: Ungültige Texturgröße.");
	}

	m_fPersistence = persistence;
	m_fOctaves = octaves;
	m_fSeed = seed;
	m_pd3dDevice = pDevice;
	m_iTextureSize = iTextureSize;

	// allocate fire buffers
	unsigned int isize = iTextureSize * iTextureSize;
	m_NoiseBuffer1 = new unsigned char[isize];
	m_NoiseBuffer2 = new unsigned char[isize];

	// set the first fire buffer active, 2nd one as scratch surface
	m_pActiveBuffer = m_NoiseBuffer1;
	m_pScratchBuffer = m_NoiseBuffer2;

	// clear the buffers
	memset(m_NoiseBuffer1, 0, isize);
	memset(m_NoiseBuffer2, 0, isize);

	this->LoadPalette();
	
	this->Restore(); // Die Zieltextur erstellen
}