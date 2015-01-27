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

	Dateiname:		flageffect.inl.h
	Beschreibung:	FlagEffect Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 17. Juli 2002 18:35

	Changelog:
	[1]		17. Juli 2002 18:35
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "flageffect.h"
#include "..\debug\debug.h"
#include "..\common\common.h"
#include "..\fastmath\fastassort.h"
#include "..\fastmath\fasttrig.h"

VSINLINE void FLAGEFFECT::CalcSINLUT() {
	for (int i=0; i < 128; i++) {
        this->m_SinLUT[i] = (int)(fastsin(VAL360d129 * DEG2RAD(i)) * 20.f);
	}
}

VSINLINE void FLAGEFFECT::Update() {
	this->ProcessFlag();
}

VSINLINE void FLAGEFFECT::Update(const LPDIRECT3DTEXTURE9 texIn, LPDIRECT3DTEXTURE9 texOut) {
	this->m_pInputTex = texIn;
	this->ProcessFlag();
	texOut = this->m_pFlagTex;
	return;
	return;
}

VSINLINE void FLAGEFFECT::Update(LPDIRECT3DTEXTURE9 texOut) {
	this->ProcessFlag();
	texOut = this->m_pFlagTex;
	return;
}

VSINLINE void FLAGEFFECT::Create(const LPDIRECT3DDEVICE9 pDevice, const int iTextureSize) {
	this->m_pd3dDevice = pDevice;
	this->m_iTextureSize = iTextureSize;
	this->CalcSINLUT();
	this->Restore();
}

VSINLINE void FLAGEFFECT::Restore() {
	HRESULT hr;
	if (FAILED(hr = D3DXCreateTexture(m_pd3dDevice, m_iTextureSize, m_iTextureSize, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pFlagTex))) {
		dprintf("FLAGEFFECT::Restore: Fehler %X ist aufgetreten.\n", hr);		
		return;
	}
}

VSINLINE void FLAGEFFECT::Invalidate() {
	SAFE_RELEASE(this->m_pFlagTex);
}

VSINLINE void FLAGEFFECT::Delete() {
}

VSINLINE FLAGEFFECT::~FLAGEFFECT() {
	this->Invalidate();
	this->Delete();
}

VSINLINE FLAGEFFECT::FLAGEFFECT() {
	this->m_pd3dDevice = NULL;
	this->m_pFlagTex = NULL;
	this->m_pInputTex = NULL;
	memset(this->m_SinLUT, 0, sizeof(this->m_SinLUT));
}

VSINLINE void FLAGEFFECT::SetBaseTexture(LPDIRECT3DTEXTURE9 Texture) {
	this->m_pInputTex = Texture;
}

VSINLINE LPDIRECT3DTEXTURE9 FLAGEFFECT::GetTexture() const {
	return this->m_pFlagTex;
}

VSINLINE FLAGEFFECT::operator LPDIRECT3DTEXTURE9() const {
	return this->m_pFlagTex;
}


VSINLINE void FLAGEFFECT::SetTextureStages() const {
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
}

VSINLINE void FLAGEFFECT::SetTexture() const {
	this->m_pd3dDevice->SetTexture( 0, this->m_pFlagTex );
}