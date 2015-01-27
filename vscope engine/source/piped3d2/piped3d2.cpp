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

	Dateiname:		piped3d2.cpp
	Beschreibung:	Direct3D-Pipeline 2
	Revision:		1
	Erstellt:		MMT, 14. Juli 2002 19:16

	Changelog:
	[1]		14. Juli 2002 19:16
			Erstellt

===========================================================================*/

#include "piped3d2.h"
#include "piped3d2.inl.h"

#pragma intrinsic(memset, memcpy)

/*
bool					PIPED3D2::m_bInitialized = false;
LPDIRECT3D9				PIPED3D2::m_objD3D = NULL;
LPDIRECT3DDEVICE9		PIPED3D2::m_objD3DDevice = NULL;
LPDIRECT3DSURFACE9		PIPED3D2::m_DefaultRenderTarget = NULL;
D3DPRESENT_PARAMETERS	PIPED3D2::m_objD3DPresentParameters;
D3DCAPS9				PIPED3D2::m_Caps;
UINT					PIPED3D2::m_iWidth = -1;
UINT					PIPED3D2::m_iHeight = -1;
MATRIX4					PIPED3D2::m_mtxProjektionsmatrix;
MATRIX4					PIPED3D2::m_mViewmatrix;
*/

HRESULT	VSFASTCALL PIPED3D2::Create(D3DPRESENT_PARAMETERS PresentParameters, UINT Adapter, D3DDEVTYPE DeviceType, DWORD BehaviorFlags) {
	//Initialize();
	
	HRESULT hr;
	this->m_iHeight	= PresentParameters.BackBufferHeight;
	this->m_iWidth	= PresentParameters.BackBufferWidth;
	this->m_objD3DPresentParameters = PresentParameters;
	hr =  this->m_objD3D->CreateDevice(Adapter, DeviceType, PresentParameters.hDeviceWindow, BehaviorFlags, &PresentParameters, &this->m_objD3DDevice);
	if(SUCCEEDED(hr)) this->PrepareRendering();

	this->CreateProjectionMatrix();
	this->SetProjectionMatrix();
	this->PrepareViewMatrixCache();
	this->m_objD3DDevice->GetDeviceCaps(&m_Caps);

	this->InternalGetRenderTarget();

	this->SelectNormalizeNormals(true);
	this->SelectLightingEnabled(false);
	this->SetDefaultMaterial();

	return hr;
}


HRESULT	VSFASTCALL PIPED3D2::Create(HWND OutputWindow, UINT ScreenWidth, UINT ScreenHeight, /*D3DFORMAT Presentation,*/ D3DFORMAT BackBuffer, UINT BackBufferCount, BOOL	Windowed, D3DMULTISAMPLE_TYPE Multisample, D3DFORMAT DepthStencil) {
	// Diese Funktion verweist auf Create(D3DPRESENT_PARAMETERS, ...)
	D3DPRESENT_PARAMETERS PParam;
	memset(&PParam, 0, sizeof(D3DPRESENT_PARAMETERS));				
	PParam.BackBufferCount = BackBufferCount;
	PParam.BackBufferHeight = ScreenHeight;
	PParam.BackBufferWidth = ScreenWidth;
	PParam.BackBufferFormat = BackBuffer;
	PParam.hDeviceWindow = OutputWindow;
	PParam.AutoDepthStencilFormat = DepthStencil;
	PParam.EnableAutoDepthStencil = TRUE;
	PParam.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // D3DPRESENT_INTERVAL_IMMEDIATE
	PParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	PParam.Flags = 0;
	PParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PParam.MultiSampleType = Multisample;
	PParam.Windowed = Windowed;

	return this->Create(PParam);
}