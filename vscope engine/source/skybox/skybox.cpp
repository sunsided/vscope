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

	Dateiname:		skybox.cpp
	Beschreibung:	Skybox
	Revision:		3
	Erstellt:		MMT, 10. Juli 2002 18:09

	Changelog:
	[3]		17. Juli 2002 19:19 MMT
			SKYBOX_STRICT
	[2]		15. Juli 2002 00:40 MMT
			Der Konstruktor ruft Create() auf.
	[1]		10. Juli 2002 18:09
			Erstellt

===========================================================================*/

#include "skybox.h"
#include "skybox.inl.h"
#include "..\vektoren\vector3.h"
#include "..\matrix\matrix4.h"
#include "..\viewcone\viewcone.h"
#include "..\vertices\vertices.h"
#include "..\common\common.h"
#include "..\bounding\aabbox.h"
#include "..\enums-math.h"
#include "..\matrix\matrix4.inl.h"
#include "..\piped3d2\piped3d2.h"
#include "..\piped3d2\piped3d2.inl.h"

#pragma intrinsic(memset, memcpy)

SKYBOX::SKYBOX() {
	this->m_fWidth = 100;
	this->m_fFilter = D3DTEXF_ANISOTROPIC;
	this->m_skyVB = NULL;
	memset(this->m_skyVertices, 0, sizeof(this->m_skyVertices));
	/*
	this->m_Texture[0] = NULL;	this->m_Texture[1] = NULL;	this->m_Texture[2] = NULL;
	this->m_Texture[3] = NULL;	this->m_Texture[4] = NULL;	this->m_Texture[5] = NULL;
	*/
	memset(this->m_Texture, 0, sizeof(LPDIRECT3DTEXTURE9)*6);
	this->m_pPipe = NULL;
}

SKYBOX::SKYBOX(PIPED3D2 &in_pPipe) {
	this->m_pPipe = &in_pPipe;
	this->m_fWidth = 100;
	this->m_fFilter = D3DTEXF_ANISOTROPIC;
	this->m_skyVB = NULL;
	memset(this->m_skyVertices, 0, sizeof(this->m_skyVertices));
	/*
	this->m_Texture[0] = NULL;	this->m_Texture[1] = NULL;	this->m_Texture[2] = NULL;
	this->m_Texture[3] = NULL;	this->m_Texture[4] = NULL;	this->m_Texture[5] = NULL;
	*/
	memset(this->m_Texture, 0, sizeof(LPDIRECT3DTEXTURE9)*6);
	Create(in_pPipe, m_fWidth);
}

SKYBOX::SKYBOX(PIPED3D2 &in_pPipe, const float Width) {
	this->m_fWidth = Width;
	this->m_fFilter = D3DTEXF_ANISOTROPIC;
	this->m_skyVB = NULL;
	memset(this->m_skyVertices, 0, sizeof(this->m_skyVertices));
	/*
	this->m_Texture[0] = NULL;	this->m_Texture[1] = NULL;	this->m_Texture[2] = NULL;
	this->m_Texture[3] = NULL;	this->m_Texture[4] = NULL;	this->m_Texture[5] = NULL;
	*/
	memset(this->m_Texture, 0, sizeof(LPDIRECT3DTEXTURE9)*6);
	this->m_pPipe = &in_pPipe;
	Create(in_pPipe, Width);
}

SKYBOX::SKYBOX(PIPED3D2 &in_pPipe, const float Width, const LPDIRECT3DTEXTURE9 *Textures) {
	this->m_fWidth = Width;
	this->m_fFilter = D3DTEXF_ANISOTROPIC;
	this->m_skyVB = NULL;
	this->SetTextures(Textures);
	this->m_pPipe = &in_pPipe;
	Create(in_pPipe, m_fWidth);
}

