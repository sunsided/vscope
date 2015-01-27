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

	Dateiname:		primitives_dome.cpp
	Beschreibung:	Dome
	Revision:		1
	Erstellt:		MMT, 14. Juni 2003 14:01

	Changelog:
	[1]		14. Juni 2003 14:01
			Erstellt

===========================================================================*/

#include "primitives_dome.h"
#include "primitives_dome.inl.h"
#include "..\common\common.h"
#include "..\debug\debug.h"
#include "..\fastmath\fasttrig.h"
/*
#include "..\vektoren\vector3.h"
#include "..\matrix\matrix4.h"
#include "..\viewcone\viewcone.h"
#include "..\vertices\vertices.h"
#include "..\common\common.h"
#include "..\bounding\aabbox.h"
#include "..\enums-math.h"
#include "..\matrix\matrix4.inl.h"
#include "..\piped3d2\piped3d2.h"
#include "..\piped3d2\piped3d2.inl.h"*/

#pragma intrinsic(memset, memcpy)

// Konstruktoren ------------------------------------------------------------------------

PRIMITIVE_DOME::PRIMITIVE_DOME() {
	this->_Initialize();
}

PRIMITIVE_DOME::PRIMITIVE_DOME(PIPED3D2 &in_pPipe, const unsigned int in_iEdges, const unsigned int in_iRows, const float in_fRadius, const float in_fNormalFactor) {
	this->_Initialize();
	this->m_pPipe = &in_pPipe;
	this->m_iEdges = in_iEdges;
	this->m_iRows = in_iRows;
	this->m_fNormalFactor = in_fNormalFactor;
	this->m_fRadius = in_fRadius;
	Create();
}

// Destruktoren -------------------------------------------------------------------------

PRIMITIVE_DOME::~PRIMITIVE_DOME() {
	this->Release();
}


// Initialisierung ----------------------------------------------------------------------

void PRIMITIVE_DOME::_Initialize() {
	memset(this, 0, sizeof(PRIMITIVE_DOME));
	// defaulting
	m_iEdges = 16;
	m_iRows = 4;
	m_fRadius = 3.f;
	m_fNormalFactor = 1.f;
}

VSINLINE unsigned int PRIMITIVE_DOME::_GetVertexCount() const {
	return (m_iEdges+1) * 2 * m_iRows;
}

// Erzeugen des Domes -------------------------------------------------------------------

HRESULT VSFASTCALL PRIMITIVE_DOME::Create(PIPED3D2 &in_pPipe, const unsigned int in_iEdges, const unsigned int in_iRows, const float in_fRadius, const float in_fNormalFactor) {
	this->Release();
	this->_Initialize();
	this->m_pPipe = &in_pPipe;
	this->m_iEdges = in_iEdges;
	this->m_iRows = in_iRows;
	this->m_fNormalFactor = in_fNormalFactor;
	this->m_fRadius = in_fRadius;
	return Create();
}

