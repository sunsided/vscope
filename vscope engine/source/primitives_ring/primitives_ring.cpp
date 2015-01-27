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

	Dateiname:		primitives_ring.cpp
	Beschreibung:	Primitive: Ring
	Revision:		1
	Erstellt:		MMT, 29. Mai 2003 13:03

	Changelog:
	[1]		29. Mai 2003 13:03
			Erstellt

===========================================================================*/

#include "primitives_ring.h"
#include "primitives_ring.inl.h"
#include "..\vektoren\vector2.h"
#include "..\matrix\matrix4.h"
#include "..\matrix\matrix4.inl.h"
#include "..\enums-math.h"
#include "..\fastmath\fasttrig.h"
#include "..\debug\debug.h"
#include "..\common\common.h"

#pragma intrinsic(memset, memcpy)

//	Diese Funktion gibt Cosinus- und Sinuswerte für die Koordinaten des Punktes zurück
VECTOR2 VSFASTCALL _RingGetAngle(const unsigned int iSegments, const unsigned int iRow, const unsigned int iPointNumber) {
	if(iRow==0) {
		return VECTOR2(0.f, 0.f);
	}
	float fAngle = PIx2-DEG2RAD(360.f / (iRow*iSegments)) * iPointNumber;
	return VECTOR2(fastcos(fAngle), fastsin(fAngle));
}

