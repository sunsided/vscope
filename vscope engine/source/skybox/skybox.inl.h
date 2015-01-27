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

	Dateiname:		skybox.inl.h
	Beschreibung:	Skybox Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 10. Juli 2002 18:09

	Changelog:
	[1]		10. Juli 2002 18:09
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "skybox.h"
#include "..\vektoren\vector3.h"
#include "..\vertices\vertices.h"
#include "..\viewcone\viewcone.h"

#include "..\vertices\vertices.inl.h"
#include "..\vektoren\vector3.inl.h"
#include "..\viewcone\viewcone.inl.h"
#include "..\plane\plane.inl.h"

#pragma intrinsic(memset, memcpy)

VSINLINE void SKYBOX::SetTextures(const LPDIRECT3DTEXTURE9 *Textures) {
	/*
	this->m_Texture[0] = Textures[0];
	this->m_Texture[1] = Textures[1];
	this->m_Texture[2] = Textures[2];
	this->m_Texture[3] = Textures[3];
	this->m_Texture[4] = Textures[4];
	this->m_Texture[5] = Textures[5];
	*/
	memcpy(this->m_Texture, Textures, sizeof(LPDIRECT3DTEXTURE9)*6);
}

VSINLINE void SKYBOX::SetTextures(const unsigned int Index, const LPDIRECT3DTEXTURE9 Texture) {
	/*
	this->m_Texture[Index] = Texture;
	*/
	if(Texture!=NULL) {
		//memcpy(&this->m_Texture[Index], Texture, sizeof(LPDIRECT3DTEXTURE9));
		this->m_Texture[Index] = Texture;
	} else {
		this->m_Texture[Index] = NULL;
	}
}

VSINLINE void SKYBOX::GetTextures(LPDIRECT3DTEXTURE9 *Textures) const {
	/*
	Textures[0] = this->m_Texture[0];
	Textures[1] = this->m_Texture[1];
	Textures[2] = this->m_Texture[2];
	Textures[3] = this->m_Texture[3];
	Textures[4] = this->m_Texture[4];
	Textures[5] = this->m_Texture[5];
	*/
	memcpy(Textures, this->m_Texture, sizeof(LPDIRECT3DTEXTURE9)*6);
}

VSINLINE void SKYBOX::GetTextures(unsigned int Index, LPDIRECT3DTEXTURE9 Texture) const {
	if(Index>5) Index=0;
	Texture = this->m_Texture[Index];
}

VSINLINE void SKYBOX::SetFiltering(const D3DTEXTUREFILTERTYPE FilterType) {
	this->m_fFilter = FilterType;
}

VSINLINE D3DTEXTUREFILTERTYPE SKYBOX::GetFiltering() const {
	return (D3DTEXTUREFILTERTYPE)this->m_fFilter;
}

VSINLINE int SKYBOX::Render(const VECTOR3 CameraPosition) {
	return this->Render(CameraPosition.x, CameraPosition.y, CameraPosition.z);
}

VSINLINE int SKYBOX::Render(const VIEWCONE *ViewCone, const VECTOR3 CameraPosition) {
	return this->Render(ViewCone, CameraPosition.x, CameraPosition.y, CameraPosition.z);
}