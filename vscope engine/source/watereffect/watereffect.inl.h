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

	Dateiname:		watereffect.inl.h
	Beschreibung:	WaterEffect Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 21:25

	Changelog:
	[1]		16. Juli 2002 21:25
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "watereffect.h"
#include "..\common\common.h"
#include "..\debug\debug.h"
#include "..\random\random.h"


VSINLINE void WATEREFFECT::Update() {
	ProcessWater();
	ProcessTexture();

	int *temp = m_pWaterActive;
	m_pWaterActive = m_pWaterScratch;
	m_pWaterScratch = temp;

	return;
}

VSINLINE void WATEREFFECT::Update(const LPDIRECT3DTEXTURE9 texIn, LPDIRECT3DTEXTURE9 texOut) {
	ProcessWater();

	this->m_pImageTex = texIn;
	ProcessTexture();
	texOut = this->m_pWaterTex;

	int *temp = m_pWaterActive;
	m_pWaterActive = m_pWaterScratch;
	m_pWaterScratch = temp;

	return;
}

VSINLINE void WATEREFFECT::Update(LPDIRECT3DTEXTURE9 texOut) {
	ProcessWater();
	ProcessTexture();
	texOut = this->m_pWaterTex;

	int *temp = m_pWaterActive;
	m_pWaterActive = m_pWaterScratch;
	m_pWaterScratch = temp;

	return;
}

VSINLINE void WATEREFFECT::Create(const LPDIRECT3DDEVICE9 pDevice, const int iTextureSize, const float fRefraction, const float fDepth, const float fDampening) {
	this->m_pd3dDevice = pDevice;
	this->m_iTextureSize = iTextureSize;
	m_fRefraction = fRefraction;
	m_fDepth = fDepth;
	m_fDamp = fDampening;
	
	MakeDisplacementLookupTable();

	SAFE_DELETE_ARRAY(m_iWaterField);
	SAFE_DELETE_ARRAY(m_iWaterField2);
	int sqSize = m_iTextureSize*m_iTextureSize;
	m_iWaterField  = new signed int[sqSize];
	m_iWaterField2 = new signed int[sqSize];

	// setup water buffers
	m_pWaterActive = m_iWaterField;
	m_pWaterScratch = m_iWaterField2;

	// clear water memory
	memset(m_iWaterField,  0, sizeof(m_iWaterField) * sqSize);
	memset(m_iWaterField2, 0, sizeof(m_iWaterField2) * sqSize);

	this->Restore();
}

VSINLINE void WATEREFFECT::Restore() {
	// create destination water texture - same size as image
	HRESULT hr;
	if (FAILED(hr = D3DXCreateTexture(m_pd3dDevice, m_iTextureSize, m_iTextureSize, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pWaterTex))) {
		dprintf("WATEREFFECT::Restore: Fehler %X ist aufgetreten.\n", hr);		
		return;
	}
}

VSINLINE void WATEREFFECT::Invalidate() {
  SAFE_RELEASE(m_pWaterTex);
}

VSINLINE void WATEREFFECT::Delete() {
	SAFE_DELETE_ARRAY(this->m_iWaterField);
	SAFE_DELETE_ARRAY(this->m_iWaterField2);
}

VSINLINE WATEREFFECT::~WATEREFFECT() {
	this->Invalidate();
	this->Delete();
}

VSINLINE WATEREFFECT::WATEREFFECT() {
	this->m_pd3dDevice = NULL;
	this->m_iWaterField = NULL;
	this->m_iWaterField2 = NULL;
	this->m_pWaterActive = NULL;
	this->m_pWaterScratch = NULL;
	memset(this->m_lutDisplacement, 0, sizeof(this->m_lutDisplacement));
}

VSINLINE void WATEREFFECT::AddDrop(int iX, int iY, int iSize, int iSplashStrength) {
	CreateWaterDroplet(iX, iY, iSize, iSplashStrength, m_pWaterActive, m_iTextureSize, m_iTextureSize);
}

VSINLINE void WATEREFFECT::AddDrop() {
	CreateWaterDroplet(RandomNumber(0, m_iTextureSize), RandomNumber(0, m_iTextureSize), RandomNumber(5, 15), RandomNumber(10, 25), m_pWaterActive, m_iTextureSize, m_iTextureSize);
}

VSINLINE void WATEREFFECT::SetBaseTexture(LPDIRECT3DTEXTURE9 Texture) {
	this->m_pImageTex = Texture;
}

VSINLINE LPDIRECT3DTEXTURE9 WATEREFFECT::GetTexture() const {
	return this->m_pWaterTex;
}

VSINLINE void WATEREFFECT::SetTextureStages() const {
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
}

VSINLINE void WATEREFFECT::SetTexture() const {
	this->m_pd3dDevice->SetTexture( 0, this->m_pWaterTex );
}