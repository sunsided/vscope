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

	Dateiname:		flagwrapeffect.cpp
	Beschreibung:	FlagWrapEffect
	Revision:		1
	Erstellt:		MMT, 17. Juli 2002 19:52

	Changelog:
	[1]		17. Juli 2002 19:52
			Erstellt

===========================================================================*/

#include "flagwrapeffect.h"
#include "flagwrapeffect.inl.h"
#include "..\fastmath\fasttrig.h"

#include <mmsystem.h>

#pragma intrinsic(memcpy, memset)

void FLAGWRAPEFFECT::ProcessFlag() {
	D3DLOCKED_RECT rect_src, rect_dest;
	memset(&rect_src, 0, sizeof(rect_src));
	memset(&rect_dest, 0, sizeof(rect_dest));

	HRESULT hr;
	if (FAILED(hr = this->m_pInputTex->LockRect(0, &rect_src, NULL, D3DLOCK_READONLY))) {
		dprintf("(FEHLER) FLAGWRAPEFFECT internal: Flagge erstellen. Fehler %X während Textur-Lock 1.\n", hr);
		return;
	}

	if (FAILED(hr = m_pFlagTex->LockRect(0, &rect_dest, NULL, 0))) {
		dprintf("(FEHLER) FLAGWRAPEFFECT internal: Flagge erstellen. Fehler %X während Textur-Lock 2.\n", hr);
		return;
	}


	int Phase = (int)((float)timeGetTime() * VAL1d10);    // animate the sine wave slowly
	
	DWORD *pSrc = (DWORD *)(rect_src.pBits);
	DWORD *pDest= (DWORD *)(rect_dest.pBits);

	int src_pitch = rect_src.Pitch / 4; // in DWORDS
	int iTraverse = (rect_dest.Pitch - (m_iTextureSize*4)) / 4;
	DWORD Pixel;
	int index = 0;

    for (int y=0; y < m_iTextureSize; y++) {
        for (int x=0; x < m_iTextureSize; x++) {
            int SrcXDelta = this->m_SinLUT[(y + Phase) & 127] >> 1;
            int SrcX = x + SrcXDelta;
            int SrcYDelta = this->m_SinLUT[(x + Phase) & 127];
            int SrcY = y + SrcYDelta;

			if(SrcY <0 ) SrcY = m_iTextureSize + SrcY;
			if(SrcX <0 ) SrcX = m_iTextureSize + SrcX;
			if(SrcY >=m_iTextureSize ) SrcY = SrcY - m_iTextureSize;
			if(SrcX >=m_iTextureSize ) SrcX = SrcX - m_iTextureSize;

			if (SrcY < 0 || SrcY >= m_iTextureSize || SrcX < 0 || SrcX >= m_iTextureSize)
                Pixel = 0;
			else
				Pixel = pSrc[SrcY * src_pitch + SrcX];
			pDest[index++] = Pixel;

        }
		index += iTraverse;
    }


	if (FAILED(hr = this->m_pInputTex->UnlockRect(0))) {
		dprintf("(FEHLER) FLAGWRAPEFFECT internal: Flagge erstellen. Fehler %X während Textur-Unlock 1.\n", hr);
		return;
	}

	if (FAILED(hr = m_pFlagTex->UnlockRect(0))) {
		dprintf("(FEHLER) FLAGWRAPEFFECT internal: Flagge erstellen. Fehler %X während Textur-Unlock 2.\n", hr);
		return;
	}

}