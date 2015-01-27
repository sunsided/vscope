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

	Dateiname:		blit2d.h
	Beschreibung:	2D-Blitten mit DirectX
	Revision:		3
	Erstellt:		MMT, 10. Juli 2002 00:24

	Changelog:
	[3]		20. Juli 2002 06:31 MMT
			SurfFormatToString
	[2]		17. Juli 2002 21:25 MMT
			GetPixelByteCount
	[1]		10. Juli 2002 00:24
			Erstellt

===========================================================================*/

#pragma once

#ifndef BLIT2D_DEFINED
#define BLIT2D_DEFINED
#endif

#include "..\defines.h"
#include "..\include-direct3d.h"

/*------------------------------------------------------------
/|	Funktion:		CreateTexture()
/|	Beschreibung:	Erstellt eine Textur
/|	Rückgabe:		HRESULT
/|  2002-07-10 00:27 MMT
/+------------------------------------------------------------*/
VSINLINE HRESULT CreateTexture(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* strTexture, LPDIRECT3DTEXTURE9* ppTexture, D3DFORMAT d3dFormat, DWORD ColorKey ) {
	return D3DXCreateTextureFromFileEx( pd3dDevice, strTexture, 
				D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, d3dFormat, 
				D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
				D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, ColorKey, NULL, NULL, ppTexture );
}

/*------------------------------------------------------------
/|	Funktion:		BlitRect()
/|	Beschreibung:	Blittet eine Textur auf den Bildschirm
/|	Rückgabe:		n/a
/|  2002-07-10 00:27 MMT
/+------------------------------------------------------------*/
void VSFASTCALL BlitRect(LPDIRECT3DDEVICE9 in_Device, LPDIRECT3DTEXTURE9 in_SourceTexture, float left, float top, float right, float bottom, D3DCOLOR in_Color, BOOL in_UseTextureAlpha = FALSE, float in_zDist = 0);

/*------------------------------------------------------------
/|	Funktion:		BlitRect()
/|	Beschreibung:	Blittet eine Textur auf den Bildschirm
/|	Rückgabe:		bool
/|  2002-07-10 00:27 MMT
/+------------------------------------------------------------*/
bool VSFASTCALL CreateMaterial(D3DMATERIAL9* out_Material, float in_ambientR = 1.f, float in_ambientG = 1.f, float in_ambientB = 1.f, float in_emissiveR = 0.f,  float in_emissiveG = 0.f, float in_emissiveB = 0.f);

/*------------------------------------------------------------
/|	Funktion:		GetPixelByteCount()
/|	Beschreibung:	Gibt die Anzahl an Bytes pro Pixel zurück
/|	Rückgabe:		int
/|  2002-07-10 00:27 MMT
/+------------------------------------------------------------*/
VSINLINE int GetPixelByteCount(D3DFORMAT &PixelFormat) {
	switch(PixelFormat) {
		// unsigned
		case D3DFMT_A8R8G8B8:		return 4; break;
		case D3DFMT_X8R8G8B8:		return 4; break;
		case D3DFMT_A2B10G10R10:	return 4; break;
		case D3DFMT_G16R16:			return 4; break;
		case D3DFMT_R8G8B8:			return 3; break;
		case D3DFMT_R5G6B5:			return 2; break;
		case D3DFMT_X1R5G5B5:		return 2; break;
		case D3DFMT_A1R5G5B5:		return 2; break;
		case D3DFMT_A4R4G4B4:		return 2; break;
		case D3DFMT_A8R3G3B2:		return 2; break;
		case D3DFMT_X4R4G4B4:		return 2; break;
		case D3DFMT_A8L8:			return 2; break;
		case D3DFMT_A8:				return 1; break;
		case D3DFMT_R3G3B2:			return 1; break;
		case D3DFMT_A8P8:			return 1; break;
		case D3DFMT_P8:				return 1; break;
		case D3DFMT_L8:				return 1; break;
		case D3DFMT_A4L4:			return 1; break;
		//signed
		case D3DFMT_Q8W8V8U8:		return 4; break;
		case D3DFMT_V16U16:			return 4; break;
		//case D3DFMT_W11V11U10:		return 4; break;
		case D3DFMT_V8U8:			return 2; break;
		// mixed
		case D3DFMT_X8L8V8U8:		return 4; break;
		case D3DFMT_A2W10V10U10:	return 4; break;
		case D3DFMT_L6V5U5:			return 2; break;
		// buffer
		case D3DFMT_INDEX32:		return 4; break;
		case D3DFMT_D32:			return 4; break;
		case D3DFMT_D24S8:			return 4; break;
		case D3DFMT_D24X8:			return 4; break;
		case D3DFMT_D24X4S4:		return 4; break;
		case D3DFMT_INDEX16:		return 2; break;
		case D3DFMT_D16:			return 2; break;
		case D3DFMT_D16_LOCKABLE:	return 2; break;
		case D3DFMT_D15S1:			return 2; break;
		
		// unbekannt
		case D3DFMT_UNKNOWN:		return -1; break;
		default:					return -1; break;
	}
}

/*------------------------------------------------------------
/|	Funktion:		SurfaceFormatToString()
/|	Beschreibung:	Wandelt einen Surfaceformat-Name in eine String um
/|	Rückgabe:		char*
/|  2002-07-20 06:24 MMT
/+------------------------------------------------------------*/
char* VSFASTCALL SurfaceFormatToString(D3DFORMAT srcformat);