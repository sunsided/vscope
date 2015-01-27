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

	Dateiname:		piped3d2.inl.h
	Beschreibung:	Direct3D-Pipeline 2 Inline-Funktionen
	Revision:		2
	Erstellt:		MMT, 14. Juli 2002 19:16

	Changelog:
	[2]		17. Juli 2002 20:38 MMT
			RenderTarget-Funktionen und Gamma
	[1]		14. Juli 2002 19:16
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\common\common.h"
#include "piped3d2.h"
#include "..\piped3d\pipedescriptor.h"
#include "..\include-windows.h"
#include "..\include-direct3d.h"
#include "..\matrix\matrix4.inl.h"
#include "..\debug\debug.h"
#include "..\material\material.inl.h"

#pragma intrinsic(memset, memcpy)


/*------------------------------------------------------------
/|	Funktion:		IsInitialized()
/|	Beschreibung:	Gibt an, ob das Objekt initialisiert wurde
/|	Parameter:		n/a
/|	Rückgabe:		bool
/|  2002-07-14 20:29 MMT
/+------------------------------------------------------------*/
VSINLINE bool& PIPED3D2::IsInitialized() {
	return this->m_bInitialized;
}


/*------------------------------------------------------------
/|	Funktion:		Release()
/|	Beschreibung:	Gibt das Objekt frei
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2002-07-14 20:29 MMT
/+------------------------------------------------------------*/
VSINLINE void PIPED3D2::Release() {
	if(this->m_bInitialized) {
		this->m_bInitialized = false;

		// Die Pipeline auswerfen
		SAFE_RELEASE(this->m_DefaultRenderTarget);
		SAFE_RELEASE(this->m_objD3DDevice);
		SAFE_RELEASE(this->m_objD3D);
		
		// Restliche Werte auf Null setzen
		memset(&m_objD3DPresentParameters, 0, sizeof(m_objD3DPresentParameters));
		memset(&m_Caps, 0, sizeof(m_Caps));
		this->m_iWidth = 0;
		this->m_iHeight = 0;
		this->m_mtxProjektionsmatrix.Identity();
		this->m_mViewmatrix.Identity();
	}
}


/*------------------------------------------------------------
/|	Funktion:		~PIPED3D2()
/|	Beschreibung:	Destruktor
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2002-07-14 20:29 MMT
/+------------------------------------------------------------*/
VSINLINE PIPED3D2::~PIPED3D2() {
	this->Release();
}


/*------------------------------------------------------------
/|	Funktion:		PIPED3D2()
/|	Beschreibung:	Konstruktor
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2002-07-14 20:29 MMT
/+------------------------------------------------------------*/
VSINLINE PIPED3D2::PIPED3D2() {
	this->Initialize();
}


/*------------------------------------------------------------
/|	Funktion:		operator LPDIRECT3D9&()
/|	Beschreibung:	Liefert das Direct3D-Objekt
/|	Parameter:		n/a
/|	Rückgabe:		LPDIRECT3D9
/|  2002-07-14 20:36 MMT
/+------------------------------------------------------------*/
VSINLINE PIPED3D2::operator LPDIRECT3D9 () {
	return this->m_objD3D;
}

VSINLINE LPDIRECT3D9 PIPED3D2::GetDirect3D() {
	return this->m_objD3D;
}


/*------------------------------------------------------------
/|	Funktion:		operator LPDIRECT3DDEVICE9&()
/|	Beschreibung:	Liefert das Direct3D-Device
/|	Parameter:		n/a
/|	Rückgabe:		LPDIRECT3DDEVICE9
/|  2002-07-14 20:37 MMT
/+------------------------------------------------------------*/
VSINLINE PIPED3D2::operator LPDIRECT3DDEVICE9 () {
	return this->m_objD3DDevice;
}

VSINLINE LPDIRECT3DDEVICE9 PIPED3D2::GetDirect3DDevice() {
	return this->m_objD3DDevice;
}



