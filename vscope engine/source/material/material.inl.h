/*==========================================================================*
    v-scope: the vision's scope realtime 3D engine
    Copyright (C) 2003, Markus Mayer, Alle Rechte vorbehalten.

	Dieser Quellcode wird "WIE ER IST" vertrieben, ohne jegliche Garantie
	auf Stabilität, Vollständigkeit oder Nützlichkeit für einen bestimmten
	Zweck. Sie sind berechtigt, ihn für jeden beliebigen unkommerziellen 
	Zweck zu nutzen, verändern oder weiter zu vertreiben, solange die
	Copyrightinformation (oben) als Teil dieser Datei erhalten bleibt.
	Der Autor möchte ebenfalls freundlich darum bitten, dass ihm alle 
	signifikanten Änderungen an diesem Quellcode zugeschickt werden.

	Dateiname:		material.inl.h
	Beschreibung:	Material Inline-Definition
	Revision:		1
	Erstellt:		MMT, 25. Juni 2003 21:59

	Changelog:
	[1]		25. Juni 2003 21:59
			Erstellt

===========================================================================*/

#pragma once

#include "..\include-direct3d.h"
#include "..\piped3d2\piped3d2.h"
#include "..\piped3d2\piped3d2.inl.h"
#include "..\color\color4.h"
#include "..\color\color4.inl.h"
#include "material.h"

#pragma intrinsic(memset, memcpy)

// Konstruktion und Destruktion bei garnichts ....
VSINLINE MATERIAL::MATERIAL() {
	//memset(this, 0, sizeof(MATERIAL));
	Clear();
	m_iID = RANDOM::RandomNumber(0, 32767);
}

VSINLINE MATERIAL::~MATERIAL() {
}

VSINLINE MATERIAL::MATERIAL(D3DMATERIAL9 &in_Material){
	memcpy(&m_Material, &in_Material, sizeof(D3DMATERIAL9));
	m_iID = 0;
}

VSINLINE MATERIAL::MATERIAL(MATERIAL &in_Material) {
	memcpy(this, &in_Material, sizeof(MATERIAL));
}

/*------------------------------------------------------------
/|	Funktion:		SetMaterial()
/|	Beschreibung:	Kopiert die derzeit gesetzten Material-Attribute
/|					der Pipeline in das member-Material
/|	Parameter:		PIPED3D2 
/|	Rückgabe:		n/a
/|  2003-06-25 22:33 MMT
/+------------------------------------------------------------*/
VSINLINE void MATERIAL::SetMaterial(PIPED3D2 &in_FromPipe) {
	in_FromPipe.GetDirect3DDevice()->GetMaterial(&this->m_Material);
}

/*------------------------------------------------------------
/|	Funktion:		ApplyMaterial()
/|	Beschreibung:	Setzt das Material via Pipe
/|	Parameter:		PIPED3D2 
/|	Rückgabe:		n/a
/|  2003-06-25 22:33 MMT
/+------------------------------------------------------------*/
VSINLINE void MATERIAL::ApplyMaterial(PIPED3D2 &in_Pipe) const {
	/*
	if(in_Pipe.m_iLastMaterial == m_iID) return;
	if(FAILED(in_Pipe.GetDirect3DDevice()->SetMaterial(&this->m_Material))) {
		dprintf("MATERIAL:SetMaterial(Pipe) - Zu setzendes Material verursachte Fehler INVALIDCALL.\n");
	}
	*/
	in_Pipe.SetMaterial(*this);
}

/*------------------------------------------------------------
/|	Funktion:		operator n()
/|	Beschreibung:	Akzessoren für das ID-Tag
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-25 22:33 MMT
/+------------------------------------------------------------*/
VSINLINE MATERIAL::operator const unsigned short int  () const {
	return (const unsigned short int) this->m_iID;
}

/*------------------------------------------------------------
/|	Funktion:		operator n()
/|	Beschreibung:	Akzessoren für das ID-Tag
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-25 22:33 MMT
/+------------------------------------------------------------*/
VSINLINE MATERIAL::operator const unsigned int  () const {
	return (const unsigned int) this->m_iID;
}

/*------------------------------------------------------------
/|	Funktion:		operator n()
/|	Beschreibung:	Akzessoren für das ID-Tag
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-25 22:33 MMT
/+------------------------------------------------------------*/
VSINLINE MATERIAL::operator const D3DMATERIAL9  () const {
	return (const D3DMATERIAL9) this->m_Material;
}

