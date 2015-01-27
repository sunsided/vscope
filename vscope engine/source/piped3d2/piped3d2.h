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

	Dateiname:		piped3d2.h
	Beschreibung:	Direct3D-Pipeline 2 Definition
	Revision:		2
	Erstellt:		MMT, 14. Juli 2002 19:16

	Changelog:
	[3]		29. Mai 2003 14:17 MMT
			SwitchFill~-Funktionen
	[2]		17. Juli 2002 20:38 MMT
			RenderTarget-Funktionen und Gamma
	[1]		14. Juli 2002 19:16
			Erstellt

===========================================================================*/

#pragma once

#ifndef PIPED3D2_DEFINED
#define PIPED3D2_DEFINED
#endif

#include "..\defines.h"
#include "..\include-windows.h"
#include "..\include-direct3d.h"
#include "..\matrix\matrix4.h"
//#include "..\matrix\matrix4.inl.h"
#include "..\material\material.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
struct PIPEDESC;

/*---------------------------------------------------------------------------
	Strukturen für die Pipeline
---------------------------------------------------------------------------*/

#pragma pack(push)
#pragma pack(4)
class __declspec(align(32)) PIPED3D2 {
friend MATERIAL;
friend MATERIALMAN;
//:: Die Membervariablen ....................................................
private:
	D3DCAPS9					m_Caps;							// 304 Byte
	MATERIAL					m_mDefaultMaterial;				// 72 Byte
protected:
	MATRIX4						m_mtxProjektionsmatrix;			// 64 Byte
	MATRIX4						m_mViewmatrix;					// 64 Byte
private:
	D3DPRESENT_PARAMETERS		m_objD3DPresentParameters;		// 56 Byte
	LPDIRECT3DDEVICE9			m_objD3DDevice;					// 4 Byte
	LPDIRECT3D9					m_objD3D;						// 4 Byte
	signed long int				m_iLastTexture;					// 4 Byte
	signed long int				m_iLastMaterial;				// 4 Byte
	LPDIRECT3DSURFACE9			m_DefaultRenderTarget;			// 4 Byte
	UINT						m_iWidth;						// 4 Byte
	UINT						m_iHeight;						// 4 Byte
	bool						m_bInitialized;					// 1 Byte

//:: Die Konstruktoren ......................................................
public:
							PIPED3D2();
	void					Initialize();

							PIPED3D2(HWND OutputWindow, UINT ScreenWidth, UINT ScreenHeight, /*D3DFORMAT Presentation,*/ D3DFORMAT BackBuffer, UINT BackBufferCount, BOOL	Windowed, D3DMULTISAMPLE_TYPE Multisample, D3DFORMAT DepthStencil);
							PIPED3D2(D3DPRESENT_PARAMETERS PresentParameters, UINT Adapter = 0, D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL, DWORD BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING);
							PIPED3D2(PIPEDESC PipeDescriptor);

//:: Die Destruktoren .......................................................
public:
	virtual					~PIPED3D2();

//:: Helfergunktionen .......................................................
private:
	bool					InternalGetRenderTarget();

//:: Das Interface ..........................................................
public:
	// Operatoren: Casting ..................................................
							operator LPDIRECT3D9 ();
							operator LPDIRECT3DDEVICE9 ();
							operator D3DPRESENT_PARAMETERS& ();

	// Funktionen: Eigenschaftenzugriff .....................................
	LPDIRECT3D9				GetDirect3D();
	LPDIRECT3DDEVICE9		GetDirect3DDevice();
	MATRIX4&				GetProjectionMatrix();
	D3DPRESENT_PARAMETERS&	GetPresentParameters();

	// Funktionen: Objektsteuerung ..........................................
	bool&					IsInitialized();
	void					Release();

	// Funktionen: Initialisierung ..........................................
	HRESULT					Create(PIPEDESC PipeDescriptor);
	HRESULT	VSFASTCALL 		Create(D3DPRESENT_PARAMETERS PresentParameters, UINT Adapter = 0, D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL, DWORD BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING);
	HRESULT	VSFASTCALL 		Create(HWND	OutputWindow, UINT ScreenWidth, UINT ScreenHeight, /*D3DFORMAT Presentation,*/ D3DFORMAT BackBuffer, UINT BackBufferCount, BOOL	Windowed, D3DMULTISAMPLE_TYPE Multisample, D3DFORMAT DepthStencil);
	HRESULT					PrepareRendering() const;

	// Funktionen: Bildschirm löschen .......................................
	HRESULT					Clear() const;
	HRESULT					Clear(D3DCOLOR Color, DWORD ClearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL) const;

	// Funktionen: Shortcuts für Szene ......................................
	HRESULT					BeginScene() const;
	HRESULT					EndScene() const;
	HRESULT					Present() const;

	// Funktionen: Projektionsmatrix ........................................
	MATRIX4&				CreateProjectionMatrix();
	MATRIX4&				CreateProjectionMatrix(float fFOV, float fAspect, float fNearPlane, float fFarPlane);
	
