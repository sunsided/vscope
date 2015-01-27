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

	Dateiname:		particle.h
	Beschreibung:	Partikel Definition
	Revision:		1
	Erstellt:		MMT, 20. Juli 2002 07:03

	Changelog:
	[1]		20. Juli 2002 07:03
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "particle.h"
#include "..\color\color4.inl.h"
#include "..\vektoren\vector3.inl.h"


VSINLINE PARTICLE::PARTICLE() :
	m_bAlive(false), m_fAge(0.f) {
}

VSINLINE PARTICLE::~PARTICLE() {
}

//:: Helferlein .............................................................
VSINLINE void PARTICLE::Accelerate(VECTOR3 &in_vForce, float in_fElapsedTime) {
	this->m_vSpeed += in_vForce * in_fElapsedTime;
}

VSINLINE bool PARTICLE::_CheckAge(float in_fElapsedTime) {
	this->m_fAge += in_fElapsedTime;
	if(this->m_fAge>=this->m_fMaxAge) this->m_bAlive = false;
	return this->m_bAlive;
}

//:: Das Interface ..........................................................
VSINLINE HRESULT PARTICLE::Update(float in_fElapsedTime) {
	if(!this->_CheckAge(in_fElapsedTime)) return FALSE;
	this->m_vOldPosition = this->m_vPosition;
	this->m_vPosition += this->m_vSpeed;
	return TRUE;
}

VSINLINE void PARTICLE::GetParticleVertex(VERTEX_T1_PARTICLE *out_vtxVertex) {
	out_vtxVertex->position.x = this->m_vPosition.x;
	out_vtxVertex->position.y = this->m_vPosition.y;
	out_vtxVertex->position.z = this->m_vPosition.z;
	out_vtxVertex->pointsize = this->m_fSize;
	this->m_vColor.MakeDWord(out_vtxVertex->color);
}