SKYBOX::SKYBOX(PIPED3D2 &in_pPipe, const float Width, const LPDIRECT3DTEXTURE9 texFront, const LPDIRECT3DTEXTURE9 texRight, const LPDIRECT3DTEXTURE9 texBack, const LPDIRECT3DTEXTURE9 texLeft, const LPDIRECT3DTEXTURE9 texTop, const LPDIRECT3DTEXTURE9 texBottom) {
	this->m_fWidth = Width;
	this->m_fFilter = D3DTEXF_ANISOTROPIC;
	this->m_skyVB = NULL;
	memset(this->m_skyVertices, 0, sizeof(this->m_skyVertices));
	this->m_Texture[0] = texFront;
	this->m_Texture[1] = texRight;
	this->m_Texture[2] = texBack;
	this->m_Texture[3] = texLeft;
	this->m_Texture[4] = texTop;
	this->m_Texture[5] = texBottom;
	this->m_pPipe = &in_pPipe;
	Create(in_pPipe, m_fWidth);
}

SKYBOX::~SKYBOX() {
	this->Release();
}

void VSFASTCALL SKYBOX::Release(BOOL AlsoReleaseTextures) {
	SAFE_RELEASE(this->m_skyVB);
	if(AlsoReleaseTextures) {
		SAFE_RELEASE(this->m_Texture[0]);
		SAFE_RELEASE(this->m_Texture[1]);
		SAFE_RELEASE(this->m_Texture[2]);
		SAFE_RELEASE(this->m_Texture[3]);
		SAFE_RELEASE(this->m_Texture[4]);
		SAFE_RELEASE(this->m_Texture[5]);
	}
}

HRESULT VSFASTCALL SKYBOX::Create(PIPED3D2 &in_pPipe) {
	float fMax =  1.f * this->m_fWidth;
	float fMin = -1.f * this->m_fWidth;

	//Vorn
	m_skyVertices[0] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMax, 0, 1);
	m_skyVertices[1] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMax, 0, 0);
	m_skyVertices[2] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMax, 1, 1);
	m_skyVertices[3] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMax, 1, 0);

	//Rechts
	m_skyVertices[4] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMax, 0, 1);
	m_skyVertices[5] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMax, 0, 0);
	m_skyVertices[6] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMin, 1, 1);
	m_skyVertices[7] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMin, 1, 0);

	//Hinten
	m_skyVertices[8] =  VSVERTEX_XYZ_TEX1( fMax, fMin, fMin, 0, 1);
	m_skyVertices[9] =  VSVERTEX_XYZ_TEX1( fMax, fMax, fMin, 0, 0);
	m_skyVertices[10] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMin, 1, 1);
	m_skyVertices[11] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMin, 1, 0);

	//Links
	m_skyVertices[12] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMin, 0, 1);
	m_skyVertices[13] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMin, 0, 0);
	m_skyVertices[14] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMax, 1, 1);
	m_skyVertices[15] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMax, 1, 0);

	//Oben
	m_skyVertices[16] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMax, 0, 1);
	m_skyVertices[17] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMin, 0, 0);
	m_skyVertices[18] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMax, 1, 1);
	m_skyVertices[19] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMin, 1, 0);

	//Unten
	m_skyVertices[20] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMin, 0, 1);
	m_skyVertices[21] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMax, 0, 0);
	m_skyVertices[22] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMin, 1, 1);
	m_skyVertices[23] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMax, 1, 0);

	if(FAILED(in_pPipe.GetDirect3DDevice()->CreateVertexBuffer(sizeof(m_skyVertices), D3DUSAGE_WRITEONLY, VSFVF_XYZ_TEX1, D3DPOOL_DEFAULT, &m_skyVB, NULL)))
		return -1;

	void*	ptr;
	if(FAILED(m_skyVB->Lock(0, sizeof(this->m_skyVertices), (void**)&ptr, 0)))
		return -2;
	memcpy(ptr, this->m_skyVertices, sizeof(this->m_skyVertices));
	m_skyVB->Unlock();

	this->m_pPipe = &in_pPipe;

	return 0;
}