VSINLINE MATRIX4& PIPED3D2::GetProjectionMatrix() {
	return this->m_mtxProjektionsmatrix;
}


/*------------------------------------------------------------
/|	Funktion:		Create()
/|	Beschreibung:	Erstellt das Objekt
/|	Parameter:		~~~
/|	Rückgabe:		HRESULT
/|  2002-07-14 20:37 MMT
/+------------------------------------------------------------*/
VSINLINE HRESULT PIPED3D2::Create(PIPEDESC PipeDescriptor) {
	// Diese Funktion verweist auf Create(D3DPRESENT_PARAMETERS, ...)
	return this->Create(PipeDescriptor.OutputWindow, PipeDescriptor.ScreenWidth, PipeDescriptor.ScreenHeight, PipeDescriptor.BackBuffer, PipeDescriptor.BackBufferCount, PipeDescriptor.Windowed, PipeDescriptor.Multisample, PipeDescriptor.DepthStencil);
}


/*------------------------------------------------------------
/|	Funktion:		Initialize()
/|	Beschreibung:	Initialisiert die ganze Plörre
/|	Parameter:		~~~
/|	Rückgabe:		void
/|  2002-07-14 20:37 MMT
/+------------------------------------------------------------*/
VSINLINE void PIPED3D2::Initialize() {
	// Zufallszahlengenerator anwerfen
	srand( (unsigned)time( NULL ) );

	// Die Pipeline anwerfen
	this->m_DefaultRenderTarget = NULL;
	this->m_objD3D = NULL;
	this->m_objD3DDevice = NULL;
	
	// D3D-Objekt erezugen
	this->m_objD3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	// Restliche Werte auf Null setzen
	memset(&m_objD3DPresentParameters, 0, sizeof(m_objD3DPresentParameters));
	memset(&m_Caps, 0, sizeof(m_Caps));
	this->m_iWidth = 800;
	this->m_iHeight = 600;
	this->m_mtxProjektionsmatrix.Identity();
	this->m_mViewmatrix.Identity();
	this->m_bInitialized = true;
	
	// Material-ID auf: kein Material
	this->m_iLastMaterial = -1;
	this->m_iLastTexture = -1;
	this->m_mDefaultMaterial.SetDefault();

/*
	if(!this->m_bInitialized) {
		// Zufallszahlengenerator anwerfen
		srand( (unsigned)time( NULL ) );

		// Die Pipeline anwerfen
		SAFE_RELEASE(this->m_DefaultRenderTarget);
		SAFE_RELEASE(this->m_objD3D);
		SAFE_RELEASE(this->m_objD3DDevice);
		
		// D3D-Objekt erezugen
		this->m_objD3D = Direct3DCreate9(D3D_SDK_VERSION);
		
		// Restliche Werte auf Null setzen
		memset(&m_objD3DPresentParameters, 0, sizeof(m_objD3DPresentParameters));
		memset(&m_Caps, 0, sizeof(m_Caps));
		this->m_iWidth = 800;
		this->m_iHeight = 600;
		this->m_mtxProjektionsmatrix.Identity();
		this->m_mViewmatrix.Identity();
		this->m_bInitialized = true;
	}
*/
}


VSINLINE PIPED3D2::operator D3DPRESENT_PARAMETERS& () {
	return this->m_objD3DPresentParameters;
}

VSINLINE D3DPRESENT_PARAMETERS& PIPED3D2::GetPresentParameters() {
	return this->m_objD3DPresentParameters;
}

VSINLINE HRESULT PIPED3D2::PrepareRendering() const {
	this->m_objD3DDevice->SetRenderState(D3DRS_AMBIENT,			D3DCOLOR_XRGB(255,255,255));
	this->m_objD3DDevice->SetRenderState(D3DRS_LIGHTING,		FALSE);
	this->m_objD3DDevice->SetRenderState(D3DRS_CULLMODE,		D3DCULL_CCW); 
	this->m_objD3DDevice->SetRenderState(D3DRS_ZENABLE,			TRUE);
	this->m_objD3DDevice->SetRenderState(D3DRS_STENCILENABLE,	TRUE);
	return S_OK;
}