/*------------------------------------------------------------
/|	Funktion:		operator n()
/|	Beschreibung:	Akzessoren für das ID-Tag
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-25 22:33 MMT
/+------------------------------------------------------------*/
VSINLINE MATERIAL::operator const D3DMATERIAL9* () const {
	return (const D3DMATERIAL9*) &this->m_Material;
}

/*------------------------------------------------------------
/|	Funktion:		operator n()
/|	Beschreibung:	Akzessoren für das ID-Tag
/|	Parameter:		n/a
/|	Rückgabe:		n/a
/|  2003-06-25 22:33 MMT
/+------------------------------------------------------------*/
VSINLINE MATERIAL::operator const D3DMATERIAL9& () const {
	return *(const D3DMATERIAL9*)&this->m_Material;
}


VSINLINE signed long int MATERIAL::GetID() const {
	return this->m_iID;
}

VSINLINE void MATERIAL::SetID(const signed long int in_iID) {
	this->m_iID = in_iID;
}


VSINLINE void MATERIAL::GetMaterial(D3DMATERIAL9& out_Material) const {
	memcpy(&out_Material, &m_Material, sizeof(D3DMATERIAL9));
}

VSINLINE void MATERIAL::GetMaterial(MATERIAL& out_Material) const {
	memcpy(&out_Material, this, sizeof(MATERIAL));
}

VSINLINE void MATERIAL::SetMaterial(const D3DMATERIAL9& in_Material) {
	memcpy(&m_Material, &in_Material, sizeof(D3DMATERIAL9));
	m_iID = 0;
}

VSINLINE void MATERIAL::SetMaterial(const MATERIAL& in_Material) {
	memcpy(this, &in_Material, sizeof(MATERIAL));
}





VSINLINE void MATERIAL::GetDiffuse(COLOR4 &out_cDiffuse) const {
	out_cDiffuse.Assign(m_Material.Diffuse.r, m_Material.Diffuse.g, m_Material.Diffuse.b, m_Material.Diffuse.a);
}

VSINLINE void MATERIAL::GetDiffuse(D3DCOLORVALUE &out_cDiffuse) const {
	out_cDiffuse = m_Material.Diffuse;
}

