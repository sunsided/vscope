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

	Dateiname:		texturewarpeffect.cpp
	Beschreibung:	TextureWarpEffect Definition
	Revision:		1
	Erstellt:		MMT, 19. Juli 2002 03:02

	Changelog:
	[1]		19. Juli 2002 03:02
			Erstellt

===========================================================================*/
/*
#include "texturewarpeffect.h"
#include "texturewarpeffect.inl.h"

#include "..\fastmath\fasttrig.h"
#include "..\fastmath\fastsqrt.h"
#include "..\vertices\vertices.h"

#pragma intrinsic(memcpy, memset)


void TEXTUREWARPEFFECT::SetupVertexGrid(LPDIRECT3DVERTEXBUFFER9 pVBGrid, int iGridWidth, int iGridHeight) {
	HRESULT hr;
	VSVERTEX_XYZ_TEX1 *pVertices;
	if(FAILED(hr = pVBGrid->Lock(0, iGridWidth*iGridHeight*sizeof(VSVERTEX_XYZ_TEX1), (BYTE**)&pVertices, 0))) {
		OutputDebugString("Uh-oh ... TEXTUREWARPEFFECT::SetupVertexGrid failed ...\n");
		return;
	}

	for(int x=0; x < iGridWidth; x++) {
		for(int y=0; y < iGridHeight; y++) {
			pVertices[(y*iGridWidth)+x].x = (((float)x/(float)(iGridWidth-1))*2.f)-1.f;
			pVertices[(y*iGridWidth)+x].y = (((float)(iGridHeight-1-y)/(iGridHeight-1))*2.f)-1.f;
			pVertices[(y*iGridWidth)+x].z = 0.f;
			pVertices[(y*iGridWidth)+x].tu = (float)x/(float)(iGridWidth-1);
			pVertices[(y*iGridWidth)+x].tv = (float)y/(float)(iGridHeight-1);

			// the jiggling
			float fRandAmtX = RandomNumber(-75, 11) / 50.f;
			float fRandAmtY = RandomNumber(-75, 11) / 50.f;
			pVertices[(y*iGridWidth)+x].tu += fRandAmtX/iGridWidth*2.f;
			pVertices[(y*iGridWidth)+x].tv += fRandAmtY/iGridHeight*2.f;
		}
	}

	if(FAILED(hr = pVBGrid->Unlock())) {
		OutputDebugString("Uh-oh ... TEXTUREWARPEFFECT::SetupVertexGrid failed at unlocking ...\n");
		return;
	}
}


void TEXTUREWARPEFFECT::ProcessBlendEffect(LPDIRECT3DDEVICE9 pd3dDevice,
                        LPDIRECT3DTEXTURE9 pOrigTex, LPDIRECT3DTEXTURE9 pDestTex,
                        LPDIRECT3DVERTEXBUFFER9 pVBGrid, LPDIRECT3DINDEXBUFFER8 pIBGrid,
                        int iTextureWidth,int iTextureHeight)
{
  SetupVertexGrid(pVBGrid, VERTEX_GRID_DENSITY, VERTEX_GRID_DENSITY);
  
  // get the current depth buffer (we have to pass this into SetRenderTarget
  // so we don't inadvertently drop our depth buffer.)
  LPDIRECT3DSURFACE9 pDepthSurf;
  pd3dDevice->GetDepthStencilSurface(&pDepthSurf);

  // get the current rendering target (we'll set it back later)
  LPDIRECT3DSURFACE9 pOldRenderTarget;
  pd3dDevice->GetRenderTarget(&pOldRenderTarget);

  // get surface interfaces for our textures, so we can set them as rendering
  // surfaces later.
  LPDIRECT3DSURFACE9 pDestSurf;
  pDestTex->GetSurfaceLevel(0, &pDestSurf);
  
  // set scratch surface active and clear it.
  // SetRenderTarget will also set our viewport so that it completely fills
  // pDestSurf.
  pd3dDevice->SetRenderTarget(pDestSurf, NULL);
  pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

  // Set up an orthagonal projection matrix, so we can render the entire
  // texture.
  D3DXMATRIX mat;
  D3DXMatrixOrthoLH(&mat, (float)iTextureWidth, (float)iTextureHeight, 
    0.0, 100.0);
  pd3dDevice->SetTransform( D3DTS_PROJECTION, &mat );

  // this world matrix, combined with orthogonal projection, causes the 
  // texture to completely and exactly fill the rendering surface.
  D3DXMATRIX matWorld,matTrans,matScale;
  D3DXMatrixScaling(&matScale, (float)iTextureWidth/2.0f, (float)iTextureHeight/2.0f, 1.0);

  // move the quad left and up 0.5 units, so that the texels are perfectly
  // centered on the screen pixels.
  D3DXMatrixMultiply(&matWorld, &matScale, D3DXMatrixTranslation(&matTrans, -0.5f, -0.5f, 0));

  // our matrix is now finished.  Tell D3D to use it!
  pd3dDevice->SetTransform( D3DTS_WORLD, &matScale );

  // Clear the backbuffer
  pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET,
                       0x00ff00, 1.0f, 0L );

  // begin rendering the scene
  if( SUCCEEDED( pd3dDevice->BeginScene() ) )
  {
    // no alpha blending
    pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
  
    // set our texture active...
    pd3dDevice->SetTexture( 0, pOrigTex );

    // set up our texture stages for a simple texture copy...
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );

    // draw our quad
    
    pd3dDevice->SetStreamSource( 0, pVBGrid, sizeof(CUSTOMVERTEX) );
    pd3dDevice->SetIndices(pIBGrid, 0);
    pd3dDevice->SetVertexShader( D3DFVF_CUSTOMVERTEX );
    pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 
      VERTEX_GRID_DENSITY*VERTEX_GRID_DENSITY, 0, VERTEX_GRID_DENSITY*VERTEX_GRID_DENSITY*2);
    

    // End the scene.
    pd3dDevice->EndScene();
  }

  // release the surface of the scratch texture.
  pDestSurf->Release();

  // set the rendering target back to the old target.
  pd3dDevice->SetRenderTarget(pOldRenderTarget, pDepthSurf);
  pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
  pOldRenderTarget->Release();

  // release the depth surface interface.
  pDepthSurf->Release();
}
*/