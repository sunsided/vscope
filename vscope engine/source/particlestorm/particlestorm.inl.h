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

	Dateiname:		particlestorm.inl.h
	Beschreibung:	ParticleStorm Inline-Funktionen
	Revision:		1
	Erstellt:		MMT, 20. Juli 2002 06:58

	Changelog:
	[1]		20. Juli 2002 06:58
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "particlestorm.h"
#include "..\debug\debug.h"
#include "..\common\common.h"
#include "..\piped3d2\piped3d2.inl.h"
#include <assert.h>

#pragma intrinsic(memset, memcpy)

VSINLINE PARTICLESTORMSYSTEM::PARTICLESTORMSYSTEM() {
	// Allet auf Null fegen
	this->ClearSystemToZero();
}

VSINLINE PARTICLESTORMSYSTEM::~PARTICLESTORMSYSTEM() {
	this->Release();
	this->ClearSystemToZero();
}

VSINLINE void PARTICLESTORMSYSTEM::Release() {
	/*
	if(m_pVB) {
		m_pVB->Release();
		m_pVB = NULL;
	}
	*/
	SAFE_RELEASE(this->m_pVB);
	/*
	if(m_ParticleList) {
		delete[] m_ParticleList;
		m_ParticleList = NULL;
	}
	*/
	SAFE_DELETE_ARRAY(this->m_ParticleList);
}

/*************** Accessor-FUnktionen ***********************************************************/

VSINLINE unsigned short PARTICLESTORMSYSTEM::GetParticleCount() const {
	return this->m_iMaxParticleCount;
}

VSINLINE unsigned short PARTICLESTORMSYSTEM::GetParticlesAlive() const {
	return this->m_iParticlesAlive;
}

VSINLINE float PARTICLESTORMSYSTEM::GetEmissionSpeed() const {
	return this->m_fEmissionSpeed;
}

VSINLINE void PARTICLESTORMSYSTEM::SetEmissionSpeed(const float fSpeed) {
	this->m_fEmissionSpeed = fSpeed;
}

VSINLINE VECTOR3 PARTICLESTORMSYSTEM::GetEmissionDirectionMin() const {
	return m_vEmissionDirectionMin;
}

VSINLINE VECTOR3 PARTICLESTORMSYSTEM::GetEmissionDirectionMax() const {
	return m_vEmissionDirectionMax;
}

VSINLINE void PARTICLESTORMSYSTEM::SetEmissionDirectionMin(const VECTOR3 &vDirection) {
	VECTOR3 vInternal(vDirection);
	vInternal.Normalize();
	m_vEmissionDirectionMin = vInternal;
}

VSINLINE void PARTICLESTORMSYSTEM::SetEmissionDirectionMax(const VECTOR3 &vDirection) {
	VECTOR3 vInternal(vDirection);
	vInternal.Normalize();
	m_vEmissionDirectionMax = vInternal;
}

VSINLINE unsigned short PARTICLESTORMSYSTEM::GetEmissionRate() const {
	return this->m_iEmissionRate;
}

VSINLINE void PARTICLESTORMSYSTEM::SetEmissionRate(const unsigned short iRate) {
	m_iEmissionRate = iRate;
}

VSINLINE PARTICLE& PARTICLESTORMSYSTEM::operator [] ( const unsigned short x ) const {
	return m_ParticleList[x];
}

VSINLINE PARTICLE& PARTICLESTORMSYSTEM::GetParticle( const unsigned short x ) const {
	return m_ParticleList[x];
}

VSINLINE BOOL PARTICLESTORMSYSTEM::ParticleIsAlive( const unsigned short x ) const {
	return m_ParticleList[x].m_bAlive;
}

VSINLINE float PARTICLESTORMSYSTEM::ParticleGetAge( const unsigned short x ) const {
	return m_ParticleList[x].m_fAge;
}

VSINLINE VECTOR3 PARTICLESTORMSYSTEM::GetSystemPos() const {
	return m_vSystemPos;
}

VSINLINE void PARTICLESTORMSYSTEM::SetSystemPos(const VECTOR3 &vNewPosition) {
	m_vSystemPos = vNewPosition;
}

VSINLINE float PARTICLESTORMSYSTEM::GetMaxParticleAgeMin() const {
	return this->m_fMaxParticleAgeMin;
}

VSINLINE float PARTICLESTORMSYSTEM::GetMaxParticleAgeMax() const {
	return this->m_fMaxParticleAgeMax;
}

VSINLINE void PARTICLESTORMSYSTEM::SetMaxParticleAgeMin(const float fAge) {
	m_fMaxParticleAgeMin = fAge;
}

VSINLINE void PARTICLESTORMSYSTEM::SetMaxParticleAgeMax(const float fAge) {
	m_fMaxParticleAgeMax = fAge;
}

VSINLINE COLOR4 PARTICLESTORMSYSTEM::GetEmissionColor() const{
	return m_cEmissionColor;
}

VSINLINE void PARTICLESTORMSYSTEM::SetEmissionColor(const COLOR4 &Color) {
	m_cEmissionColor = Color;
}

VSINLINE float PARTICLESTORMSYSTEM::GetEmissionSize() const {
	return m_fEmissionSize;
}

VSINLINE void PARTICLESTORMSYSTEM::SetEmissionSize(const float fSize) {
	m_fEmissionSize = fSize;
}

VSINLINE bool PARTICLESTORMSYSTEM::GetSystemActive() const {
	return m_bSystemActive;
}

VSINLINE bool PARTICLESTORMSYSTEM::GetSystemHalted() const {
	return m_bHalted;
}

VSINLINE void PARTICLESTORMSYSTEM::SetSystemHalted(const bool bHalted) {
	m_bHalted = bHalted;
}

VSINLINE PARTICLESYSTEMTYPE PARTICLESTORMSYSTEM::GetSystemType() const {
	return m_SystemType;
}

VSINLINE LPPIPED3D2 PARTICLESTORMSYSTEM::GetPipe() const {
	return m_pPipe;
}

VSINLINE void PARTICLESTORMSYSTEM::SetPipe(PIPED3D2 &in_pPipe) {
	//assert(m_pPipe != NULL);
	m_pPipe = &in_pPipe;
}

VSINLINE LPDIRECT3DTEXTURE9 PARTICLESTORMSYSTEM::GetTexture() const {
	return m_pTexture;
}

VSINLINE void PARTICLESTORMSYSTEM::SetTexture(const LPDIRECT3DTEXTURE9 pTexture) {
	m_pTexture = pTexture;
}

VSINLINE unsigned short PARTICLESTORMSYSTEM::GetMaxParticleCount() const {
	return this->m_iMaxParticleCount;
}

VSINLINE void PARTICLESTORMSYSTEM::SetMaxParticleCount(const unsigned short iCount) {
	this->m_iMaxParticleCount = iCount;
}

/*******************************************************************************/
VSINLINE void PARTICLESTORMSYSTEM::ClearSystemToZero() {
	memset(this, 0, sizeof(PARTICLESTORMSYSTEM));
}

VSINLINE BOOL PARTICLESTORMSYSTEM::DeleteParticleArray() {
	SAFE_DELETE_ARRAY(this->m_ParticleList);
	return TRUE;
}

VSINLINE void PARTICLESTORMSYSTEM::DecreaseLivingCount() {
	if(this->m_iParticlesAlive==0) return;
	this->m_iParticlesAlive--;
}

VSINLINE void PARTICLESTORMSYSTEM::IncreaseLivingCount() {
	this->m_iParticlesAlive++;
}