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

	Dateiname:		FireEffect.cpp
	Beschreibung:	FireEffect Definition
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 16:58

	Changelog:
	[1]		16. Juli 2002 16:58
			Erstellt

===========================================================================*/

#include "FireEffect.h"
#include "FireEffect.inl.h"

#include "..\fastmath\fastassort.h"
#pragma intrinsic(memcpy, memset)


unsigned char FIREEFFECT::m_FireRed[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,4,4,4,4,4,4,4,8,8,8,8,8,12,12,12,12,16,16,16,16,20,20,20,24,24,
  24,28,28,32,32,32,36,36,40,40,44,44,48,48,52,52,56,56,60,60,64,68,68,72,72,
  76,80,80,84,88,88,92,92,96,100,100,104,108,108,112,116,120,120,124,128,128,
  132,136,136,140,144,144,148,152,152,156,160,160,164,164,172,172,172,176,176,
  180,184,184,188,188,192,192,196,196,200,200,204,204,208,208,208,212,212,216,
  216,220,220,220,220,224,224,224,228,228,228,228,232,232,232,232,236,236,236,
  236,236,240,240,240,240,240,240,240,244,244,244,244,244,244,244,244,244,244,
  248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,
  248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,
  248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,
  248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,
  248,248,248,248,248};

unsigned char FIREEFFECT::m_FireGreen[256]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,8,8,8,8,
  8,8,8,8,8,12,12,12,12,12,12,16,16,16,16,16,16,20,20,20,20,20,24,24,24,24,28,
  28,28,28,32,32,32,32,36,36,36,36,40,40,40,44,44,44,48,48,48,52,52,52,56,56,
  56,60,60,60,64,64,64,68,68,72,72,72,76,76,80,80,80,84,84,84,88,88,92,92,92,
  96,96,100,100,104,104,104,108,108,112,112,116,116,116,120,120,124,124,128,
  128,128,132,132,136,136,140,140,140,144,144,148,148,148,152,152,156,156,160,
  160,163,164,164,168,168,168,172,172,172,176,176,180,180,180,184,184,184,188,
  188,188,192,192,192,196,196,200,200,200,200,200,204,204,204,208,208,208,208,
  212,212,212,212,216,216,216,216,220,220,220,220,220,224,224,224,224,224,228,
  228,228,228,228,228,232,232,232,232,232,232,236,236,236,236,236,236,236,236,
  240,240,240,240,240,240};

unsigned char FIREEFFECT::m_FireBlue[256]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,8,8,8,2,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,16,16,16,16,16,16,16,16,16,16,16,16,16,16,20,20,20,20,
  20,20,20,20,20,20,20,20,24,24,24,24,24,24,24,24,24,24,24,24,28,28,28,28,28,
  28,28,28,28,28,32,32,32,32,32,32,32,32,32,32,36,36,36,36,36,36,36,36,36,40,
  40,40,40,40,40,40,40,44,44,44,44,44};



bool FIREEFFECT::CopyToTexture() {
	HRESULT hr;

	D3DLOCKED_RECT lockedrect;
	memset(&lockedrect, 0, sizeof(D3DLOCKED_RECT));
	  
	if (FAILED(hr = m_pTexture->LockRect(0, &lockedrect, NULL, 0))) {
		dprintf("(FEHLER) FIREEFFECT internal: Textur kopieren. Fehler %X während Textur-Lock.\n", hr);
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
		dprintf("(FEHLER) FIREEFFECT internal: Textur kopieren. Fehler %X während Textur-Freigabe.\n", hr);
		return false;
	}
	return true;
}

void FIREEFFECT::Process() {
	//TODO: Dieser doppelte Loop kann als einzige Schleife dargestellt werden!

	int y, x;

	// loop through all the fire values...
	for (y=0; y < m_iTextureSize; y++) {
		for (x=0; x < m_iTextureSize; x++) {
			// these will store, temporarily, the fire values immediately to the
			// left, right, top, and bottom of this fire value.
			unsigned char firevalue_left, firevalue_right, firevalue_bottom, firevalue_top;
			int finalfirevalue;

			// x+-1 and y+-1 aren't always that simple; we must account for wrapping
			// around the horizontal edge (not vertical, however).
			// so we calculate x/y +- 1 and store them temporarily.
			int xplus1, xminus1, yplus1, yminus1;
			xplus1 = x+1; if (xplus1 >= m_iTextureSize) xplus1=0;
			xminus1= x-1; if (xminus1 < 0) xminus1 = m_iTextureSize-1;
			yplus1 = y+1; if (yplus1 >= m_iTextureSize) yplus1=m_iTextureSize-1;
			yminus1= y-1; if (yminus1 < 0) yminus1 = 0;
		      
			// now we can get the fire values of the neighboring pixels
			int yTex = y * m_iTextureSize;
			int yTexM1X = (yminus1 * m_iTextureSize) + x;
			firevalue_right = m_pActiveBuffer[yTex + xplus1];
			firevalue_left  = m_pActiveBuffer[yTex + xminus1];
			firevalue_bottom= m_pActiveBuffer[(yplus1 * m_iTextureSize)+x];
			firevalue_top   = m_pActiveBuffer[yTexM1X];

			// now, the most important part-  calculate the new fire value..
			finalfirevalue = (int)((firevalue_left + firevalue_right + firevalue_top + firevalue_bottom) * VAL1d4);

			// subtract a certain amount to simulate the fire "cooling."
			// this is where you'd apply your cooling map.
			finalfirevalue -= m_iCoolAmount;

			// make sure that the subtraction of the coolamount didn't take us
			// below zero.
			if (finalfirevalue < 0) finalfirevalue = 0;

			// store the fire value on the scratch array, up one line from where
			// it originally was.  This simulates the flames rising.
			m_pScratchBuffer[yTexM1X] = finalfirevalue;
		}
	}

	// add fuel to the fire.  This particular fueling method is one of my
	// favorite; it creates little jet streams of flame.

	//TODO: Dieser einfache Loop kann als einzige Schleife dargestellt werden!

	y = m_iTextureSize-1;
	int yTex = (y*m_iTextureSize);

	// we work in blocks of 2x1...
	for (x=0; x < m_iTextureSize; x+=2) {
		// we add fuel only to the last row.
		int yTexX = yTex + x;
	    
		// determine whether this particular spot gets fuel added or taken
		// away from it, by adding a number between (-31..31)
		int fuel = m_pActiveBuffer[yTexX] + (rand() % 64) - 32;

		// we must be between 0-255.
		if (fuel > 255) fuel = 255;
		if (fuel < 0) fuel = 0;

		// apply the new fuel value to two adjacent pixels.  This helps reduce
		// the "dithering" effect that the fire is prone to.
		m_pScratchBuffer[yTexX] = (unsigned char)fuel;
		m_pScratchBuffer[yTexX + 1] = (unsigned char)fuel;
	}

}
