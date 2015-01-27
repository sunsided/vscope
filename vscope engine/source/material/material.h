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

	Dateiname:		material.h
	Beschreibung:	Material Definition
	Revision:		1
	Erstellt:		MMT, 25. Juni 2003 21:59

	Changelog:
	[1]		25. Juni 2003 21:59
			Erstellt

===========================================================================*/

#pragma once

#ifndef MATERIAL_DEFINED
#define MATERIAL_DEFINED

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\color\color4.h"

/*---------------------------------------------------------------------------
	Vorabdeklarationen
---------------------------------------------------------------------------*/
class PIPED3D2;
class MATERIALMAN;

/*---------------------------------------------------------------------------
	Strukturen für die Skybox
---------------------------------------------------------------------------*/
struct MATERIAL {
friend MATERIALMAN;
friend PIPED3D2;
//:: Die Membervariablen ....................................................
public:
	union {
		D3DMATERIAL9		m_Material;
		struct {
			COLOR4			m_cDiffuse;	
			COLOR4			m_cAmbient;
			COLOR4			m_cSpecular;
			COLOR4			m_cEmissive;
			float			m_fPower;
		};
	};
protected:
	signed long int		m_iID;
public:

//:: Die Konstruktoren ......................................................
public:
							MATERIAL();
							MATERIAL(D3DMATERIAL9 &in_Material);
							MATERIAL(MATERIAL &in_Material);

//:: Die Destruktoren .......................................................
public:
							~MATERIAL();

//:: Akzessor ...............................................................
public:
	operator				const unsigned short int () const;
	operator				const unsigned int () const;
	operator				const D3DMATERIAL9 () const;
	operator				const D3DMATERIAL9* () const;
	operator				const D3DMATERIAL9& () const;

	void					GetMaterial(D3DMATERIAL9& out_Material) const;
	void					GetMaterial(MATERIAL& out_Material) const;
	void					SetMaterial(const D3DMATERIAL9& in_Material);
	void					SetMaterial(const MATERIAL& in_Material);

	void					GetDiffuse(COLOR4 &out_cDiffuse) const;
	void					GetDiffuse(D3DCOLORVALUE &out_cDiffuse) const;
	void					GetDiffuse(DWORD &out_cDiffuse) const;
	void					GetEmissive(COLOR4 &out_cEmissive) const;
	void					GetEmissive(D3DCOLORVALUE &out_cEmissive) const;
	void					GetEmissive(DWORD &out_cEmissive) const;
	void					GetAmbient(COLOR4 &out_cAmbient) const;
	void					GetAmbient(D3DCOLORVALUE &out_cAmbient) const;
	void					GetAmbient(DWORD &out_cAmbient) const;
	void					GetSpecular(COLOR4 &out_cSpecular) const;
	void					GetSpecular(D3DCOLORVALUE &out_cSpecular) const;
	void					GetSpecular(DWORD &out_cSpecular) const;
	float					GetPower() const;

	void					SetDiffuse(const COLOR4 &in_cDiffuse);
	void					SetDiffuse(const D3DCOLORVALUE &in_cDiffuse);
	void					SetEmissive(const COLOR4 &in_cEmissive);
	void					SetEmissive(const D3DCOLORVALUE &in_cEmissive);
	void					SetAmbient(const COLOR4 &in_cAmbient);
	void					SetAmbient(const D3DCOLORVALUE &in_cAmbient);
	void					SetSpecular(const COLOR4 &in_cSpecular);
	void					SetSpecular(const D3DCOLORVALUE &in_cSpecular);
	void					SetPower(const float in_fPower);

//:: Das Interface ..........................................................
public:
	void					SetMaterial(PIPED3D2 &in_FromPipe);
	void					ApplyMaterial(PIPED3D2 &in_Pipe) const;
	signed long int			GetID() const;
	
	void					Clear();
	void					SetDefault();

protected:
	void					SetID(const signed long int in_iID);
};

/*---------------------------------------------------------------------------
	Deklaration der unausgerichteten Datentypen
---------------------------------------------------------------------------*/
typedef MATERIAL					*LPMATERIAL;

/*---------------------------------------------------------------------------
	Deklaration der ausgerichteten Datentypen
---------------------------------------------------------------------------*/
/*typedef _ALIGN_16 MATERIAL			MATERIALA16;
typedef _ALIGN_16 MATERIAL			*LPMATERIALA16;

typedef _ALIGN_32 MATERIAL			MATERIALA32;
typedef _ALIGN_32 MATERIAL			*LPMATERIALA32;

typedef _CACHEALIGN MATERIAL		MATERIALAC;
typedef _CACHEALIGN MATERIAL		*LPMATERIALAC;*/

#endif