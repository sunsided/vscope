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

	Dateiname:		piped3d.cpp
	Beschreibung:	Direct3D-Pipeline
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 22:03

	Changelog:
	[1]		10. Juli 2002 22:03
			Erstellt

===========================================================================*/

#include "piped3d.h"
#include "piped3d.inl.h"

#pragma intrinsic(memset, memcpy)

PIPED3D::PIPED3D() {
	this->Reset();
	this->m_objD3D = Direct3DCreate8(D3D_SDK_VERSION);
}

PIPED3D::PIPED3D(HWND OutputWindow, UINT ScreenWidth, UINT ScreenHeight, /*D3DFORMAT Presentation,*/ D3DFORMAT BackBuffer, UINT BackBufferCount, BOOL	Windowed, D3DMULTISAMPLE_TYPE Multisample, D3DFORMAT DepthStencil) {
	this->Reset();
	this->m_objD3D = Direct3DCreate8(D3D_SDK_VERSION);
	this->Create(OutputWindow, ScreenWidth, ScreenHeight, BackBuffer, BackBufferCount, Windowed, Multisample, DepthStencil);
}

PIPED3D::PIPED3D(D3DPRESENT_PARAMETERS PresentParameters, UINT Adapter, D3DDEVTYPE DeviceType, DWORD BehaviorFlags) {
	this->Reset();
	this->m_objD3D = Direct3DCreate8(D3D_SDK_VERSION);
	this->Create(PresentParameters, Adapter, DeviceType, BehaviorFlags);
}

PIPED3D::PIPED3D(PIPEDESC PipeDescriptor) {
	this->Reset();
	this->m_objD3D = Direct3DCreate8(D3D_SDK_VERSION);
	this->Create(PipeDescriptor);
}

PIPED3D::~PIPED3D() {
	this->Release();
}

void PIPED3D::Release() {
	SAFE_RELEASE(this->m_objD3DDevice);
	SAFE_RELEASE(this->m_objD3D);
	this->Reset();
}

HRESULT	PIPED3D::Create(D3DPRESENT_PARAMETERS PresentParameters, UINT Adapter, D3DDEVTYPE DeviceType, DWORD BehaviorFlags) {
	HRESULT hr;
	this->m_Height	= PresentParameters.BackBufferHeight;
	this->m_Width	= PresentParameters.BackBufferWidth;
	this->m_objD3DPresentParameters = PresentParameters;
	hr =  this->m_objD3D->CreateDevice(Adapter, DeviceType, PresentParameters.hDeviceWindow, BehaviorFlags, &PresentParameters, &this->m_objD3DDevice);
	if(SUCCEEDED(hr)) this->PrepareRendering();
	return hr;
}


HRESULT	PIPED3D::Create(HWND	OutputWindow, UINT ScreenWidth, UINT ScreenHeight, /*D3DFORMAT Presentation,*/ D3DFORMAT BackBuffer, UINT BackBufferCount, BOOL	Windowed, D3DMULTISAMPLE_TYPE Multisample, D3DFORMAT DepthStencil) {
	D3DPRESENT_PARAMETERS PParam;
	memset(&PParam, 0, sizeof(D3DPRESENT_PARAMETERS));				
	PParam.BackBufferCount = BackBufferCount;
	PParam.BackBufferHeight = ScreenHeight;
	PParam.BackBufferWidth = ScreenWidth;
	PParam.BackBufferFormat = BackBuffer;
	PParam.hDeviceWindow = OutputWindow;
	PParam.AutoDepthStencilFormat = DepthStencil;
	PParam.EnableAutoDepthStencil = TRUE;
	PParam.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	PParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	PParam.Flags = 0;
	PParam.SwapEffect = D3DSWAPEFFECT_FLIP;
	PParam.MultiSampleType = Multisample;
	PParam.Windowed = Windowed;

	return this->Create(PParam);
}