HRESULT	VSFASTCALL PRIMITIVE_RING::Create(const float in_fInnerRadius, const float in_fOuterRadius, const unsigned int in_iSegments, const unsigned int in_iRows, const bool in_bFirstVertexUp) {
	// Array für Vertices erzeugen
	/* Benötigter Speicher
		innerer Fan:	Segmente+2 (Start- und Endvertex!) 
		äußere Reihen:	2*Segmente+2
	*/
	unsigned int iItemCount = /* je Reihe */ (in_iRows)*(2*in_iSegments+2);
	this->m_RingVertices = new VSVERTEX_XYZ_TEX1[iItemCount];
#ifdef _DEBUG
	memset(this->m_RingVertices, 0, iItemCount*sizeof(VSVERTEX_XYZ_TEX1));
#endif

#ifdef _DEBUG
	//dprintf("Ring creation: allocated %d bytes for %d items (%d bytes each).\n", iItemCount * sizeof(VSVERTEX_XYZ_TEX1), iItemCount, sizeof(VSVERTEX_XYZ_TEX1));
	dprintf("Ring creation: allocated %d bytes (%1.1f KB) for %d items (%d bytes each).\n", iItemCount * sizeof(VSVERTEX_XYZ_TEX1),(float)(iItemCount * sizeof(VSVERTEX_XYZ_TEX1))/1024, iItemCount, sizeof(VSVERTEX_XYZ_TEX1));
#endif

	float fSizeFactor = (in_fOuterRadius-in_fInnerRadius) / in_iRows;
	
	// Den Vertex-Fan der ersten Kreisreihe erzeugen
	float fStepsRad = DEG2RAD(360.f / in_iSegments);
	float fAngle = DEG2RAD(360);
	unsigned int iBase = in_iSegments+2;

	// Nun die folgenden Reihen
	unsigned int iVertexCount = 2*in_iSegments;
	unsigned int iStepper = 0;
	for(unsigned int iR=1; iR<=in_iRows; iR++) {
		float fUpperRowSizeFactor = in_fInnerRadius + fSizeFactor*iR;
		float fLowerRowSizeFactor = in_fInnerRadius + fSizeFactor*(iR-1);
		unsigned int iPointIdx = 0;
		
		iBase = (in_iSegments+2) + (iR-1)*iVertexCount;
		unsigned int iFirst = iStepper;

		for(unsigned int iItem=0; iItem<iVertexCount; iItem+=2) {
			VECTOR2 Point = _RingGetAngle(in_iSegments, 1, iPointIdx++);
			
			float fSin = Point.y;
			float fCos = Point.x;
			float fPosX = fCos;
			float fPosY = fSin;

			// Unterer Vertex
			this->m_RingVertices[iStepper++] = VSVERTEX_XYZ_TEX1( fPosX*fLowerRowSizeFactor, fPosY*fLowerRowSizeFactor, 0.f, (fPosX*fLowerRowSizeFactor+in_fOuterRadius)/(2*in_fOuterRadius), 1-((fPosY*fLowerRowSizeFactor+in_fOuterRadius)/(2*in_fOuterRadius)));
			// Oberer Vertex
			this->m_RingVertices[iStepper++] = VSVERTEX_XYZ_TEX1( fPosX*fUpperRowSizeFactor, fPosY*fUpperRowSizeFactor, 0.f, (fPosX*fUpperRowSizeFactor+in_fOuterRadius)/(2*in_fOuterRadius), 1-((fPosY*fUpperRowSizeFactor+in_fOuterRadius)/(2*in_fOuterRadius)));
		}
		// Letzter, unterer Vertex
		this->m_RingVertices[iStepper++] = this->m_RingVertices[iFirst];
		// Letzter, oberer Vertex
		this->m_RingVertices[iStepper++] = this->m_RingVertices[iFirst+1];
	}

	// Den Vertex-Puffer erzeugen
	HRESULT retval;
	retval = this->m_pd3dDevice->CreateVertexBuffer(sizeof(VSVERTEX_XYZ_TEX1)*iItemCount, D3DUSAGE_WRITEONLY, VSFVF_XYZ_TEX1, D3DPOOL_DEFAULT, &this->m_RingVB, NULL);
	if(FAILED(retval)) {
		dprintf("Ring creation: Erzeugung des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return retval;
	}

	// Den Vertexpuffer mit Daten füllen
	void*	ptr;
	retval = this->m_RingVB->Lock(0, sizeof(VSVERTEX_XYZ_TEX1)*iItemCount, (void**)&ptr, 0);
	if(FAILED(retval)) {
		dprintf("Ring creation: Lock des Vertex-Puffers fehlgeschlagen. Fehlercode: %d - %s\n  %s", retval, DXGetErrorString9(retval), DXGetErrorDescription9(retval));
		return retval;
	}
	memcpy(ptr, this->m_RingVertices, sizeof(VSVERTEX_XYZ_TEX1)*iItemCount);
	this->m_RingVB->Unlock();

	// Speicher für Array freigeben
	SAFE_DELETE_ARRAY(this->m_RingVertices);

	return S_OK;
}

HRESULT	VSFASTCALL PRIMITIVE_RING::Create(const LPDIRECT3DDEVICE9 in_Device, const float in_fInnerRadius, const float in_fOuterRadius, const unsigned int in_iSegments, const unsigned int in_iRows, const bool in_bFirstVertexUp) {
	// Variablen setzen
	this->m_iSegments = in_iSegments;
	this->m_iRows = in_iRows;
	this->m_pd3dDevice = in_Device;
	// Create-Funktion aufrufen
	return this->Create(in_fInnerRadius, in_fOuterRadius, in_iSegments, in_iRows, in_bFirstVertexUp);
}

int VSFASTCALL PRIMITIVE_RING::Render() {
	//this->m_pd3dDevice->SetVertexShader(VSFVF_XYZ_TEX1);
	this->m_pd3dDevice->SetVertexShader(NULL);
	this->m_pd3dDevice->SetFVF(VSFVF_XYZ_TEX1);
	this->m_pd3dDevice->SetStreamSource(0, m_RingVB, 0, sizeof(VSVERTEX_XYZ_TEX1));
	// Der innere Fan	
	//this->m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, this->m_iSegments);	
	// Die äußeren Reihen
	unsigned int iDoubleSegs = this->m_iSegments*2;
	for(unsigned int i=1; i<=this->m_iRows; i++) {
		this->m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, ((iDoubleSegs+2)*(i-1)), iDoubleSegs);
	}
	return 0;
}


