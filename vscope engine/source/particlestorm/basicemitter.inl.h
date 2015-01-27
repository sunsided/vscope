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

	Dateiname:		basicemitter.inl.h
	Beschreibung:	ParticleStorm Basic Emitter
	Revision:		1
	Erstellt:		MMT, 20. Juli 2002 17:25

	Changelog:
	[2]		29. Mai 2003 18:03
			Weitergeführt
	[1]		20. Juli 2002 17:25
			Erstellt

===========================================================================*/

#pragma once

#include "..\defines.h"
#include "..\include-direct3d.h"
#include "..\common\common.h"
#include "..\random\random.h"
#include "..\debug\debug.h"
#include "..\piped3d2\piped3d2.inl.h"
#include "basicemitter.h"
#include "particle.h"
#include "particle.inl.h"

#pragma intrinsic(memset, memcpy)

VSINLINE PS1BASICEMITTER::PS1BASICEMITTER() {
	memset(this, 0, sizeof(PS1BASICEMITTER));
}

VSINLINE PS1BASICEMITTER::~PS1BASICEMITTER() {
	memset(this, 0, sizeof(PS1BASICEMITTER));
}

VSINLINE BOOL PS1BASICEMITTER::CreateParticleArray() {
	// Dass hier PARTICLEAC steht, ist rein willkürlich: dieser Emitter wollte es so!
	this->m_ParticleList = new PARTICLE[this->m_iMaxParticleCount];
	memset(this->m_ParticleList, 0, sizeof(PARTICLE)*this->m_iMaxParticleCount);
	return true;
}

VSINLINE long PS1BASICEMITTER::CreateNewParticle() {

	unsigned long i = this->m_iLastNew;

	if(this->m_iParticlesAlive >= this->m_iMaxParticleCount) return -1; // zu viele Partikel
	for(int o=0; o<this->m_iMaxParticleCount; o++) {	
		// freies Partikelchen finden
		if(!this->m_ParticleList[i].m_bAlive) {
			break;
		} else {
			i++; if(i>=this->m_iMaxParticleCount) i=0;
		}
	}
	this->m_iLastNew = i;
	// Partikel wurde gefunden - Initialisierung der Werte
	this->IncreaseLivingCount();
	PARTICLE *Part = &this->m_ParticleList[i];

	Part->m_bAlive = true;
	Part->m_fAge = 0.f;
	Part->m_fMaxAge = RandomNumber(this->GetMaxParticleAgeMin(), this->GetMaxParticleAgeMax());
	Part->m_fSize = this->GetEmissionSize();
	//Part->m_vColor = this->GetEmissionColor();

	Part->m_vColor.r = RandomNumber(0.25f, 1.f);
	Part->m_vColor.g = RandomNumber(0.25f, 1.f);
	Part->m_vColor.b = RandomNumber(0.25f, 1.f);

	Part->m_vOldPosition.x = this->m_vSystemPos.x + RandomNumber(this->m_vEmissionOriginMin.x, this->m_vEmissionOriginMax.x);
	Part->m_vOldPosition.y = this->m_vSystemPos.y + RandomNumber(this->m_vEmissionOriginMin.y, this->m_vEmissionOriginMax.y);
	Part->m_vOldPosition.z = this->m_vSystemPos.z + RandomNumber(this->m_vEmissionOriginMin.z, this->m_vEmissionOriginMax.z);
	Part->m_vPosition = Part->m_vOldPosition;
	Part->m_vSpeed.x = RandomNumber(this->m_vEmissionDirectionMin.x, this->m_vEmissionDirectionMax.x) * this->m_fEmissionSpeed;
	Part->m_vSpeed.y = RandomNumber(this->m_vEmissionDirectionMin.y, this->m_vEmissionDirectionMax.y) * this->m_fEmissionSpeed;
	Part->m_vSpeed.z = RandomNumber(this->m_vEmissionDirectionMin.z, this->m_vEmissionDirectionMax.z) * this->m_fEmissionSpeed;

	return i;
}

