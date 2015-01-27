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

	Dateiname:		piped3d.nil.h
	Beschreibung:	Direct3D-Pipeline VSINLINE-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 22:03

	Changelog:
	[1]		10. Juli 2002 22:03
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\common\common.h"
#include "piped3d.h"
#include "pipedescriptor.h"
#include "..\include-windows.h"
#include "..\include-direct3d.h"
#include "..\matrix\matrix4.h"
#include "..\debug\debug.h"

#pragma intrinsic(memset, memcpy)

VSINLINE HRESULT PIPED3D::Clear() {
	return this->m_objD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

VSINLINE HRESULT PIPED3D::Clear(DWORD ClearFlags) {
	return this->m_objD3DDevice->Clear(0, NULL, ClearFlags, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

VSINLINE HRESULT PIPED3D::Clear(D3DCOLOR Color, DWORD ClearFlags) {
	return this->m_objD3DDevice->Clear(0, NULL, ClearFlags, Color, 1.0f, 0);
}

VSINLINE HRESULT PIPED3D::Present() {
	return this->m_objD3DDevice->Present(NULL, NULL, NULL, NULL);
}

VSINLINE HRESULT PIPED3D::PrepareRendering() {
	this->m_objD3DDevice->SetRenderState(D3DRS_AMBIENT,			D3DCOLOR_XRGB(255,255,255));
	this->m_objD3DDevice->SetRenderState(D3DRS_LIGHTING,		TRUE);
	this->m_objD3DDevice->SetRenderState(D3DRS_CULLMODE,		D3DCULL_CCW); 
	this->m_objD3DDevice->SetRenderState(D3DRS_ZENABLE,			TRUE);
	this->m_objD3DDevice->SetRenderState(D3DRS_STENCILENABLE,	TRUE);
	return S_OK;
}

VSINLINE HRESULT PIPED3D::SetzeProjektionsmatrix() {
	return this->m_objD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&this->m_Projektionsmatrix);
}

VSINLINE HRESULT PIPED3D::SetzeProjektionsmatrix(LPMATRIX4 Projektionsmatrix) {
	return this->m_objD3DDevice->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)Projektionsmatrix);
}

VSINLINE HRESULT PIPED3D::SetzeWeltmatrix() {
	return this->m_objD3DDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&this->m_Weltmatrix);
}

VSINLINE HRESULT PIPED3D::SetzeWeltmatrix(LPMATRIX4 Weltmatrix) {
	return this->m_objD3DDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)Weltmatrix);
}

VSINLINE MATRIX4 PIPED3D::ErstelleProjektionsmatrix() {
	D3DVIEWPORT8 Viewport;
	float fAspekt = 0.f;

	if(FAILED(this->m_objD3DDevice->GetViewport(&Viewport))) {
		fAspekt = ((float)m_Width) / m_Height;
		dprintf("(WARNUNG) PIPED3D::ErstelleProjektionsmatrix(): GetViewport() fehlgeschlagen.\n");
	} else
		fAspekt = ((float)Viewport.Height) / Viewport.Width;

	this->m_Projektionsmatrix.Projection(0.8f, fAspekt, 1.0f, 1000.0f);
	return this->m_Projektionsmatrix;
}

VSINLINE MATRIX4 PIPED3D::ErstelleProjektionsmatrix(float fFOV, float fAspect, float fNearPlane, float fFarPlane) {
	this->m_Projektionsmatrix.Projection(fFOV, fAspect, fNearPlane, fFarPlane);
	return this->m_Projektionsmatrix;
}

VSINLINE HRESULT PIPED3D::BeginScene() {
	return this->m_objD3DDevice->BeginScene();
}

VSINLINE HRESULT PIPED3D::EndScene() {
	return this->m_objD3DDevice->EndScene();
}

VSINLINE HRESULT PIPED3D::Create(PIPEDESC PipeDescriptor) {
	return this->Create(PipeDescriptor.OutputWindow, PipeDescriptor.ScreenWidth, PipeDescriptor.ScreenHeight, PipeDescriptor.BackBuffer, PipeDescriptor.BackBufferCount, PipeDescriptor.Windowed, PipeDescriptor.Multisample, PipeDescriptor.DepthStencil);
}

VSINLINE void PIPED3D::Reset() {
	memset(&this->m_objD3DPresentParameters, 0, sizeof(D3DPRESENT_PARAMETERS));
	this->m_Height = 0;
	this->m_Width = 0;
	this->m_Projektionsmatrix.ToZero();
	this->m_Weltmatrix.ToZero();
	this->m_objD3D = NULL;
	this->m_objD3DDevice = NULL;
}