unsigned int VSFASTCALL PRIMITIVE_RING::ExportVertices(VSVERTEX_XYZ_TEX1 *out_VertexArray, const float in_fInnerRadius, const float in_fOuterRadius, const unsigned int in_iSegments, const unsigned int in_iRows, const bool in_bFirstVertexUp) {
	// Array für Vertices erzeugen
	/* Benötigter Speicher
		innerer Fan:	Segmente+2 (Start- und Endvertex!) 
		äußere Reihen:	2*Segmente+2
	*/
	unsigned int iItemCount = /* je Reihe */ (in_iRows)*(2*in_iSegments+2);
	out_VertexArray = new VSVERTEX_XYZ_TEX1[iItemCount];
#ifdef _DEBUG
	memset(out_VertexArray, 0, iItemCount*sizeof(VSVERTEX_XYZ_TEX1));
#endif

#ifdef _DEBUG
	//dprintf("Ring export: allocated %d bytes for %d items (%d bytes each).\n", iItemCount * sizeof(VSVERTEX_XYZ_TEX1), iItemCount, sizeof(VSVERTEX_XYZ_TEX1));
	dprintf("Ring export: allocated %d bytes (%1.1f KB) for %d items (%d bytes each).\n", iItemCount * sizeof(VSVERTEX_XYZ_TEX1),(float)(iItemCount * sizeof(VSVERTEX_XYZ_TEX1))/1024, iItemCount, sizeof(VSVERTEX_XYZ_TEX1));
#endif

	float fSizeFactor = (in_fOuterRadius-in_fInnerRadius) / in_iRows;
	
	// Den Vertex-Fan der ersten Kreisreihe erzeugen
	float fStepsRad = DEG2RAD(360.f / in_iSegments);
	float fAngle = DEG2RAD(360);
	unsigned int iBase = in_iSegments+2;

	// Nun die folgenden Reihen
	unsigned int iVertexCount = 2*in_iSegments;
	unsigned int iStepper = 0;
	for(unsigned int iR=1; iR<=in_iRows; iR++) {
		float fUpperRowSizeFactor = in_fInnerRadius + fSizeFactor*iR;
		float fLowerRowSizeFactor = in_fInnerRadius + fSizeFactor*(iR-1);
		unsigned int iPointIdx = 0;
		
		iBase = (in_iSegments+2) + (iR-1)*iVertexCount;
		unsigned int iFirst = iStepper;

		for(unsigned int iItem=0; iItem<iVertexCount; iItem+=2) {
			VECTOR2 Point = _RingGetAngle(in_iSegments, 1, iPointIdx++);
			
			float fSin = Point.y;
			float fCos = Point.x;
			float fPosX = fCos;
			float fPosY = fSin;

			// Unterer Vertex
			out_VertexArray[iStepper++] = VSVERTEX_XYZ_TEX1( fPosX*fLowerRowSizeFactor, fPosY*fLowerRowSizeFactor, 0.f, (fPosX*fLowerRowSizeFactor+in_fOuterRadius)/(2*in_fOuterRadius), 1-((fPosY*fLowerRowSizeFactor+in_fOuterRadius)/(2*in_fOuterRadius)));
			// Oberer Vertex
			out_VertexArray[iStepper++] = VSVERTEX_XYZ_TEX1( fPosX*fUpperRowSizeFactor, fPosY*fUpperRowSizeFactor, 0.f, (fPosX*fUpperRowSizeFactor+in_fOuterRadius)/(2*in_fOuterRadius), 1-((fPosY*fUpperRowSizeFactor+in_fOuterRadius)/(2*in_fOuterRadius)));
		}
		// Letzter, unterer Vertex
		out_VertexArray[iStepper++] = out_VertexArray[iFirst];
		// Letzter, oberer Vertex
		out_VertexArray[iStepper++] = out_VertexArray[iFirst+1];
	}

	return iItemCount;
}