VSINLINE BOOL PS1BASICEMITTER::Update(const float in_fElapsedTime) {
	// Die Partikel updaten
	unsigned short count = 0;

	unsigned short c=this->m_iMaxParticleCount;
	unsigned short q=0;

	//for(unsigned short q=0; q < this->m_iMaxParticleCount; q++) {
	do {
		q = c-1;

		// Wenn das Partikel noch lebt, das Update aber fehlschlägt, ist es soeben gestorben
		// - alle anderen sind an dieser Stelle uninteressant.
		if(this->ParticleIsAlive(q) && !this->m_ParticleList[q].Update(in_fElapsedTime)) {
			this->DecreaseLivingCount();
			
			count++;

		} else if(this->ParticleIsAlive(q)) {	// Partikel lebt - Zusatzupdates
			//this->m_ParticleList[q].m_vColor.a = 1.f * (0+((this->m_ParticleList[q].m_fMaxAge-this->m_ParticleList[q].m_fAge)/this->m_ParticleList[q].m_fMaxAge));
			float fAgeRatio = this->m_ParticleList[q].m_fAge / this->m_ParticleList[q].m_fMaxAge;
			this->m_ParticleList[q].m_vColor.a = 1.f - fAgeRatio;// this->m_ParticleList[q].m_fMaxAge-this->m_ParticleList[q].m_fAge)/this->m_ParticleList[q].m_fMaxAge));
			this->m_ParticleList[q].m_fSize = fAgeRatio * this->m_fEmissionSize + this->m_fEmissionSize; //fAgeRatio * 3.f + 1.f;

			
			VECTOR3 vGrav(0.f, -0.0981f, 0.f);
			
			this->m_ParticleList[q].m_vSpeed += vGrav * 0.01f * in_fElapsedTime;

			if(fAgeRatio >= 0.75) this->m_ParticleList[q].m_vSpeed += vGrav * in_fElapsedTime;


			if(++count >= this->m_iParticlesAliveLastTurn) break; // wenn wir schon alle lebendigen bearbeitet haben, warum dann weiter schleifen?
		}
	} while(--c>0);
	//} // for

	// Neue Partikel halten die Welt am Atmen
	float fNewParticlesExact = (float)this->m_iEmissionRate * in_fElapsedTime;	// Neue Partikel, float (etwa 2.34)
	unsigned short iNumNewParticles = (int)fNewParticlesExact;			// Neue Partikel, int	(etwa 2)
	m_fNewParticlesExcess += fNewParticlesExact - iNumNewParticles;		// Überschuss, float (alt + (2.34-2))

	if(m_fNewParticlesExcess>=1.f) {							// Überschuss >= 1?	(etwa 10.56)
		iNumNewParticles += (int)m_fNewParticlesExcess;			// Integer auf Neue addieren	(alt + 10)
		m_fNewParticlesExcess -= (int)m_fNewParticlesExcess;	// Integer von Überschuss abziehen (alt - 10)
	}

	for(q=0; q<iNumNewParticles; q++) {			// Neue Partikel erzeugen
		if(this->CreateNewParticle()<0) break;					// Wenn Abbruch: zu viele Partikel
	}

	// Anzahl der lebendigen merken
	this->m_iParticlesAliveLastTurn = this->m_iParticlesAlive;

return TRUE;	
}

VSINLINE BOOL PS1BASICEMITTER::Initialize(PIPED3D2 &in_pPipe, const LPDIRECT3DTEXTURE9 pTexture, const unsigned short iMaxParticles) {
	// Pointer übernehmen
	this->m_pPipe = &in_pPipe;
	this->m_pTexture = pTexture;
	// Werte setzten
	this->m_iMaxParticleCount = iMaxParticles;
	this->m_iLastNew = 0;
	this->m_iParticlesAlive = 0;
	// Partikelarray erstellen
	this->CreateParticleArray();
	// Vertexbuffer erzeugen
	HRESULT hr;
	if(FAILED(hr = in_pPipe.GetDirect3DDevice()->CreateVertexBuffer(iMaxParticles*sizeof(PARTICLE), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS, D3DFVF_T1_PARTICLE, D3DPOOL_DEFAULT, &this->m_pVB, NULL))) {
		dprintf("ParticleStorm-1 BasicEmitter Initialization: Could not create Vertex Buffer.\n\tError code: %d.\n", hr);
		return FALSE;
	}
	return true;
}

VSINLINE BOOL PS1BASICEMITTER::Restore() {
	return TRUE;
}

VSINLINE void PS1BASICEMITTER::Release() {
	SAFE_DELETE_ARRAY(this->m_ParticleList);
	SAFE_RELEASE(this->m_pVB);
}