VSINLINE void MATERIAL::GetDiffuse(DWORD &out_cDiffuse) const {
	float r = m_Material.Diffuse.r;
	float g = m_Material.Diffuse.g;
	float b = m_Material.Diffuse.b;
	float a = m_Material.Diffuse.a;
	unsigned long dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned long) (r * 255.0f + 0.5f);
	unsigned long dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned long) (g * 255.0f + 0.5f);
	unsigned long dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned long) (b * 255.0f + 0.5f);
	unsigned long dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned long) (a * 255.0f + 0.5f);
	out_cDiffuse = (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

VSINLINE void MATERIAL::GetEmissive(COLOR4 &out_cEmissive) const {
	out_cEmissive.Assign(m_Material.Emissive.r, m_Material.Emissive.g, m_Material.Emissive.b, m_Material.Emissive.a);
}

VSINLINE void MATERIAL::GetEmissive(D3DCOLORVALUE &out_cEmissive) const {
	out_cEmissive = m_Material.Emissive;
}

VSINLINE void MATERIAL::GetEmissive(DWORD &out_cEmissive) const {
	float r = m_Material.Emissive.r;
	float g = m_Material.Emissive.g;
	float b = m_Material.Emissive.b;
	float a = m_Material.Emissive.a;
	unsigned long dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned long) (r * 255.0f + 0.5f);
	unsigned long dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned long) (g * 255.0f + 0.5f);
	unsigned long dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned long) (b * 255.0f + 0.5f);
	unsigned long dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned long) (a * 255.0f + 0.5f);
	out_cEmissive = (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

VSINLINE void MATERIAL::GetAmbient(COLOR4 &out_cAmbient) const {
	out_cAmbient.Assign(m_Material.Ambient.r, m_Material.Ambient.g, m_Material.Ambient.b, m_Material.Ambient.a);
}

VSINLINE void MATERIAL::GetAmbient(D3DCOLORVALUE &out_cAmbient) const {
	out_cAmbient = m_Material.Ambient;
}

VSINLINE void MATERIAL::GetAmbient(DWORD &out_cAmbient) const {
	float r = m_Material.Ambient.r;
	float g = m_Material.Ambient.g;
	float b = m_Material.Ambient.b;
	float a = m_Material.Ambient.a;
	unsigned long dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned long) (r * 255.0f + 0.5f);
	unsigned long dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned long) (g * 255.0f + 0.5f);
	unsigned long dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned long) (b * 255.0f + 0.5f);
	unsigned long dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned long) (a * 255.0f + 0.5f);
	out_cAmbient = (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

VSINLINE void MATERIAL::GetSpecular(COLOR4 &out_cSpecular) const {
	out_cSpecular.Assign(m_Material.Specular.r, m_Material.Specular.g, m_Material.Specular.b, m_Material.Specular.a);
}

VSINLINE void MATERIAL::GetSpecular(D3DCOLORVALUE &out_cSpecular) const {
	out_cSpecular = m_Material.Specular;
}

VSINLINE void MATERIAL::GetSpecular(DWORD &out_cSpecular) const {
	float r = m_Material.Specular.r;
	float g = m_Material.Specular.g;
	float b = m_Material.Specular.b;
	float a = m_Material.Specular.a;
	unsigned long dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned long) (r * 255.0f + 0.5f);
	unsigned long dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned long) (g * 255.0f + 0.5f);
	unsigned long dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned long) (b * 255.0f + 0.5f);
	unsigned long dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned long) (a * 255.0f + 0.5f);
	out_cSpecular = (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

VSINLINE float MATERIAL::GetPower() const {
	return m_Material.Power;
}


VSINLINE void MATERIAL::SetDiffuse(const COLOR4 &in_cDiffuse) {
	m_Material.Diffuse.r = in_cDiffuse.r;
	m_Material.Diffuse.g = in_cDiffuse.g;
	m_Material.Diffuse.b = in_cDiffuse.b;
	m_Material.Diffuse.a = in_cDiffuse.a;
}

VSINLINE void MATERIAL::SetDiffuse(const D3DCOLORVALUE &in_cDiffuse) {
	m_Material.Diffuse = in_cDiffuse;
}

VSINLINE void MATERIAL::SetEmissive(const COLOR4 &in_cEmissive) {
	m_Material.Emissive.r = in_cEmissive.r;
	m_Material.Emissive.g = in_cEmissive.g;
	m_Material.Emissive.b = in_cEmissive.b;
	m_Material.Emissive.a = in_cEmissive.a;
}

VSINLINE void MATERIAL::SetEmissive(const D3DCOLORVALUE &in_cEmissive) {
	m_Material.Emissive= in_cEmissive;
}

VSINLINE void MATERIAL::SetAmbient(const COLOR4 &in_cAmbient) {
	m_Material.Ambient.r = in_cAmbient.r;
	m_Material.Ambient.g = in_cAmbient.g;
	m_Material.Ambient.b = in_cAmbient.b;
	m_Material.Ambient.a = in_cAmbient.a;
}

VSINLINE void MATERIAL::SetAmbient(const D3DCOLORVALUE &in_cAmbient) {
	m_Material.Ambient = in_cAmbient;
}

VSINLINE void MATERIAL::SetSpecular(const COLOR4 &in_cSpecular) {
	m_Material.Specular.r = in_cSpecular.r;
	m_Material.Specular.g = in_cSpecular.g;
	m_Material.Specular.b = in_cSpecular.b;
	m_Material.Specular.a = in_cSpecular.a;
}

VSINLINE void MATERIAL::SetSpecular(const D3DCOLORVALUE &in_cSpecular) {
	m_Material.Specular = in_cSpecular;
}

VSINLINE void MATERIAL::SetPower(const float in_fPower) {
	m_Material.Power = in_fPower;
}


	
VSINLINE void MATERIAL::Clear() {
	signed long int iTempID = m_iID;
	memset(this, 0, sizeof(MATERIAL));
	m_iID = iTempID;
}

VSINLINE void MATERIAL::SetDefault() {
	Clear();
	SetAmbient(COLOR4(1.f, 1.f, 1.f, 0.f));
	SetDiffuse(COLOR4(1.f, 1.f, 1.f, 0.f));
}