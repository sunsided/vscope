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

	Dateiname:		piped3d.h
	Beschreibung:	Direct3D-Pipeline Definition
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 22:03

	Changelog:
	[1]		10. Juli 2002 22:03
			Erstellt

===========================================================================*/

#pragma once

#ifndef PIPED3D_DEFINED
#define PIPED3D_DEFINED
#endif

#include "..\defines.h"
#include "..\include-windows.h"
#include "..\include-direct3d.h"
#include "..\matrix\matrix4.h"
#include "..\matrix\matrix4.inl.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct PIPEDESC;

/*---------------------------------------------------------------------------
	Strukturen für die Pipeline
---------------------------------------------------------------------------*/

class PIPED3D {
//:: Die Membervariablen ....................................................
public:
	LPDIRECT3D8				m_objD3D;
	LPDIRECT3DDEVICE8		m_objD3DDevice;
	D3DPRESENT_PARAMETERS	m_objD3DPresentParameters;

	MATRIX4					m_Weltmatrix;
	MATRIX4					m_Projektionsmatrix;

private:
	UINT					m_Width;
	UINT					m_Height;

//:: Die Konstruktoren ......................................................
public:
							PIPED3D();
							PIPED3D(HWND OutputWindow, UINT ScreenWidth, UINT ScreenHeight, /*D3DFORMAT Presentation,*/ D3DFORMAT BackBuffer, UINT BackBufferCount, BOOL	Windowed, D3DMULTISAMPLE_TYPE Multisample, D3DFORMAT DepthStencil);
							PIPED3D(D3DPRESENT_PARAMETERS PresentParameters, UINT Adapter = 0, D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL, DWORD BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING);
							PIPED3D(PIPEDESC PipeDescriptor);

//:: Die Destruktoren .......................................................
public:
	virtual					~PIPED3D();

//:: Das Interface ..........................................................
public:
	void					Release();
	void					Reset();

	HRESULT					Create(PIPEDESC PipeDescriptor);
	HRESULT					Create(D3DPRESENT_PARAMETERS PresentParameters, UINT Adapter = 0, D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL, DWORD BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING);
	HRESULT					Create(HWND	OutputWindow, UINT ScreenWidth, UINT ScreenHeight, /*D3DFORMAT Presentation,*/ D3DFORMAT BackBuffer, UINT BackBufferCount, BOOL	Windowed, D3DMULTISAMPLE_TYPE Multisample, D3DFORMAT DepthStencil);

	HRESULT					Clear();
	HRESULT					Clear(DWORD ClearFlags);
	HRESULT					Clear(D3DCOLOR Color, DWORD ClearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL);

	HRESULT					BeginScene();
	HRESULT					EndScene();
	HRESULT					Present();

	HRESULT					PrepareRendering();

	MATRIX4					ErstelleProjektionsmatrix();
	MATRIX4					ErstelleProjektionsmatrix(float fFOV, float fAspect, float fNearPlane, float fFarPlane);

	HRESULT					SetzeProjektionsmatrix();
	HRESULT					SetzeProjektionsmatrix(LPMATRIX4 Projektionsmatrix);
	HRESULT					SetzeWeltmatrix();
	HRESULT					SetzeWeltmatrix(LPMATRIX4 Weltmatrix);
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PIPED3D				*LPPIPED3D;
typedef PIPED3D				VS3D;
typedef PIPED3D				*LPVS3D;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef _ALIGN_16 PIPED3D	PIPED3DA16;
typedef _ALIGN_16 PIPED3D	*LPPIPED3DA16;
typedef _ALIGN_16 PIPED3D	VS3DA16;
typedef _ALIGN_16 PIPED3D	*LPVS3DA16;

typedef _ALIGN_32 PIPED3D	PIPED3DA32;
typedef _ALIGN_32 PIPED3D	*LPPIPED3DA32;
typedef _ALIGN_32 PIPED3D	VS3DA32;
typedef _ALIGN_32 PIPED3D	*LPVS3DA32;

typedef _CACHEALIGN PIPED3D	PIPED3DAC;
typedef _CACHEALIGN PIPED3D	*LPPIPED3DAC;
typedef _CACHEALIGN PIPED3D	VS3DAC;
typedef _CACHEALIGN PIPED3D	*LPVS3DAC;