HRESULT VSFASTCALL PRIMITIVE_DOME::Create() {
	m_pVertices = new VSD3DVERTEX_DIFFUSE[_GetVertexCount()];

	unsigned int iRow;
	unsigned int iVertex;
	float fStepsH = DEG2RAD(360.f / m_iEdges);
	float fStepsV = DEG2RAD(90.f / m_iRows);

	// Vertexpositionen vorberechnen
	VECTOR3						*m_aVertexPos = NULL; //[m_iRows][m_iEdges];
	m_aVertexPos = new VECTOR3[(m_iRows+1)*(m_iEdges+1)];
	//memset(m_aVertexPos, 0, sizeof(VECTOR3)*((m_iRows+1)*(m_iEdges+1)));

	unsigned int iMaximum = 0;

	for(iRow = 0; iRow < m_iRows; iRow++) {
		float fAngleV = fStepsV * iRow;
		for(iVertex = 0; iVertex <= m_iEdges; iVertex++) {
			float fAngleH = fStepsH * iVertex;
			float fY = fastsin(fAngleV);
			float fX = fastcos(fAngleH) * fastcos(fAngleV);// * (1-fY);
			float fZ = fastsin(fAngleH) * fastcos(fAngleV);// * (1-fY);
			m_aVertexPos[iRow*(m_iEdges+1)+iVertex].Assign(fX, fY, fZ);
			//m_aVertexPos[iRow*(m_iEdges+1)+iVertex].Normalize();
		}
	}
	for(iVertex = 0; iVertex<=m_iEdges; iVertex++) {
		m_aVertexPos[m_iRows*(m_iEdges+1)+iVertex].Assign(0.f, 1.f, 0.f);
	}

	unsigned int iAccess = 0;
	unsigned int iAccessT = 0;
	unsigned int iAccessor = 0;
	
	COLOR4 colorDefault(1.f, 1.f, 1.f, 1.f);

	for(iRow = 0; iRow < m_iRows; iRow++) {
		float fAngleV = fStepsV * iRow;
		for(iVertex = 0; iVertex <= m_iEdges; iVertex++) {
			iAccess = iRow*(m_iEdges+1)+iVertex;
			iAccessT = (iRow+1)*(m_iEdges+1)+iVertex;
			// Werte auslesen
			float fX = m_aVertexPos[iAccess].x;
			float fY = m_aVertexPos[iAccess].y;
			float fZ = m_aVertexPos[iAccess].z;
			float fXt = m_aVertexPos[iAccessT].x;
			float fYt = m_aVertexPos[iAccessT].y;
			float fZt = m_aVertexPos[iAccessT].z;

			float fInvRows = 1.f / m_iRows;
			colorDefault.a = fastsqrt(fastsqrt(((float)iRow*fInvRows)));
			D3DCOLOR color = colorDefault.MakeDWord();

			VECTOR3 vNormal = m_aVertexPos[iAccess]*m_fNormalFactor;		vNormal.Normalize();
			VECTOR3 vNormalT = m_aVertexPos[iAccessT]*m_fNormalFactor;		vNormalT.Normalize();
				
			// Vertex unten
			m_pVertices[iAccessor++].Assign(m_aVertexPos[iAccess]*m_fRadius, vNormal, color, ((float)iVertex/m_iEdges), (1.f-(float)iRow*fInvRows)*0.5f);
			// Vertex oben
			m_pVertices[iAccessor++].Assign(m_aVertexPos[iAccessT]*m_fRadius, vNormalT, color, ((float)iVertex/m_iEdges), (1.f-(float)(iRow+1)*fInvRows)*0.5f);
		}
	}

	HRESULT retval;
	retval = m_pPipe->GetDirect3DDevice()->CreateVertexBuffer(sizeof(VSD3DVERTEX_DIFFUSE)*_GetVertexCount(), D3DUSAGE_WRITEONLY, VS_D3DFVF_VERTEX_DIFFUSE, D3DPOOL_DEFAULT, &m_pVBdome, NULL);
	if(FAILED(retval)) {
		dprintf("dome creation: Erzeugung des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		SAFE_DELETE_ARRAY(m_aVertexPos);
		SAFE_DELETE_ARRAY(m_pVertices);
		return retval;
	}

	// Den Vertexpuffer mit Daten füllen
	void* ptr = NULL;
	retval = m_pVBdome->Lock(0, sizeof(VSD3DVERTEX_DIFFUSE)*_GetVertexCount(), (void**)&ptr, 0);
	if(FAILED(retval)) {
		dprintf("dome creation: Lock des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		SAFE_DELETE_ARRAY(m_aVertexPos);
		SAFE_DELETE_ARRAY(m_pVertices);
		return retval;
	}
	memcpy(ptr, m_pVertices, sizeof(VSD3DVERTEX_DIFFUSE)*_GetVertexCount());
	m_pVBdome->Unlock();

	// Spuren verwischen
	SAFE_DELETE_ARRAY(m_aVertexPos);
	SAFE_DELETE_ARRAY(m_pVertices);

	return S_OK;
}

// Freiegeben des Domes ------------------------------------------------------------------

void VSFASTCALL	PRIMITIVE_DOME::Release() {
	SAFE_DELETE_ARRAY(m_pVertices);
	SAFE_RELEASE(m_pVBdome);
}


// Rendern des Domes --------------------------------------------------------------------

HRESULT PRIMITIVE_DOME::Render() {
	HRESULT retval;
	
#ifdef _DEBUG
	if(this->m_pVBdome == NULL) {
		dprintf("dome rendering: Dome wurde noch nicht erzeugt - nichts zu rendern.\n");
		return E_FAIL;
	}
#endif

	//m_pPipe->GetDirect3DDevice()->SetVertexShader(VS_D3DFVF_VERTEX_DIFFUSE);
	//m_pPipe->GetDirect3DDevice()->SetVertexShader(NULL);
	m_pPipe->GetDirect3DDevice()->SetFVF(VS_D3DFVF_VERTEX_DIFFUSE);
	m_pPipe->GetDirect3DDevice()->SetStreamSource(0, m_pVBdome, 0, sizeof(VSD3DVERTEX_DIFFUSE));

	for(unsigned int iRow = 0; iRow < m_iRows; iRow++) {
		retval = m_pPipe->GetDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, iRow*((m_iEdges+1)*2), (m_iEdges)*2);
		if(FAILED(retval)) {
			dprintf("dome rendering: Fehler bei DrawPrimitive(). Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
			return retval;
		}
	}
	return S_OK;
}