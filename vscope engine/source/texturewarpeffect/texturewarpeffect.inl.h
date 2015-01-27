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

	Dateiname:		texturewarpeffect.inl.h
	Beschreibung:	TextureWarpEffect Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 19. Juli 2002 03:02

	Changelog:
	[1]		19. Juli 2002 03:02
			Erstellt

===========================================================================*/

#pragma once
/*
#include "..\defines.h"
#include "texturewarpeffect.h"
#include "..\common\common.h"
#include "..\debug\debug.h"
#include "..\random\random.h"

VSINLINE TEXTUREWARPEFFECT::TEXTUREWARPEFFECT() {
	m_pTex1             = NULL;
	m_pTex2             = NULL;
	m_pImageTex         = NULL;
	m_pVBGrid           = NULL;
	m_pIBGrid           = NULL;
	m_pActiveTex		= NULL;
	m_pScratchTex		= NULL;
}

VSINLINE TEXTUREWARPEFFECT::~TEXTUREWARPEFFECT() {
	Invalidate();
	Delete();
}

VSINLINE void TEXTUREWARPEFFECT::Invalidate() {
	SAFE_RELEASE(m_pTex1);
	SAFE_RELEASE(m_pTex2);
	SAFE_RELEASE(this->m_pActiveTex);
	SAFE_RELEASE(this->m_pScratchTex);
	SAFE_RELEASE(m_pVBGrid);
	SAFE_RELEASE(m_pIBGrid);
}

VSINLINE void TEXTUREWARPEFFECT::Delete() {
}

VSINLINE void TEXTUREWARPEFFECT::Update() {
	const float DELAY = 0.05f; // Our Warp effect runs at 20 FPS
	static float fTimeToProcess = DELAY;
	
	fTimeToProcess -= 0.0001f;
	if (fTimeToProcess < 0) {
		ProcessBlendEffect(m_pd3dDevice, m_pActiveTex, m_pScratchTex, m_pVBGrid, m_pIBGrid, GetLowestPowerOf2(m_iImageWidth), GetLowestPowerOf2(m_iImageHeight));

		LPDIRECT3DTEXTURE9 pTemp;
		pTemp = m_pActiveTex;
		m_pActiveTex = m_pScratchTex;
		m_pScratchTex = pTemp;

		fTimeToProcess = DELAY;
  }
}

VSINLINE void TEXTUREWARPEFFECT::Restore() {
	// create the two texture buffers that we'll use for the effect
	// these must be created as render targets.
	if (FAILED(hr = D3DXCreateTexture(m_pd3dDevice, 
		GetLowestPowerOf2(m_iImageWidth), GetLowestPowerOf2(m_iImageHeight), 
		1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTex1))) {
		return(hr);
	}
	  
	if (FAILED(hr = D3DXCreateTexture(m_pd3dDevice, 
		GetLowestPowerOf2(m_iImageWidth), GetLowestPowerOf2(m_iImageHeight), 
		1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTex2))) {
		return(hr);
	}

	// set up the pointers
	m_pActiveTex = m_pTex1;
	m_pScratchTex = m_pTex2;	

	// create grid vertex buffer
	if(FAILED(hr = m_pd3dDevice->CreateVertexBuffer(
		VERTEX_GRID_DENSITY*VERTEX_GRID_DENSITY*sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_MANAGED, &m_pVBGrid)))
		return hr;

	// create index buffer
	if(FAILED(hr = m_pd3dDevice->CreateIndexBuffer(
		VERTEX_GRID_DENSITY*VERTEX_GRID_DENSITY*2*3*2,
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &m_pIBGrid)))
		return hr;

	

}
*/