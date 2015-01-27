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

	Dateiname:		PerlinNoiseEffect.cpp
	Beschreibung:	PerlinNoiseEffect Definition
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 21:25

	Changelog:
	[1]		16. Juli 2002 21:25
			Erstellt

===========================================================================*/

#include "PerlinNoiseEffect.h"
#include "PerlinNoiseEffect.inl.h"

#include "..\perlinnoise\perlinnoise.h"
#include "..\perlinnoise\perlinnoise.inl.h"

#include "..\fastmath\fastassort.h"
#pragma intrinsic(memcpy, memset)


bool PERLINNOISEEFFECT::CopyToTexture() {
	HRESULT hr;

	D3DLOCKED_RECT lockedrect;
	memset(&lockedrect, 0, sizeof(D3DLOCKED_RECT));
	  
	if (FAILED(hr = m_pTexture->LockRect(0, &lockedrect, NULL, 0))) {
		dprintf("(FEHLER) PERLINNOISEEFFECT internal: Textur kopieren. Fehler %X während Textur-Lock.\n", hr);
		return false;
	}
	  
	// our texture surface is now locked, and we can use the pitch to traverse it.
	unsigned char *pSurfBits = static_cast<unsigned char *>(lockedrect.pBits);
	  
	int index=0;
	int iTraverse = lockedrect.Pitch - (m_iTextureSize*4);
	  
	for (int y=0; y < m_iTextureSize; y++) {
		for (int x=0; x < m_iTextureSize; x++) {
			// the fire value at this position determines the color of this texel
		
			//TODO: Dieser doppelte Loop kann als einzige Schleife dargestellt werden!

			pSurfBits[index++] = m_Palette[m_pActiveBuffer[(y*m_iTextureSize)+x]].peBlue; // blue
			pSurfBits[index++] = m_Palette[m_pActiveBuffer[(y*m_iTextureSize)+x]].peGreen; // green
			pSurfBits[index++] = m_Palette[m_pActiveBuffer[(y*m_iTextureSize)+x]].peRed; // red
			pSurfBits[index++] = m_Palette[m_pActiveBuffer[(y*m_iTextureSize)+x]].peFlags; // alpha
		}
		// next line
		index += iTraverse;
	}

	// unlock texture surface
	if (FAILED(hr = m_pTexture->UnlockRect(0))) {
		dprintf("(FEHLER) PERLINNOISEEFFECT internal: Textur kopieren. Fehler %X während Textur-Freigabe.\n", hr);
		return false;
	}
	return true;
}


void PERLINNOISEEFFECT::Process() {
	//TODO: Dieser doppelte Loop kann als einzige Schleife dargestellt werden!

	int y, x;
	m_Generator.Init(m_fPersistence, m_fOctaves);

	float fSeedX = frand_1((unsigned int)(m_fSeed * 3.f));
	float t = frand_1((unsigned int)(m_fSeed * m_fSeed));
	if(t==1.f)t=1.f;
	float fSeedY = (fSeedX / t) + frand_1((unsigned int)(m_fSeed * 19.f));

	// loop through all the fire values...
	for (y=0; y < m_iTextureSize; y++) {
		for (x=0; x < m_iTextureSize; x++) {
			m_pScratchBuffer[(y * m_iTextureSize) + x] = (unsigned char)(m_Generator.GetNoise((float)x + fSeedX, (float)y + fSeedY) * 255.f);
		}
	}
}


void PERLINNOISEEFFECT::Process(const float fTreshold) {
	//TODO: Dieser doppelte Loop kann als einzige Schleife dargestellt werden!

	m_Generator.Init(m_fPersistence, m_fOctaves);

	int y, x;
	float noise;
	float fSeedX = frand_1((unsigned int)(m_fSeed * 3.f));
	float t = frand_1((unsigned int)(m_fSeed * m_fSeed));
	if(t<1.f)t=1.f;
	float fSeedY = (fSeedX / t) + frand_1((unsigned int)(m_fSeed * 19.f));

	// loop through all the fire values...
	for (y=0; y < m_iTextureSize; y++) {
		for (x=0; x < m_iTextureSize; x++) {
			noise = m_Generator.GetNoise((float)x + fSeedX, (float)y + fSeedY);
			if(noise<=fTreshold) noise = 0.f;
			m_pScratchBuffer[(y * m_iTextureSize) + x] = (unsigned char)(noise * 255.f);
		}
	}
}