VSINLINE HRESULT PIPED3D2::Clear() const {
	return this->m_objD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

VSINLINE HRESULT PIPED3D2::Clear(D3DCOLOR Color, DWORD ClearFlags) const {
	return this->m_objD3DDevice->Clear(0, NULL, ClearFlags, Color, 1.0f, 0);
}

VSINLINE HRESULT PIPED3D2::Present() const {
	return this->m_objD3DDevice->Present(NULL, NULL, NULL, NULL);
}





VSINLINE HRESULT PIPED3D2::SetProjectionMatrix() {
	return this->m_objD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&this->m_mtxProjektionsmatrix);
}

VSINLINE HRESULT PIPED3D2::SetProjectionMatrix(LPMATRIX4 Projektionsmatrix) {
	return this->m_objD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)Projektionsmatrix);
}

VSINLINE HRESULT PIPED3D2::SetWorldMatrix(LPMATRIX4 Weltmatrix) {
	// intern gecachte Viewmatrix verwenden
	MATRIX4 temp = Weltmatrix->GetMultiplied(m_mViewmatrix);
	return this->m_objD3DDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)temp);
}

VSINLINE HRESULT PIPED3D2::SetWorldMatrix(LPMATRIX4 Weltmatrix, bool m_bExplicit) {
	// intern gecachte Viewmatrix verwenden
	if(!m_bExplicit) {
		MATRIX4 temp = Weltmatrix->GetMultiplied(m_mViewmatrix);
		return this->m_objD3DDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)temp);
	} else {
		return this->m_objD3DDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)Weltmatrix);
	}
	return S_OK;
}

VSINLINE MATRIX4& PIPED3D2::CreateProjectionMatrix() {
	D3DVIEWPORT9 Viewport;
	float fAspekt = 0.f;

	if(FAILED(this->m_objD3DDevice->GetViewport(&Viewport))) {
		fAspekt = ((float)m_iWidth) / m_iHeight;
		dprintf("(WARNUNG) PIPED3D::ErstelleProjektionsmatrix(): GetViewport() fehlgeschlagen.\n");
	} else
		fAspekt = ((float)Viewport.Height) / Viewport.Width;

	this->m_mtxProjektionsmatrix.Projection(0.8f, fAspekt, 1.0f, 1000.0f);
	return this->m_mtxProjektionsmatrix;
}

VSINLINE MATRIX4& PIPED3D2::CreateProjectionMatrix(float fFOV, float fAspect, float fNearPlane, float fFarPlane) {
	this->m_mtxProjektionsmatrix.Projection(fFOV, fAspect, fNearPlane, fFarPlane);
	return this->m_mtxProjektionsmatrix;
}


VSINLINE void PIPED3D2::SetViewMatrix(LPMATRIX4 in_pmViewmatrix) {
	this->m_mViewmatrix.Assign(in_pmViewmatrix);
}

VSINLINE HRESULT PIPED3D2::SetViewMatrix(LPMATRIX4 in_pmViewmatrix, bool in_bNow) {
	this->m_mViewmatrix.Assign(in_pmViewmatrix);
	if(in_bNow) {
		return this->m_objD3DDevice->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)m_mViewmatrix);
	}
	return S_OK;
}

VSINLINE void PIPED3D2::PrepareViewMatrixCache() {
	MATRIX4 IdentityView;
	IdentityView.Identity();
	this->m_mViewmatrix.Identity();
	this->m_objD3DDevice->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&IdentityView);
}

VSINLINE void PIPED3D2::GetViewMatrix(LPMATRIX4 out_mMatrix, bool in_bFromDevice) {
	if(!in_bFromDevice) {
		out_mMatrix->Assign(&this->m_mViewmatrix);
	} else {
		this->m_objD3DDevice->GetTransform(D3DTS_VIEW, (D3DXMATRIX*)&out_mMatrix);
	}
}