HRESULT VSFASTCALL SKYBOX::Create(PIPED3D2 &in_pPipe, const float Width) {
	this->m_fWidth = Width;
	float fMax =  1.f * Width;
	float fMin = -1.f * Width;

	//Vorn
	m_skyVertices[0] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMax, 0, 1);
	m_skyVertices[1] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMax, 0, 0);
	m_skyVertices[2] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMax, 1, 1);
	m_skyVertices[3] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMax, 1, 0);

	//Rechts
	m_skyVertices[4] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMax, 0, 1);
	m_skyVertices[5] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMax, 0, 0);
	m_skyVertices[6] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMin, 1, 1);
	m_skyVertices[7] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMin, 1, 0);

	//Hinten
	m_skyVertices[8] =  VSVERTEX_XYZ_TEX1( fMax, fMin, fMin, 0, 1);
	m_skyVertices[9] =  VSVERTEX_XYZ_TEX1( fMax, fMax, fMin, 0, 0);
	m_skyVertices[10] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMin, 1, 1);
	m_skyVertices[11] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMin, 1, 0);

	//Links
	m_skyVertices[12] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMin, 0, 1);
	m_skyVertices[13] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMin, 0, 0);
	m_skyVertices[14] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMax, 1, 1);
	m_skyVertices[15] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMax, 1, 0);

	//Oben
	m_skyVertices[16] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMax, 0, 1);
	m_skyVertices[17] = VSVERTEX_XYZ_TEX1( fMin, fMax, fMin, 0, 0);
	m_skyVertices[18] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMax, 1, 1);
	m_skyVertices[19] = VSVERTEX_XYZ_TEX1( fMax, fMax, fMin, 1, 0);

	//Unten
	m_skyVertices[20] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMin, 0, 1);
	m_skyVertices[21] = VSVERTEX_XYZ_TEX1( fMin, fMin, fMax, 0, 0);
	m_skyVertices[22] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMin, 1, 1);
	m_skyVertices[23] = VSVERTEX_XYZ_TEX1( fMax, fMin, fMax, 1, 0);

	if(FAILED(in_pPipe.GetDirect3DDevice()->CreateVertexBuffer(sizeof(m_skyVertices), D3DUSAGE_WRITEONLY, VSFVF_XYZ_TEX1, D3DPOOL_DEFAULT, &m_skyVB, NULL)))
		return -1;

	void*	ptr;
	if(FAILED(m_skyVB->Lock(0, sizeof(this->m_skyVertices), (void**)&ptr, 0)))
		return -2;
	memcpy(ptr, this->m_skyVertices, sizeof(this->m_skyVertices));
	m_skyVB->Unlock();
	
	this->m_pPipe = &in_pPipe;

	return 0;
}

int VSFASTCALL SKYBOX::Render(const float cameraX, const float cameraY, const float cameraZ) {
	MATRIX4 matWelt;

	//this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pPipe->SelectCullCCW();
	DWORD addU, addV;
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_ADDRESSU, &addU);
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_ADDRESSV, &addV);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	
	DWORD MagFilter, MinFilter, MipFilter;
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_MAGFILTER, &MagFilter);
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_MINFILTER, &MinFilter);
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_MIPFILTER, &MipFilter);

	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, this->m_fFilter);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, this->m_fFilter);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, this->m_fFilter);

	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	matWelt.Translation(cameraX, cameraY, cameraZ);
	//this->m_pd3dDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&matWelt);
	m_pPipe->SetWorldMatrix(&matWelt);

	//this->m_pPipe->GetDirect3DDevice()->SetVertexShader(VSFVF_XYZ_TEX1);
	this->m_pPipe->GetDirect3DDevice()->SetVertexShader(NULL);
	this->m_pPipe->GetDirect3DDevice()->SetFVF(VSFVF_XYZ_TEX1);
	this->m_pPipe->GetDirect3DDevice()->SetStreamSource(0, this->m_skyVB, 0, sizeof(VSVERTEX_XYZ_TEX1));

	for(int i=0; i<6; i++) {
		#ifndef SKYBOX_STRICT
		if(this->m_Texture[i]) this->m_pPipe->GetDirect3DDevice()->SetTexture(0, this->m_Texture[i]);
		#else
		this->m_pPipe->GetDirect3DDevice()->SetTexture(0, this->m_Texture[i]);
		#endif
		this->m_pPipe->GetDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4, 2);
	}

	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, addU);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, addV);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, MagFilter);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, MinFilter);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, MipFilter);

	return 12; // Triangles
}

