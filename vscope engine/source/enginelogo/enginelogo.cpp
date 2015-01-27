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

	Dateiname:		enginelogo.cpp
	Beschreibung:	EngineLogo Kontainer
	Revision:		2
	Erstellt:		MMT, 10. Juli 2002 00:16

	Changelog:
	[2]		15. Juli 2002 00:18
			Neuer Konstruktor (Pipe-Direktübergabe)
	[1]		10. Juli 2002 00:16

===========================================================================*/

#include "enginelogo.h"
#include "enginelogo.inl.h"
#include "vslogo.h"
#include "..\blit\blit2d.h"

void VSFASTCALL ENGINELOGO::Render(LPDIRECT3DDEVICE9 inDevice, UINT Alpha) {
/*
	DWORD MagFilter, MinFilter, MipFilter;
	inDevice->GetSamplerState(0, D3DSAMP_MAGFILTER, &MagFilter);
	inDevice->GetSamplerState(0, D3DSAMP_MINFILTER, &MinFilter);
	inDevice->GetSamplerState(0, D3DSAMP_MIPFILTER, &MipFilter);

	inDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	inDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	inDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
*/
	DWORD FillMode;
	inDevice->GetRenderState(D3DRS_FILLMODE, &FillMode);
	inDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	// 184x65
	BlitRect(inDevice, this->LogoTexture, 596, 515, 780, 580, D3DCOLOR_ARGB(Alpha, 255, 255, 255), TRUE, 0.f);

	inDevice->SetRenderState(D3DRS_FILLMODE, FillMode);
/*
	inDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, MagFilter);
	inDevice->SetSamplerState(0, D3DSAMP_MINFILTER, MinFilter);
	inDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, MipFilter);
*/
}

ENGINELOGO::ENGINELOGO(LPDIRECT3DDEVICE9 in_Device) {
	//HRESULT hr = vs_CreateTexture(in_Device, "vslogo.bmp", &LogoTexture, D3DFMT_UNKNOWN, D3DCOLOR_ARGB(0, 0, 0, 0));
	HRESULT hr = D3DXCreateTextureFromFileInMemory(in_Device, &baVSLogoSmall, SIZEbaVSLogoSmall, &LogoTexture);
	if(FAILED(hr)) {
		//URGENT: Debugger benötigt
		//debug::vs_DebugMessage("(FEHLER) EngineLogo::Load() - Textur konnte nicht geladen werden.\n");
		return;
	}
}

void VSFASTCALL ENGINELOGO::Load(LPDIRECT3DDEVICE9 in_Device) {
	//HRESULT hr = vs_CreateTexture(in_Device, "vslogo.bmp", &LogoTexture, D3DFMT_UNKNOWN, D3DCOLOR_ARGB(0, 0, 0, 0));
	HRESULT hr = D3DXCreateTextureFromFileInMemory(in_Device, &baVSLogoSmall, SIZEbaVSLogoSmall, &LogoTexture);
	if(FAILED(hr)) {
		//URGENT: Debugger benötigt
		//debug::vs_DebugMessage("(FEHLER) EngineLogo::Load() - Textur konnte nicht geladen werden.\n");
		return;
	}
}