VSINLINE BOOL PS1BASICEMITTER::Render() {
	// Render states setzen
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.00f));
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.00f));
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.00f));
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.00f));
	this->m_pPipe->GetDirect3DDevice()->SetTexture(0, this->m_pTexture);
	this->m_pPipe->GetDirect3DDevice()->SetStreamSource(0, this->m_pVB, 0, sizeof(VERTEX_T1_PARTICLE));
	//this->m_pPipe->GetDirect3DDevice()->SetVertexShader(D3DFVF_T1_PARTICLE);
	this->m_pPipe->GetDirect3DDevice()->SetVertexShader(NULL);
	this->m_pPipe->GetDirect3DDevice()->SetFVF(D3DFVF_T1_PARTICLE);

	MATRIX4 matWelt;
	matWelt.Translation(this->m_vSystemPos.x, this->m_vSystemPos.y, this->m_vSystemPos.z);

	//this->m_pDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&matWelt);
	this->m_pPipe->SetWorldMatrix(&matWelt);

	HRESULT hr = 0;
	VERTEX_T1_PARTICLE *pVertices;		// Unser Link in den Vertex Buffer
	DWORD dwNumParticlesToRender = 0;	// Anzahl der bearbeiteten Vertices
	float fRenderQuantification = 0.1f; // 10% der Gesamtzahl
	DWORD dwAllowedParticles = (int)((float)this->m_iMaxParticleCount*fRenderQuantification);

	// Locken
	if(FAILED(hr = this->m_pVB->Lock(0, dwAllowedParticles*sizeof(VERTEX_T1_PARTICLE),(void**) &pVertices, D3DLOCK_DISCARD))) {
		dprintf("ParticleStorm-1 BasicEmitter Renderer: Failed locking Vertex Buffer.\n\tError code: %d.\n", hr);
		return FALSE;
	}

	// Render each particle
	unsigned int c = m_iMaxParticleCount;
	unsigned int q = 0;
	unsigned int count = 0;

	//for(int q=0; q<this->m_iMaxParticleCount; q++) {		// für alle Partikel
	do {
		q = c-1;
		
		if(this->m_ParticleList[q].m_bAlive) {				// wenn dieses Partikel lebendig ...
		
			PARTICLE &part = this->m_ParticleList[q];				// shortcut erstellen
			this->m_ParticleList[q].GetParticleVertex(pVertices);	// Den aktuellen Vertex füllen
			pVertices++;											// Pointer auf den nächsten Vertex
			if(++dwNumParticlesToRender == dwAllowedParticles) {	// Wenn render-Quantifikation erreicht
				
				if(FAILED(hr=this->m_pVB->Unlock())) {				// Puffer entriegeln
					dprintf("ParticleStorm-1 BasicEmitter Renderer: Failed unlocking Vertex Buffer at inner loop.\n\tError code: %d.\n", hr);
					return FALSE;
				}		
				if(FAILED(hr=this->m_pPipe->GetDirect3DDevice()->DrawPrimitive(D3DPT_POINTLIST, 0, dwNumParticlesToRender))) {
					dprintf("ParticleStorm-1 BasicEmitter Renderer: Failed drawing primitives.\n\tError code: %d.\n", hr);
					return FALSE;
				}
				if(FAILED(hr=this->m_pVB->Lock(0, dwAllowedParticles*sizeof(VERTEX_T1_PARTICLE),(void**) &pVertices, D3DLOCK_DISCARD))) {
					dprintf("ParticleStorm-1 BasicEmitter Renderer: Failed relocking Vertex Buffer.\n\tError code: %d.\n", hr);
					return FALSE;
				}
				dwNumParticlesToRender = 0;							// reset der zu rendernden Vertices

			}

			// nicht mehr suchen, wenn wir bereits alles gefunden haben!
			if(++count >= this->m_iParticlesAlive) break;

		}

	} while((--c)>0);
	//} // for

	if(FAILED(hr=this->m_pVB->Unlock())) {				// Puffer schluss-Entriegeln
		dprintf("ParticleStorm-1 BasicEmitter Renderer: Failed unlocking Vertex Buffer at end of loop.\n\tError code: %d.\n", hr);		
		return FALSE;
	}								
	if(dwNumParticlesToRender) {						// wenn noch Vertices gerendert werden möchten
		if(FAILED(hr = this->m_pPipe->GetDirect3DDevice()->DrawPrimitive(D3DPT_POINTLIST, 0, dwNumParticlesToRender ))) {
			dprintf("ParticleStorm-1 BasicEmitter Renderer: Failed drawing primitives at end of loop.\n\tError code: %d.\n", hr);
			return FALSE;
		}
	}

	// Render States zurücksetzen
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	this->m_pPipe->GetDirect3DDevice()->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	return TRUE;
}