int VSFASTCALL SKYBOX::Render(const VIEWCONE *ViewCone, const float cameraX, const float cameraY, const float cameraZ) {
	MATRIX4 matWelt;
	UINT Count = 0;

	//this->m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pPipe->SelectCullCCW();
	DWORD addU, addV;
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_ADDRESSU, &addU);
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_ADDRESSV, &addV);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	
	DWORD MagFilter, MinFilter, MipFilter;
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_MAGFILTER, &MagFilter);
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_MINFILTER, &MinFilter);
	this->m_pPipe->GetDirect3DDevice()->GetSamplerState(0, D3DSAMP_MIPFILTER, &MipFilter);

	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, this->m_fFilter);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, this->m_fFilter);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, this->m_fFilter);

	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	matWelt.Translation(cameraX, cameraY, cameraZ);
	//this->m_pd3dDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&matWelt);
	m_pPipe->SetWorldMatrix(&matWelt);

	//this->m_pPipe->GetDirect3DDevice()->SetVertexShader(VSFVF_XYZ_TEX1);
	this->m_pPipe->GetDirect3DDevice()->SetVertexShader(NULL);
	this->m_pPipe->GetDirect3DDevice()->SetFVF(VSFVF_XYZ_TEX1);
	this->m_pPipe->GetDirect3DDevice()->SetStreamSource(0, this->m_skyVB, 0, sizeof(VSVERTEX_XYZ_TEX1));

	for(int i=0; i<6; i++) {

		// Alle vier Eckpunkte der Skybox auf Sichtbarkeit prüfen.
		// Wenn alle nicht drin sind, wird die Box wohl nicht sichtbar sein ...
		VECTOR3 min;
		min.x = MIN(this->m_skyVertices[i*4+0].x, MIN3(this->m_skyVertices[i*4+1].x, this->m_skyVertices[i*4+2].x, this->m_skyVertices[i*4+3].x));
		min.y = MIN(this->m_skyVertices[i*4+0].y, MIN3(this->m_skyVertices[i*4+1].y, this->m_skyVertices[i*4+2].y, this->m_skyVertices[i*4+3].y));
		min.z = MIN(this->m_skyVertices[i*4+0].z, MIN3(this->m_skyVertices[i*4+1].z, this->m_skyVertices[i*4+2].x, this->m_skyVertices[i*4+3].z));
		VECTOR3 max;
		max.x = MAX(this->m_skyVertices[i*4+0].x, MAX3(this->m_skyVertices[i*4+1].x, this->m_skyVertices[i*4+2].x, this->m_skyVertices[i*4+3].x));
		max.y = MAX(this->m_skyVertices[i*4+0].y, MAX3(this->m_skyVertices[i*4+1].y, this->m_skyVertices[i*4+2].y, this->m_skyVertices[i*4+3].y));
		max.z = MAX(this->m_skyVertices[i*4+0].z, MAX3(this->m_skyVertices[i*4+1].z, this->m_skyVertices[i*4+2].x, this->m_skyVertices[i*4+3].z));
		AABBOX3 Box(min, max);

		LOCATION Loc = ViewCone->GetLocation(Box);
		if(Loc == LOC_INSIDE || Loc == LOC_SPLIT) {
			#ifndef SKYBOX_STRICT
			if(this->m_Texture[i]) this->m_pPipe->GetDirect3DDevice()->SetTexture(0, this->m_Texture[i]);
			#else
			this->m_pPipe->GetDirect3DDevice()->SetTexture(0, this->m_Texture[i]);
			#endif
			this->m_pPipe->GetDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4, 2);
			Count+=2;
		}
	}

	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, addU);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, addV);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, MagFilter);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, MinFilter);
	this->m_pPipe->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, MipFilter);

	return Count;	// Anzahl Triangles
}