VSINLINE void PIPED3D2::GetWorldMatrix(LPMATRIX4 out_mMatrix) {
	this->m_objD3DDevice->GetTransform(D3DTS_WORLD, (D3DXMATRIX*)&out_mMatrix);
}

VSINLINE void PIPED3D2::GetProjectionMatrix(LPMATRIX4 out_mMatrix, bool in_bFromDevice) {
	if(!in_bFromDevice) {
		out_mMatrix->Assign(&this->m_mtxProjektionsmatrix);
	} else {
		this->m_objD3DDevice->GetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&out_mMatrix);
	}
}



VSINLINE HRESULT PIPED3D2::BeginScene() const {
	return this->m_objD3DDevice->BeginScene();
}

VSINLINE HRESULT PIPED3D2::EndScene() const {
	return this->m_objD3DDevice->EndScene();
}


VSINLINE PIPED3D2::PIPED3D2(HWND OutputWindow, UINT ScreenWidth, UINT ScreenHeight, /*D3DFORMAT Presentation,*/ D3DFORMAT BackBuffer, UINT BackBufferCount, BOOL	Windowed, D3DMULTISAMPLE_TYPE Multisample, D3DFORMAT DepthStencil) {
	this->Initialize();
	this->Create(OutputWindow, ScreenWidth, ScreenHeight, BackBuffer, BackBufferCount, Windowed, Multisample, DepthStencil);
}

VSINLINE PIPED3D2::PIPED3D2(D3DPRESENT_PARAMETERS PresentParameters, UINT Adapter, D3DDEVTYPE DeviceType, DWORD BehaviorFlags) {
	this->Initialize();
	this->Create(PresentParameters, Adapter, DeviceType, BehaviorFlags);
}

VSINLINE PIPED3D2::PIPED3D2(PIPEDESC PipeDescriptor) {
	this->Initialize();
	this->Create(PipeDescriptor);
}



VSINLINE bool PIPED3D2::CanWBuffer() const {
	return (m_Caps.RasterCaps & D3DPRASTERCAPS_WBUFFER)!=0;
}

VSINLINE bool PIPED3D2::CanGamma() const {
	return ((m_Caps.Caps2 & D3DCAPS2_FULLSCREENGAMMA)!=0) && ((m_Caps.Caps2 & D3DCAPS2_CANCALIBRATEGAMMA)!=0);
}



VSINLINE bool PIPED3D2::InternalGetRenderTarget() {
	return SUCCEEDED(this->m_objD3DDevice->GetRenderTarget(0, &this->m_DefaultRenderTarget));
}

VSINLINE bool PIPED3D2::SetRenderTarget() {
	return SUCCEEDED(this->m_objD3DDevice->SetRenderTarget(0, m_DefaultRenderTarget));
}

VSINLINE bool PIPED3D2::SetRenderTarget(LPDIRECT3DSURFACE9 RenderTarget) {
	return SUCCEEDED(this->m_objD3DDevice->SetRenderTarget(0, RenderTarget));
}

VSINLINE bool PIPED3D2::SetRenderTarget(LPDIRECT3DTEXTURE9 RenderTarget) {
	LPDIRECT3DSURFACE9 RTSurface = NULL;
	RenderTarget->GetSurfaceLevel(0, &RTSurface);
	bool bSucceeded = SUCCEEDED(this->m_objD3DDevice->SetRenderTarget(0, RTSurface));
	SAFE_RELEASE(RTSurface);
	return bSucceeded;
}

VSINLINE bool PIPED3D2::GetRenderTarget(LPDIRECT3DSURFACE9 RenderTarget) const {
	return SUCCEEDED(this->m_objD3DDevice->GetRenderTarget(0, &RenderTarget));
}

//Füllmodi
VSINLINE bool PIPED3D2::SelectFillWireframe() {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME)));
}

