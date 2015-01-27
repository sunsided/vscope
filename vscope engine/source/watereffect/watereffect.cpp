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

	Dateiname:		watereffect.cpp
	Beschreibung:	WaterEffect Definition
	Revision:		1
	Erstellt:		MMT, 16. Juli 2002 21:25

	Changelog:
	[1]		16. Juli 2002 21:25
			Erstellt

===========================================================================*/

#include "watereffect.h"
#include "watereffect.inl.h"

#include "..\fastmath\fasttrig.h"
#include "..\fastmath\fastsqrt.h"

#pragma intrinsic(memcpy, memset)


/****************************************************************************

 MakeDisplacementLookupTable: populates our m_cDisplacement map with valid
 values based on a refraction index.  The refraction index of water is 2.0.

 ****************************************************************************/
void WATEREFFECT::MakeDisplacementLookupTable() {
	int iArraySizeH = sizeof(this->m_lutDisplacement) / 2;
	float fInvRefract = 1.f / m_fRefraction;
	for (int i=-iArraySizeH; i < (iArraySizeH)-1; i++) {
		float heightdiff = i*m_fDepth;
		float angle = (float)fastatan(heightdiff);
		float beamangle = (float)fastasin(fastsin(angle) * fInvRefract);
		this->m_lutDisplacement[i+iArraySizeH] = (int)(fasttan(beamangle) * heightdiff);
	  }
}

/****************************************************************************

 ProcessWater: this function processes our water.  It takes two input buffers,
 the water dimensions, and the cooling amount.  It calculates the new water
 values from waterfield1 and puts them into waterfield2.

 ****************************************************************************/
void WATEREFFECT::ProcessWater() {
	float fInvDamp = 1.f / 1.05f; // m_fDamp

	// loop through all the water values...
	for (int y=0; y < m_iTextureSize; y++) {
		int yTex = y * m_iTextureSize;

		for (int x=0; x < m_iTextureSize; x++) {

			// add up the values of all the neighboring water values...
			int value;
			int xminus1 = x-1; if (xminus1 < 0) xminus1 = 0;
			int xminus2 = x-2; if (xminus2 < 0) xminus2 = 0;
			int yminus1 = y-1; if (yminus1 < 0) yminus1 = 0;
			int yminus2 = y-2; if (yminus2 < 0) yminus2 = 0;

			int xplus1 = x+1; if (xplus1 >= m_iTextureSize) xplus1 = m_iTextureSize-1;
			int xplus2 = x+2; if (xplus2 >= m_iTextureSize) xplus2 = m_iTextureSize-1;
			int yplus1 = y+1; if (yplus1 >= m_iTextureSize) yplus1 = m_iTextureSize-1;
			int yplus2 = y+2; if (yplus2 >= m_iTextureSize) yplus2 = m_iTextureSize-1;

			//////////////////////////
			//
			// Blending methods: uncomment one of these two methods.
			//
			//////////////////////////

			// Method 1: Slower but yields slightly better looking water
			{
				
				//value  = (float)m_pWaterScratch[(yTex)+xminus1];
				//value += (float)m_pWaterScratch[(yTex)+xminus2];
				//value += (float)m_pWaterScratch[(yTex)+xplus1];
				//value += (float)m_pWaterScratch[(yTex)+xplus2];
				//value += (float)m_pWaterScratch[((yminus1)*m_iTextureSize)+x];
				//value += (float)m_pWaterScratch[((yminus2)*m_iTextureSize)+x];
				//value += (float)m_pWaterScratch[((yplus1) *m_iTextureSize)+x];
				//value += (float)m_pWaterScratch[((yplus2) *m_iTextureSize)+x];
				//value += (float)m_pWaterScratch[((yminus1)*m_iTextureSize)+xminus1];
				//value += (float)m_pWaterScratch[((yminus1)*m_iTextureSize)+xplus1];
				//value += (float)m_pWaterScratch[((yplus1) *m_iTextureSize)+xminus1];
				//value += (float)m_pWaterScratch[((yplus1) *m_iTextureSize)+xplus1];
				//
				//// average them
				//value /= 6;
				
			}

			// Method 2: This method is faster but doesn't look as good (IMHO)
			{
				value  = m_pWaterScratch[(yTex)+xminus1];
				value += m_pWaterScratch[(yTex)+xplus1];
				value += m_pWaterScratch[((yminus1)*m_iTextureSize)+x];
				value += m_pWaterScratch[((yplus1) *m_iTextureSize)+x];
				
				// average them (/4) then multiply by two 
				// so they don't die off as quickly.
				value = (int)((float)value * 0.5f);
			}

			////////////////////////
			//
			// regardless of the blending method we choose, we still must
			// do this stuff.
			//
			////////////////////////
			    
			// subtract the previous water value
			value -= m_pWaterActive[(yTex)+x];

			// dampen it!
			value = (int)((float)value * fInvDamp);

			// store it in array
			m_pWaterActive[(yTex)+x] = value;
		}
	}
			
	/* unremark this section of code to create a eastbound current
	for (y=0; y < m_iTextureSize; y++) {
		for (int x=m_iTextureSize-1; x >= 0; x--) {
			int xminus1 = x ? x-1 : m_iTextureSize-1; // wrap around
			m_pWaterActive[(y*m_iTextureSize)+x] = m_pWaterActive[(y*m_iTextureSize)+xminus1];
		}
	}

	for (y=0; y < m_iTextureSize; y++) {
		for (int x=m_iTextureSize-1; x >= 1; x--) {
			int xminus1 = x ? x-1 : m_iTextureSize-1; // wrap around
			m_pWaterScratch[(y*m_iTextureSize)+x] = m_pWaterScratch[(y*m_iTextureSize)+xminus1];
		}
	}
	*/
}

