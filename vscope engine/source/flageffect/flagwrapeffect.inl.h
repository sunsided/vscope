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

	Dateiname:		flagwrapeffect.inl.h
	Beschreibung:	FlagWrapEffect Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 17. Juli 2002 19:52

	Changelog:
	[1]		17. Juli 2002 19:52
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "flagwrapeffect.h"
#include "..\debug\debug.h"
#include "..\common\common.h"
#include "..\fastmath\fastassort.h"
#include "..\fastmath\fasttrig.h"

VSINLINE void FLAGWRAPEFFECT::CalcSINLUT() {
	for (int i=0; i < 128; i++) {
        this->m_SinLUT[i] = (int)(fastsin(VAL360d129 * DEG2RAD(i)) * 20.f);
	}
}

VSINLINE void FLAGWRAPEFFECT::Update() {
	this->ProcessFlag();
}

VSINLINE void FLAGWRAPEFFECT::Update(const LPDIRECT3DTEXTURE9 texIn, LPDIRECT3DTEXTURE9 texOut) {
	this->m_pInputTex = texIn;
	this->ProcessFlag();
	texOut = this->m_pFlagTex;
	return;
	return;
}

VSINLINE void FLAGWRAPEFFECT::Update(LPDIRECT3DTEXTURE9 texOut) {
	this->ProcessFlag();
	texOut = this->m_pFlagTex;
	return;
}

VSINLINE void FLAGWRAPEFFECT::Create(const LPDIRECT3DDEVICE9 pDevice, const int iTextureSize) {
	this->m_pd3dDevice = pDevice;
	this->m_iTextureSize = iTextureSize;
	this->CalcSINLUT();
	this->Restore();
}

VSINLINE void FLAGWRAPEFFECT::Restore() {
	HRESULT hr;
	if (FAILED(hr = D3DXCreateTexture(m_pd3dDevice, m_iTextureSize, m_iTextureSize, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pFlagTex))) {
		dprintf("FLAGWRAPEFFECT::Restore: Fehler %X ist aufgetreten.\n", hr);		
		return;
	}
}

VSINLINE void FLAGWRAPEFFECT::Invalidate() {
	SAFE_RELEASE(this->m_pFlagTex);
}

VSINLINE void FLAGWRAPEFFECT::Delete() {
}

VSINLINE FLAGWRAPEFFECT::~FLAGWRAPEFFECT() {
	this->Invalidate();
	this->Delete();
}

VSINLINE FLAGWRAPEFFECT::FLAGWRAPEFFECT() {
	this->m_pd3dDevice = NULL;
	this->m_pFlagTex = NULL;
	this->m_pInputTex = NULL;
	memset(this->m_SinLUT, 0, sizeof(this->m_SinLUT));
}

VSINLINE void FLAGWRAPEFFECT::SetBaseTexture(LPDIRECT3DTEXTURE9 Texture) {
	this->m_pInputTex = Texture;
}

VSINLINE LPDIRECT3DTEXTURE9 FLAGWRAPEFFECT::GetTexture() const {
	return this->m_pFlagTex;
}

VSINLINE FLAGWRAPEFFECT::operator LPDIRECT3DTEXTURE9() const {
	return this->m_pFlagTex;
}

VSINLINE void FLAGWRAPEFFECT::SetTextureStages() const {
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	this->m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
}

VSINLINE void FLAGWRAPEFFECT::SetTexture() const {
	this->m_pd3dDevice->SetTexture( 0, this->m_pFlagTex );
}