VSINLINE bool PIPED3D2::SelectFillPoint() {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT)));
}

VSINLINE bool PIPED3D2::SelectFillSolid() {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID)));
}

//Culling
VSINLINE bool PIPED3D2::SelectCullNone() {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE)));
}

VSINLINE bool PIPED3D2::SelectCullCW() {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW)));
}

VSINLINE bool PIPED3D2::SelectCullCCW() {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW)));
}

//Alpha
VSINLINE bool PIPED3D2::SelectAlphaBlendEnabled(BOOL in_bEnabled) {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, in_bEnabled)));
}

VSINLINE void PIPED3D2::SelectAlphaTreshold(BOOL in_bEnabled, const unsigned short in_iValue) {
	this->m_objD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, in_bEnabled);
	if(in_bEnabled) {
		this->m_objD3DDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)in_iValue);	
		this->m_objD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	
	}
}

VSINLINE void PIPED3D2::SelectBlendAdditive() {
	// final color = new color × D3DBLEND_SRCALPHA + old color × D3DBLEND_DESTALPHA
	this->m_objD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->m_objD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
}

VSINLINE void PIPED3D2::SelectBlendSrcAlpha() {
	// final color = new color × D3DBLEND_SRCALPHA + old color / D3DBLEND_SRCALPHA
	this->m_objD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->m_objD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

VSINLINE void PIPED3D2::SelectBlendOverwrite() {
	// final color = new color × D3DBLEND_SRCALPHA + old color * 0
	this->m_objD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->m_objD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

//Shading
VSINLINE bool PIPED3D2::SelectShadeFlat() {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT)));
}

VSINLINE bool PIPED3D2::SelectShadeGouraud() {
	return(FAILED(this->m_objD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD)));
}

// Material
VSINLINE signed long int PIPED3D2::GetLastMaterialID() const {
	return this->m_iLastMaterial;
}

VSINLINE bool PIPED3D2::IsActiveMaterial(const signed long int in_MaterialID) const {
	return (this->m_iLastMaterial == in_MaterialID);
}

VSINLINE void PIPED3D2::SetMaterial(const D3DMATERIAL9 &in_Material) {
	// Material setzen
	m_iLastMaterial = -1;
	if(FAILED(m_objD3DDevice->SetMaterial(&in_Material))) {
		dprintf("PIPED3D2:SetMaterial(D3DMATERIAL9) - Zu setzendes Material verursachte Fehler INVALIDCALL.\n");
	}	
}

VSINLINE void PIPED3D2::SetMaterial(const MATERIAL &in_Material) {
	// Material prüfen
	if(m_iLastMaterial == in_Material.m_iID) return;
	// Material setzen
	m_iLastMaterial = in_Material.m_iID;
	if(FAILED(m_objD3DDevice->SetMaterial(&(in_Material.m_Material)))) {
		dprintf("PIPED3D2:SetMaterial(MATERIAL) - Zu setzendes Material verursachte Fehler INVALIDCALL.\n");
	}	
}

VSINLINE void PIPED3D2::SetDefaultMaterial() {
	this->SetMaterial(m_mDefaultMaterial);
}

// Light
VSINLINE void PIPED3D2::SelectLightingEnabled(BOOL in_bEnabled) {
	m_objD3DDevice->SetRenderState(D3DRS_LIGHTING, in_bEnabled);
}

VSINLINE void PIPED3D2::SelectLightEnabled(unsigned long int in_dwLightID, BOOL in_bEnabled) {
	m_objD3DDevice->LightEnable(in_dwLightID, in_bEnabled);
}

VSINLINE void PIPED3D2::SetAmbientColor(unsigned long int in_dwAmbientColor) {
	m_objD3DDevice->SetRenderState(D3DRS_AMBIENT, in_dwAmbientColor);
}

VSINLINE void PIPED3D2::SelectNormalizeNormals(BOOL in_bNormalize) {
	m_objD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, in_bNormalize);
}