void VSFASTCALL WATEREFFECT::CreateWaterDroplet(int iX, int iY, int iSize, int iSplashStrength, int *waterbuf, int iWaterWidth, int iWaterHeight) {
	int square_size = iSize*iSize;
	int iXiSize = iX+iSize;
	int iYiSize = iY+iSize;

	for (int x=iX-iSize; x <= iXiSize; x++) {
		for (int y=iY-iSize; y <= iYiSize; y++) {
			// make sure we're in bounds
			if (x < 0 || x >= iWaterWidth || y < 0 || y >= iWaterHeight) continue;
				
			// see if the point at (x,y) is within the circle of radius size
			int xiX = (x-iX);
			int yiY = (y-iY);
			int square_x    = (xiX)*(xiX);
			int square_y    = (yiY)*(yiY);
			
			if (square_x+square_y <= square_size) {
				// it's within the size circle!  apply it to the water buffer.
				waterbuf[(y*iWaterWidth)+x] += (int)((float)iSplashStrength)*(int)fastsqrt((float)square_x+(float)square_y);
			}
		}
	}
}

HRESULT WATEREFFECT::ProcessTexture() {
	HRESULT hr;

	// lock texture
	D3DLOCKED_RECT rect_src, rect_dest;
	memset(&rect_src, 0, sizeof(rect_src));
	memset(&rect_dest, 0, sizeof(rect_dest));
	  
	if (FAILED(hr = m_pImageTex->LockRect(0, &rect_src, NULL, 0))) return(hr);
	if (FAILED(hr = m_pWaterTex->LockRect(0, &rect_dest, NULL, 0))) return(hr);
	  
	// our texture surface is now locked, and we can use the pitch to traverse it.
	DWORD *pSrc = (DWORD *)(rect_src.pBits);
	DWORD *pDest= (DWORD *)(rect_dest.pBits);
	  
	int dest_index=0;
	int src_pitch = rect_src.Pitch / 4; // in DWORDS
	int iTraverse = (rect_dest.Pitch - (m_iTextureSize*4)) / 4;

	int TexM1 = m_iTextureSize-1;
	  
	// this could be optimized a LOT.  It's this way so you can learn the technique.
	for (int y=0; y < m_iTextureSize; y++) {

		int yTex = y*m_iTextureSize;
		int y1Tex = (y+1)*m_iTextureSize;

		for (int x=0; x < m_iTextureSize; x++) {

			int yTexX = yTex + x;
			int y1TexX = y1Tex + x;

			//int xdiff = (x == TexM1) ? 0 : m_pWaterActive[yTexX+1]  - m_pWaterActive[yTexX];
			int xdiff = 0;
			if (x != TexM1) xdiff = m_pWaterActive[yTexX+1]  - m_pWaterActive[yTexX];
			//int ydiff = (y == TexM1) ? 0 : m_pWaterActive[y1TexX]   - m_pWaterActive[yTexX];
			int ydiff = 0;
			if (y != TexM1) ydiff = m_pWaterActive[y1TexX]   - m_pWaterActive[yTexX];
		      
			int xdisp = m_lutDisplacement[(xdiff+256) % 512];
			int ydisp = m_lutDisplacement[(ydiff+256) % 512];

			int ymydisp = y-ydisp;
			int ypydisp = y+ydisp;
			int xmxdisp = x-xdisp;
			int xpxdisp = x+xdisp;

			if (xdiff < 0) {
				if (ydiff < 0) {
					if (ymydisp < 0 || ymydisp >= m_iTextureSize || xmxdisp < 0 || xmxdisp >= m_iTextureSize) {
						pDest[dest_index++] = pSrc[0];   
						continue;
					} else {
						pDest[dest_index++] = pSrc[((ymydisp)*src_pitch)+xmxdisp];  
						continue;
					}
				} else {
					if (ypydisp < 0 || ypydisp >= m_iTextureSize || xmxdisp < 0 || xmxdisp >= m_iTextureSize) {
						pDest[dest_index++] = pSrc[0];    
						continue;
					} else {
						pDest[dest_index++] = pSrc[((ypydisp)*src_pitch)+xmxdisp];  
						continue;
					}
				}
			} else {
				if (ydiff < 0) {
					if (ymydisp < 0 || ymydisp >= m_iTextureSize || xpxdisp < 0 || xpxdisp >= m_iTextureSize) {
						pDest[dest_index++] = pSrc[0];    
						continue;
					} else {
						pDest[dest_index++] = pSrc[((ymydisp)*src_pitch)+xpxdisp];  
						continue;
					}
				} else {
					if (ypydisp < 0 || ypydisp >= m_iTextureSize || xpxdisp < 0 || xpxdisp >= m_iTextureSize) {
						pDest[dest_index++] = pSrc[0];    
						continue;
					} else {
						pDest[dest_index++] = pSrc[((ypydisp)*src_pitch)+xpxdisp];  
						continue;
					}
				}
			}
		}
		// next line
		dest_index += iTraverse;
	}

	// unlock texture surface
	if (FAILED(hr = m_pImageTex->UnlockRect(0))) return(hr);
	if (FAILED(hr = m_pWaterTex->UnlockRect(0))) return(hr);

	return S_OK;
}