	// Funktionen: Matrizen setzen ..........................................
	HRESULT					SetProjectionMatrix();
	HRESULT					SetProjectionMatrix(LPMATRIX4 Projektionsmatrix);
	HRESULT					SetWorldMatrix(LPMATRIX4 Weltmatrix);
	HRESULT					SetWorldMatrix(LPMATRIX4 Weltmatrix, bool m_bExplicit);
	void					SetViewMatrix(LPMATRIX4 in_pmViewmatrix);
	HRESULT					SetViewMatrix(LPMATRIX4 in_pmViewmatrix, bool in_bNow);

	void					GetViewMatrix(LPMATRIX4 out_mMatrix, bool in_bFromDevice = false);
	void					GetWorldMatrix(LPMATRIX4 out_mMatrix);
	void					GetProjectionMatrix(LPMATRIX4 out_mMatrix, bool in_bFromDevice = false);

	void					PrepareViewMatrixCache();

	// Funktionen: Capabilities .............................................
	bool					CanWBuffer() const;
	bool					CanGamma() const;

	// Funktionen: RenderTarget .............................................
	bool					SetRenderTarget();
	bool					SetRenderTarget(LPDIRECT3DSURFACE9 RenderTarget);
	bool					SetRenderTarget(LPDIRECT3DTEXTURE9 RenderTarget);
	bool					GetRenderTarget(LPDIRECT3DSURFACE9 RenderTarget) const;

	// Füllmodi
	bool					SelectFillWireframe();
	bool					SelectFillPoint();
	bool					SelectFillSolid();

	// Cullingmodi
	bool					SelectCullNone();
	bool					SelectCullCW();
	bool					SelectCullCCW();

	// Alpha
	bool					SelectAlphaBlendEnabled(BOOL in_bEnabled = TRUE);
	void					SelectAlphaTreshold(BOOL in_bEnabled = TRUE, const unsigned short in_iValue = 50);
	void					SelectBlendAdditive();
	void					SelectBlendSrcAlpha();
	void					SelectBlendOverwrite();

	// Shading
	bool					SelectShadeFlat();
	bool					SelectShadeGouraud();

	// Material
	signed long int			GetLastMaterialID() const;
	bool					IsActiveMaterial(const signed long int in_MaterialID) const;
	void					SetMaterial(const MATERIAL &in_Material);
	void					SetMaterial(const D3DMATERIAL9 &in_Material);
	void					SetDefaultMaterial();

	// Light
	void					SelectLightingEnabled(BOOL in_bEnabled = TRUE);
	void					SelectLightEnabled(unsigned long int in_dwLightID, BOOL in_bEnabled = TRUE);
	void					SetAmbientColor(unsigned long int in_dwAmbientColor = 0x00202020);
	void					SelectNormalizeNormals(BOOL in_bNormalize = TRUE);

};
#pragma pack(pop)

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef PIPED3D2				*LPPIPED3D2;
typedef PIPED3D2				VS3D2;
typedef PIPED3D2				*LPVS3D2;
#ifndef PIPED3D_DEFINED
typedef PIPED3D2				PIPED3D;
typedef PIPED3D2				*LPPIPED3D;
typedef PIPED3D2				VS3D;
typedef PIPED3D2				*LPVS3D;
#endif


/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 PIPED3D2		PIPED3D2A16;
typedef _ALIGN_16 PIPED3D2		*LPPIPED3D2A16;
typedef _ALIGN_16 PIPED3D2		VS3D2A16;
typedef _ALIGN_16 PIPED3D2		*LPVS3D2A16;
#ifndef PIPED3D_DEFINED
typedef _ALIGN_16 PIPED3D2		PIPED3DA16;
typedef _ALIGN_16 PIPED3D2		*LPPIPED3DA16;
typedef _ALIGN_16 PIPED3D2		VS3DA16;
typedef _ALIGN_16 PIPED3D2		*LPVS3DA16;
#endif

typedef _ALIGN_32 PIPED3D2		PIPED3D2A32;
typedef _ALIGN_32 PIPED3D2		*LPPIPED3D2A32;
typedef _ALIGN_32 PIPED3D2		VS3D2A32;
typedef _ALIGN_32 PIPED3D2		*LPVS3D2A32;
#ifndef PIPED3D_DEFINED
typedef _ALIGN_32 PIPED3D2		PIPED3DA32;
typedef _ALIGN_32 PIPED3D2		*LPPIPED3DA32;
typedef _ALIGN_32 PIPED3D2		VS3DA32;
typedef _ALIGN_32 PIPED3D2		*LPVS3DA32;
#endif

typedef _CACHEALIGN PIPED3D2	PIPED3D2AC;
typedef _CACHEALIGN PIPED3D2	*LPPIPED3D2AC;
typedef _CACHEALIGN PIPED3D2	VS3D2AC;
typedef _CACHEALIGN PIPED3D2	*LPVS3D2AC;
#ifndef PIPED3D_DEFINED
typedef _CACHEALIGN PIPED3D2	PIPED3DAC;
typedef _CACHEALIGN PIPED3D2	*LPPIPED3DAC;
typedef _CACHEALIGN PIPED3D2	VS3DAC;
typedef _CACHEALIGN PIPED3D2	*LPVS3DAC;
#endif*/